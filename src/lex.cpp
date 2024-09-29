#include "lex.h"
#include "str.h"

namespace lex {
	tape::tape(vec::vec<char> v) {
		i = 0, col = 1, line = 1;
		src = v;
	}

	auto tape::lex() -> R<vec::vec<tok>> {
		auto r = vec::vec<tok>();

		/*
		for (; i < src.size(); i++) {
			auto c = src.at(i);
			if (chr::is_alpha(c));
			else return R<vec::vec<tok>>(UNEXPECTED_CHAR);
		}
		*/

		return result<vec::vec<tok>, err>(r);
	}

	auto tok::to_str() -> str::str {
		auto r = str::str();

		for (size_t i = s; i < e; i++) r.push(v->at(i));

		return r;
	}
}
