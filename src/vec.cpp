#include "vec.h"

namespace vec {
	void char_vec_to_str(vec<char> v, char b[SIZE]) {
		for (size_t i = 0; i < SIZE && v.at(i) != 0; i++) b[i] = v.at(i);
	}
}
