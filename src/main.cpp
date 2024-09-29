#include <stdint.h>
#include <ti/screen.h>
#include <ti/getcsc.h>

#include "con.h"
#include "vec.h"
#include "str.h"

int main(void) {
	auto c = con::con();
	c.putln("tik. (c)skylar bleed 2024.");
	c.putln("version 0.0.1");

	while (c.getc() != '\v');
}
