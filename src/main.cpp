#include "con.h"

int main(void) {
	auto c = con::con();
	c.putln("tik. (c)skylar bleed 2024.");
	c.putln("version 0.0.2");

	while (c.getc() != '\0');
}
