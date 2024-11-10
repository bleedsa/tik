#ifndef HOST
#include <ti/screen.h>
#include <ti/getcsc.h>
#include <ti/getkey.h>
#endif

#include "str.h"
#include "key.h"
#include "con.h"
#include "lex.h"
#include "prs.h"

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

	void con::back() {
		x -= 1;
	}

	uint8_t con::putc(char c) {
		switch (c) {
			case '\n': nl();  return 1;
			case '\t': tab(); return 1;
			case '\b': back(); return 1;
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

		/* display */
		auto d = [this](prs::node_t x) {
			putc(' ');
			putln(x.to_str());
		};

		switch (c) {
		case '\n': {
			auto l = lex::tape(ln);
			auto v = lex::lex(&l);

			if (v.is_ok()) {
				auto p = prs::tape(v.ok());
				auto n = prs::parse(&p);
				if (n.is_ok()) {
					n.ok().for_each(d);
				} else {
					puts(" !");
					putln(n.err());
				}
			} else {
				puts(" !");
				putln(v.err());
			}

			lns.push(ln);
			ln.clear();
			break;
		}
		case '\v':
			clr();
			break;
		default:
			ln.push(c);
		}

		return c;
	}
}
