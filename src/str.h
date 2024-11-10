#ifndef __STR_H__
#define __STR_H__

#include "u.h"
#include <stdint.h>
#include <ti/real>
#include <debug.h>

namespace str {
	uint8_t len(const char *s);

	struct str {
		size_t i;
		size_t sz;
		char *buf;

		str();
		~str();
		str(const str& x);
		str& operator=(const str& x);

		void push(char x);
		void append(const char *x);
		void append(str x);
		char at(size_t x);
		size_t len();
		char *to_c_str();

		int_t to_i();
		real_t to_f();

		bool eql(str x) {
			auto l = len();
			if (l == x.len()) {
				for (size_t i = 0; i < l; i++) {
					if (at(i) != x.at(i)) return false;
				}
				return true;
			}
			return false;
		}
	};

	str from_c(const char *s);
	str from_i(int_t x);
	str from_f(real_t x);
}

namespace chr {
	bool is_alpha(uint8_t x);
	bool is_digit(uint8_t x);
}

#endif
