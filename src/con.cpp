#ifndef HOST
#include <ti/screen.h>
#include <ti/getcsc.h>
#include <ti/getkey.h>
#endif

#include "str.h"
#include "key.h"
#include "con.h"
#include "lex.h"

namespace con {
	con::con() {
		x = 0, y = 0;
		ln = vec::vec<char>();
		lns = vec::vec<vec::vec<char>>();
		clr();
	}

	static char BUF[2] = {0, 0};

	void con::clr() {
		os_ClrHomeFull();
	}

	void con::nl() {
		y += 1;
		x = 0;

		if (y > 9) {
			y = 0;
			clr();
		}
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

	uint8_t con::puts(str::str s) {
		for (size_t i = 0; i < s.len(); i++) {
			if (putc(s.at(i)) != 1) return -1;
		}
		return 1;
	}

	uint8_t con::putln(const char *s) {
		auto r = puts(s);
		nl();
		return r;
	}

	uint8_t con::putln(str::str s) {
		auto r = puts(s);
		nl();
		return r;
	}

	uint8_t con::getc() {
		auto k = os_GetKey();
		auto c = key::map[k];
		putc(c);

		if (c == '\n') {
			auto t = lex::tape(ln);
			auto v = lex::exprs(&t);
			/* display */
			auto d = [this](lex::tok_t x) {
				auto e = x.to_str();
				if (e.is_ok()) {
					putc(' ');
					putln(e.ok());
				} else {
					putln(e.err());
				}
			};

			if (v.is_ok()) {
				v.ok().for_each(d);
			} else {
				putln(v.err());
			}

			lns.push(ln);
			ln.clear();
		} else {
			ln.push(c);
		}

		return c;
	}
}
