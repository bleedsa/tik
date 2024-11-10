#ifndef __PRS_H__
#define __PRS_H__

#include <stdint.h>
#include <ti/real>

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
		VERB,
	};

	struct verb_t;

	struct node_t {
		node_ty_t ty;
		union {
			int_t i;
			real_t f;
			uint8_t c;
			vec::vec<node_t> a;
			verb_t* v;
		};

		#define CLONE(x) { \
			ty = x.ty; \
			switch (ty) { \
			case INT: \
				i = x.i; \
				break; \
			case FLT: \
				f = x.f; \
				break; \
			case CHR: \
				c = x.c; \
				break; \
			case VEC: \
				a = x.a; \
				break; \
			case VERB: \
				v = x.v; \
				break; \
			} \
		}

		node_t(int_t x) {
			ty = INT;
			i = x;
		}

		node_t(real_t x) {
			ty = FLT;
			f = x;
		}

		node_t(vec::vec<node_t> x) {
			ty = VEC;
			a = x;
		}

		node_t(verb_t x);

		node_t(const node_t& x) CLONE(x)

		const node_t& operator=(const node_t& x) {
			CLONE(x)
			return *this;
		}

		~node_t() {
			switch (ty) {
			case VERB: free(v); break;
			default: break;
			}
		}

		str::str to_str();
	};

	struct verb_t {
		char v; /* verb */
		vec::vec<node_t> a; /* args */

		verb_t() {
			v = 0;
			a = vec::vec<node_t>();
		}

		verb_t(char c, vec::vec<node_t> q) {
			v = c;
			a = q;
		}

		const verb_t& operator=(const verb_t& x) {
			v = x.v;
			a = x.a;
			return *this;
		}
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

		bool inc_if(const char *x);
	};


	node_t::node_t(verb_t x) {
		ty = VERB;
		v = new verb_t();
		memcpy(&v, &x, sizeof(verb_t));
	}

	template<typename T>
	using R = result<T, str::str>;

	/* result vec */
	using R_A = R<vec::vec<node_t>>;
	/* result node */
	using R_N = R<node_t>;
	
	R_A exprs(tape *t);
	R_A parse(tape *t);
}

#endif
