#include <ti/screen.h>
#include <ti/getcsc.h>
#include <ti/getkey.h>

#include "str.h"
#include "key.h"
#include "con.h"

namespace con {
	con::con() {
		x = 0, y = 0;
		clr();
	}

	static char BUF[2] = {0, 0};

	void con::clr() {
		os_ClrHomeFull();
	}

	void con::nl() {
		y += 1;
		x = 0;
	}

	void con::tab() {
		x += 2;
	}

	uint8_t con::putc(char c) {
		switch (c) {
			case '\n': nl();  return 1;
			case '\t': tab(); return 1;
		}

		os_SetCursorPos(y, x);
		x += 1;

		BUF[0] = c;
		return os_PutStrFull(BUF);
	}

	uint8_t con::puts(const char *s) {
		for (; *s; s++) {
			if (putc(*s) != 1) return -1;
		}
		return 1;
	}

	uint8_t con::putln(const char *s) {
		auto r = puts(s);
		nl();
		return r;
	}

	uint8_t con::getc() {
		auto k = os_GetKey();
		auto c = key::map[k];
		putc(c);

		if (c == '\n') {
			char b[vec::SIZE];
			vec::char_vec_to_str(ln, b);
			putln(b);
			ln = vec::vec<char>();
		} else {
			ln.push(c);
		}

		return c;
	}
}
