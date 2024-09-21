#ifndef __CON_H__
#define __CON_H__

#include <stdint.h>

namespace con {
	struct con {
		uint8_t x;
		uint8_t y;

		con();

		void clr();
		void nl();
		void tab();

		uint8_t putc(char c);
		uint8_t puts(const char *s);
		uint8_t putln(const char *s);

		uint8_t getc();
	};
}

#endif
