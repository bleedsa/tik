#ifndef __LEX_H__
#define __LEX_H__

#include <ctype.h>
#include "vec.h"
#include "str.h"
#include "u.h"

namespace lex {
	template<typename T>
	using R = result<T, str::str>;

	enum tok_ty_t {
		INT,
		FLT,
		CHR,
		VERB,
		NAME,
		OPEN,
		CLOSE,
		SEP
	};

	struct pos_t {
		size_t i;
		size_t line;
		size_t col;

		inline size_t idx() {
			return i;
		}

		inline auto to_str() -> str::str {
			auto r = str::str();
			r.append(str::from_i(line));
			r.push(',');
			r.append(str::from_i(col));
			return r;
		}
	};

	struct tape {
		size_t i;
		size_t line;
		size_t col;
		vec::vec<char> src;

		tape(vec::vec<char> s);
		option<char> peek();
		
		inline option<char> at(size_t idx) {
			return src.at(idx);
		}

		inline pos_t pos() {
			return (pos_t) { i, line, col };
		}

		inline void inc() {
			i++;
			col++;
		}

		bool inc_if(option<char> x);
		bool inc_if_not(option<char> x);
	};

	struct tok_t {
		tok_ty_t ty;
		pos_t s; /* start */
		tape t;

		str::str to_str();

		inline auto pos() -> pos_t {
			return s;
		}
	};

	/** return tok_t */
	using R_T = R<tok_t>;
	/** return A (vec) */
	using R_A = R<vec::vec<tok_t>>;
	/** return S (str) */
	using R_S = R<str::str>;

	R_A lex(tape *t);
}

#endif
