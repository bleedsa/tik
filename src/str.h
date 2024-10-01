#ifndef __STR_H__
#define __STR_H__

#include <stdint.h>

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
	};

	str from_c(const char *s);
}

namespace chr {
	bool is_alpha(uint8_t x);
	bool is_digit(uint8_t x);
}

#endif
