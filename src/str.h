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

		void push(char x);
		char at(size_t x);
		size_t len();
	};

	str from_c(char *s);
}

namespace chr {
	bool is_alpha(uint8_t x);
	bool is_digit(uint8_t x);
}

#endif
