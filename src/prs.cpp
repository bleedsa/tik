#include "prs.h"

namespace prs {
	auto node_t::to_str() -> str::str {
		auto s = str::str();

		switch (ty) {
		case INT:
			s.append(str::from_i(i));
			break;
		default:
			s.append("???");
		}

		return s;
	}

	auto parse(tape *t) -> R_A {
		auto r = vec::vec<node_t>();

		for (
			auto p = t->peek();
			p.is_some();
			t->inc(), p = t->peek()
		) {
			auto x = p.get();
			auto s = str::str();
			switch (x.ty) {
			case lex::INT:
				r.push(node_t(x.to_str().to_i()));
				break;
			default:
				s.append("parse\n? ");
				s.append(x.to_str());
				return R_A::mkerr(s);
			}
		}
		
		return R_A::mkok(r);
	}
}
