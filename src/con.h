#ifndef __CON_H__
#define __CON_H__

#include <stdint.h>

#include "vec.h"
#include "str.h"

namespace con {
	struct con {
		uint8_t x;
		uint8_t y;
		vec::vec<char> ln;
		vec::vec<vec::vec<char>> lns;

		con();

		void clr();
		void nl();
		void tab();
		void back();

		uint8_t putc(char c);
		uint8_t puts(const char *s);
		uint8_t puts(str::str s);
		uint8_t putln(const char *s);
		uint8_t putln(str::str s);

		uint8_t getc();
	};
}

#endif
