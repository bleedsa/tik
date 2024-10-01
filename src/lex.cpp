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

	auto tape::inc_if(char x) -> bool {
		if (peek() == option<char>(x)) {
			inc();
			return true;
		}
		return false;
	}

	auto tok_t::to_str() -> R_S {
		auto r = str::str();

		for (size_t i = s.idx(); i < t.pos().idx(); i++) {
			auto c = t.at(i);
			if (c.is_some()) {
				r.push(c.get());
			}
		}


		return R_S::mkok(r);
	}

	auto name(tape *t) -> R_T {
		auto p = t->pos();

		for (
			auto x = t->peek();
			x.is_some() && isalpha(x.get());
			x = t->peek()
		) t->inc();

		return R_T::mkok((tok_t){ NUM, p, *t });
	}

	auto num(tape *t) -> R_T {
		auto p = t->pos();

		for (
			auto x = t->peek();
			x.is_some() && isdigit(x.get());
			x = t->peek()
		) t->inc();

		return R_T::mkok((tok_t){ NAME, p, *t });
	}

	auto expr(tape *t) -> R_T {
		auto x = t->peek();
		if (x.is_some()) {
			auto c = x.get();
			if (isalpha(c)) return name(t);
			else if (isdigit(c)) return num(t);
			else {
				auto r = str::str();
				r.append("'lex\n? ");
				r.push(c);
				return R_T::mkerr(r);
			}
		} else return R_T::mkerr(str::from_c("'lex\n? EOF"));
	}

	auto exprs(tape *t) -> R_A {
		auto r = vec::vec<tok_t>();

		do {
			auto e = expr(t);
			if (e.is_ok()) r.push(e.ok());
			else return R_A::mkerr(e.err());
		} while (t->inc_if(','));

		return R_A::mkok(r);
	}
}
