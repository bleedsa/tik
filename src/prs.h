#ifndef __PRS_H__
#define __PRS_H__

#include <stdint.h>

#include "u.h"
#include "vec.h"
#include "lex.h"
#include "str.h"

namespace prs {
	enum node_ty_t {
		INT,
		FLT,
		CHR,
		VEC,
	};

	struct node_t {
		node_ty_t ty;
		union {
			int_t i;
			double f;
			uint8_t c;
			vec::vec<node_t> a;
		};

		#define CLONE(x) { \
			ty = x.ty; \
			switch (ty) { \
			case INT: \
				i = x.i; \
				break; \
			case FLT: \
				dbg_printf("into float\n"); \
				f = x.f; \
				break; \
			case CHR: \
				c = x.c; \
				break; \
			case VEC: \
				a = x.a; \
				break; \
			} \
		}

		node_t(int_t x) {
			ty = INT;
			i = x;
		}

		node_t(const node_t& x) CLONE(x)

		const node_t& operator=(const node_t& x) {
			CLONE(x)
			return *this;
		}

		~node_t() { }

		str::str to_str();
	};

	struct tape {
		size_t i;
		vec::vec<lex::tok_t> src;

		tape(vec::vec<lex::tok_t> v) {
			i = 0;
			src = v;
		}

		inline auto inc() -> void {
			i++;
		}

		inline auto peek() -> option<lex::tok_t> {
			return src.at(i);
		}
	};

	template<typename T>
	using R = result<T, str::str>;

	/* result vec */
	using R_A = R<vec::vec<node_t>>;
	
	R_A parse(tape *t);
}

#endif
