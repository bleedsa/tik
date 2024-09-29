#include "str.h"
#include "con.h"
#include <stdlib.h>
#include <string.h>

namespace str {
	uint8_t len(const char *s) {
		uint8_t i;
		for (i = 0; *s; i++, s++);
		return i;
	}

	str::str() {
		i = 0;
		sz = 8;
		buf = (char*)malloc(sizeof(char) * sz);
		if (buf == NULL) os_PutStrLine("null");
		memset(buf, 0, sizeof(char) * sz);
	}

	str::~str() {
		free(buf);
	}

	void str::push(char x) {
		if (i >= sz) {
			sz *= 2;
			buf = (char*)realloc(buf, sizeof(char) * sz);
			if (buf == NULL) os_PutStrLine("null");
			memset(buf, 0, sizeof(char) * sz);
		}

		buf[i] = x;
		i++;
	}

	char str::at(size_t x) {
		return buf[x];
	}

	size_t str::len() {
		return i;
	}

	str from_c(char *s) {
		auto r = str();
		for (; *s; s++) r.push(*s);
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
