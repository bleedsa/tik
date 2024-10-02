#include <debug.h>

#include "lex.h"

namespace lex {
	tape::tape(vec::vec<char> v) {
		i = 0, col = 1, line = 1;
		src = v;
	}

	auto tape::peek() -> option<char> {
		return src.at(i);
	}

	auto tape::inc_if(option<char> x) -> bool {
		if (x == peek()) {
			inc();
			return true;
		}
		return false;
	}

	auto tape::inc_if_not(option<char> x) -> bool {
		if (x != peek()) {
			inc();
			return true;
		}
		return false;
	}

	auto tok_t::to_str() -> str::str {
		auto r = str::str();

		for (size_t i = s.idx(); i < t.pos().idx(); i++) {
			auto c = t.at(i);
			if (c.is_some()) {
				r.push(c.get());
			}
		}


		return r;
	}

	static auto isverb(char c) -> bool {
		const char v[] = "~!@#$%^&*_+-=?><:'\\/";
		for (size_t i = 0; i < str::len(v); i++) {
			if (c == v[i]) return true;
		}
		return false;
	}

	static auto name(tape *t) -> R_T {
		auto p = t->pos();

		for (
			auto x = t->peek();
			x.is_some() && isalpha(x.get());
			x = t->peek()
		) t->inc();

		return R_T::mkok((tok_t){ NAME, p, *t });
	}

	static auto scan_num(tape *t) -> tok_t {
		auto p = t->pos();

		for (
			auto x = t->peek();
			x.is_some() && isdigit(x.get());
			x = t->peek()
		) t->inc();

		return (tok_t){ INT, p, *t };
	}

	static auto num(tape *t) -> R_T {
		/* lhs */
		auto l = scan_num(t);

		if (t->inc_if('.')) {
			auto r = scan_num(t);
			return R_T::mkok((tok_t){ FLT, l.s, *t });
		} else return R_T::mkok(l);
	}

	inline auto open(tape *t) -> R_T {
		auto p = t->pos();
		t->inc();
		return R_T::mkok((tok_t){ OPEN, p, *t });
	}

	inline auto close(tape *t) -> R_T {
		auto p = t->pos();
		t->inc();
		return R_T::mkok((tok_t){ CLOSE, p, *t });
	}

	inline auto sep(tape *t) -> R_T {
		auto p = t->pos();
		t->inc();
		return R_T::mkok((tok_t){ SEP, p, *t });
	}

	inline auto verb(tape *t) -> R_T {
		auto p = t->pos();
		t->inc();
		return R_T::mkok((tok_t){ VERB, p, *t });
	}

	auto token(tape *t) -> R_T {
		auto x = t->peek();
		if (x.is_some()) {
			auto c = x.get();
			if (isalpha(c)) return name(t);
			else if (isdigit(c)) return num(t);
			else if (isverb(c)) return verb(t);
			else {
				switch (c) {
				case '(':
				case '[':
				case '{':
					return open(t);
				case ')':
				case ']':
				case '}':
					return close(t);
				case ',':
				case '\n':
					return sep(t);
				default:
					auto r = str::str();
					r.append("lex ");
					r.append(t->pos().to_str());
					r.append("\n? ");
					r.push(c);
					return R_T::mkerr(r);
				}
			}
		} else {
			auto r = str::str();
			r.append("lex\n? EOF");
			return R_T::mkerr(r);
		}
	}

	auto lex(tape *t) -> R_A {
		auto r = vec::vec<tok_t>();

		do {
			auto e = token(t);
			if (e.is_ok()) r.push(e.ok());
			else return R_A::mkerr(e.err());
		} while (t->peek() != option<char>());

		return R_A::mkok(r);
	}
}
