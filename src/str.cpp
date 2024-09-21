#include "str.h"

namespace str {
	uint8_t len(const char *s) {
		uint8_t i;
		for (i = 0; *s; i++, s++);
		return i;
	}
}
