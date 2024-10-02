#include "str.h"
#include <stdlib.h>
#include <string.h>
#include <debug.h>

namespace str {
	uint8_t len(const char *s) {
		uint8_t i;
		for (i = 0; *s; i++, s++);
		return i;
	}

	str::str() {
		i = 0;
		sz = 1;
		buf = (char*)malloc(sizeof(char) * sz);
		if (buf == nullptr) fatal(OS_E_MEMORY);
		memset(buf, 0, sizeof(char) * sz);
	}

	str::~str() {
		free(buf);
	}

	#define CLONE(x) { \
		i = x.i, sz = x.sz; \
		buf = (char*)malloc(sizeof(char) * sz); \
		if (buf == nullptr) fatal(OS_E_MEMORY); \
		memcpy(buf, x.buf, sizeof(char) * sz); \
	}

	str::str(const str& x) CLONE(x)

	str& str::operator=(const str& x) {
		CLONE(x);
		return *this;
	}

	void str::push(char x) {
		if (i >= sz) {
			sz += 1;
			buf = (char*)realloc(buf, sizeof(char) * sz);
		}

		buf[i] = x;
		i++;
	}

	void str::append(const char *x) {
		dbg_printf("appending char*: ");
		for (size_t j = 0; j < ::str::len(x); j++) {
			push(x[j]);
			dbg_printf("%c", buf[i - 1]);
		}
		dbg_printf("\n");
	}

	void str::append(str x) {
		dbg_printf("appending str: ");
		for (size_t j = 0; j < x.len(); j++) {
			dbg_printf("%c", x.at(j));
			push(x.at(j));
		}
		dbg_printf("\n");
	}

	char str::at(size_t x) {
		return buf[x];
	}

	size_t str::len() {
		return i;
	}

	int_t str::to_i() {
		int_t n = 0;
		int_t m = 1;
		for (size_t x = 0; x < len(); x++) {
			n += m * (at(x) - '0');
			m *= 10;
		}
		return n;
	}

	str from_c(const char *s) {
		auto r = str();
		for (size_t i = 0; i < ::str::len(s); i++) r.push(s[i]);
		return r;
	}	

	str from_i(int_t x) {
		auto r = str();
		auto n = x;
		while (n > 0) {
			r.push((char)('0' + (n % 10)));
			n /= 10;
		}
		return r;
	}
}

namespace chr {
	bool is_alpha(uint8_t x) {
		return x > 63 && x < 91; 
	}

	bool is_digit(uint8_t x) {
		return x > 47 && x < 58;
	}
}
