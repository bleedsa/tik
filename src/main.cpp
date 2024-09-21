#include <stdint.h>
#include <ti/screen.h>
#include <ti/getcsc.h>

#include "con.h"

int main(void) {
	auto c = con::con();

	c.putln("tik. (c)skylar bleed 2024.");

	do {

		auto x = c.getc();
		c.putc(x);
	} while (true);

}
