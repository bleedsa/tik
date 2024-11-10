#include "prs.h"
#include "con.h"

namespace prs {
	auto node_t::to_str() -> str::str {
		auto s = str::str();

		switch (ty) {
		case INT: s.append(str::from_i(i)); break;
		case FLT: s.append(str::from_f(f)); break;
		case VEC: {
			s.push('(');
			a.for_each([&s](node_t x) {
				s.append(x.to_str());
				s.push(',');
			});
			s.append("\b)");
			break;
		}
		default:
			s.append("???");
		}

		return s;
	}

	auto tape::inc_if(const char *x) -> bool {
		auto i = peek();
		if (i.is_some()) {
			auto b = str::from_c(x).eql(i.get().to_str());

			if (b) inc();
			dbg_printf("b: %s\n", b ? "true" : "false");

			return b;
		} else return false;
	}

	auto noun(tape *t) -> R_N {
		dbg_printf("noun()\n");

		auto p = t->peek();

		if (p.is_some()) {
			auto x = p.get();
			switch (x.ty) {
			case lex::INT: {
				t->inc();
				auto n = node_t(x.to_str().to_i());
				auto ns = n.to_str().to_c_str();
				dbg_printf("n: %s\n", ns);
				free(ns);
				return R_N::mkok(n);
			}
			case lex::FLT:
				t->inc();
				return R_N::mkok(node_t(x.to_str().to_f()));
			case lex::OPEN:
				if (t->inc_if("(")) {
					auto r = exprs(t);
					if (!t->inc_if(")")) {
						auto q = t->peek();
						auto s = str::str();
						s.append("parse ");
						s.append((q.is_some() ? q.get().pos() : x.pos()).to_str());
						s.append("\nunclosed vec\n? ");
						s.append(q.is_some() ? q.get().to_str() : str::from_c("EOF"));
						return R_N::mkerr(s);
					}
					
					if (r.is_ok()) return R_N::mkok(node_t(r.ok()));
					else {
						auto s = str::str();
						s.append("parse ");
						s.append(x.pos().to_str());
						s.append("\nerr in vec:\n? ");
						s.append(r.err());
						return R_N::mkerr(s);
					}
				} else goto err;
				break;
			default:
			err:
				auto s = str::str();
				s.append("parse ");
				s.append(x.pos().to_str());
				s.append("\n? ");
				s.append(x.to_str());
				return R_N::mkerr(s);
			}
		} else {
			auto s = str::str();
			s.append("parse\n? EOF");
			return R_N::mkerr(s);
		}
	}

	auto expr(tape *t) -> R_N {
		dbg_printf("expr()\n");

		auto p = t->peek();
		if (p.is_some()) {
			auto x = p.get();
			switch (x.ty) {
			case lex::VERB: {
				t->inc();
				auto n = noun(t);
				if (n.is_ok()) {
					auto a = vec::vec<node_t>();
					a.push(n.ok());

					auto c = x.to_str().at(0);

					return R_N::mkok(node_t(verb_t(c, a)));
				} else {
					return R_N::mkerr(n.err());
				}
			}
			default: return noun(t);
			}
		} else {
			return R_N::mkerr(str::from_c("parse\n? EOF"));
		}
	}

	auto exprs(tape *t) -> R_A {
		dbg_printf("exprs()\n");

		auto r = vec::vec<node_t>();

		for (
			auto p = t->peek();
			p.is_some();
			p = t->peek()
		) {
			auto x = expr(t);
			if (x.is_ok()) r.push(x.ok());
			else return R_A::mkerr(x.err());
			if (!t->inc_if(",")) goto ret;
		}

		ret:
		return R_A::mkok(r);
	}

	auto parse(tape *t) -> R_A {
		return exprs(t);
	}
}
