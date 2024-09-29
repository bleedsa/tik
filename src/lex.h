#ifndef __LEX_H__
#define __LEX_H__

#include <ctype.h>
#include "vec.h"
#include "str.h"
#include "u.h"

namespace lex {
	enum err {
		UNEXPECTED_CHAR,
	};

	template<typename T>
	using R = result<T, err>;

	enum tok_ty {
		NUM,
		CHR,
		VEC,
		VERB,
		NAME,
	};

	struct tok {
		tok_ty type;
		size_t s; /* start */
		size_t e; /* end */
		vec::vec<char> *v;

		str::str to_str();
	};

	struct tape {
		size_t i;
		size_t line;
		size_t col;
		vec::vec<char> src;

		tape(vec::vec<char> s);
		R<vec::vec<tok>> lex();
	};
}

#endif
