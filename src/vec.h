#ifndef __VEC_H__
#define __VEC_H__

#include <stdint.h>
#include <stdlib.h>
#include <ti/screen.h>

namespace vec {
	template<typename T>
	struct vec {
		T *buf;
		size_t i;
		size_t sz;

		vec() {
			i = 0;
			sz = 8;
			buf = (T*)malloc(sizeof(T) * sz);

			if (buf == NULL) {
				os_PutStrLine("null");
			} else os_PutStrLine("ok");
		}

		~vec() {
			free(buf);
		}

		void push(T x) {
			if (i >= sz) {
				sz *= 2;
				buf = (T*)realloc(buf, sizeof(T) * sz);
				if (buf == NULL) os_PutStrLine("null");
				else os_PutStrLine("reok");
			}

			buf[i] = x;
			i++;
		}

		T at(size_t idx) {
			return buf[idx];
		}

		inline size_t size() {
			return sz;
		}

		template<typename F>
		void for_each(F f) {
			for (size_t j = 0; j < i; j++) f(at(j));
		}
	};
}

#endif
