#include <stdint.h>
#include <ti/screen.h>
#include <ti/getcsc.h>

#include "con.h"
#include "vec.h"

int main(void) {
	auto c = con::con();
	c.putln("tik. (c)skylar bleed 2024.");

	while (true) c.getc();
}
