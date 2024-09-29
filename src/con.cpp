#include <ti/screen.h>
#include <ti/getcsc.h>
#include <ti/getkey.h>

#include "str.h"
#include "key.h"
#include "con.h"
#include "lex.h"

namespace con {
	con::con() {
		x = 0, y = 0;
		ln = vec::vec<char>();
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
			auto v = t.lex();

			if (/*v.is_ok()*/true) {
				//putln(v.ok().at(0).to_str());
				/*
				v.ok().for_each([this](lex::tok x){
					putln(x.to_str());
				});
				*/
				ln = vec::vec<char>();
			} else {
				putln("ERR");
			}
		} else {
			ln.push(c);
		}

		return c;
	}
}
