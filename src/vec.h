#ifndef __VEC_H__
#define __VEC_H__

#include <stdint.h>

namespace vec {
	const size_t SIZE = 1024;

	template<typename T>
	struct vec {
		T buf[SIZE];
		size_t i;

		vec() {
			i = 0;
		}

		void push(T x) {
			if (i < SIZE) {
				buf[i] = x;
				i++;
			}
		}

		T at(size_t idx) {
			return buf[idx];
		}
	};

	void char_vec_to_str(vec<char> v, char b[SIZE]);
}

#endif
