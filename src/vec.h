#ifndef __VEC_H__
#define __VEC_H__

#include <stdint.h>
#include <stdlib.h>
#include <debug.h>
#include <string.h>

namespace vec {
	template<typename T>
	struct vec {
		T *buf;
		size_t i;
		size_t sz;

		vec() {
			i = 0;
			sz = 32;
			buf = (T*)malloc(sizeof(T) * sz);
			if (buf == nullptr) dbg_printf("malloc() failed\n");
			else dbg_printf("malloc() ok\n");
		}

		~vec() {
			free(buf);
		}

		vec(const vec& x) {
			i = x.i, sz = x.sz;
			buf = (T*)malloc(sizeof(T) * sz);
			memcpy(buf, x.buf, sizeof(T) * sz);
		}

		vec& operator=(const vec& x) {
			i = x.i, sz = x.sz;
			buf = (T*)malloc(sizeof(T) * sz);
			memcpy(buf, x.buf, sizeof(T) * sz);
			return *this;
		}

		void push(T x) {
			if (i >= sz) {
				sz *= 2;
				buf = (T*)realloc(buf, sizeof(T) * sz);
				if (buf == nullptr) dbg_printf("realloc() failed\n");
				else dbg_printf("realloc() ok\n");
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
