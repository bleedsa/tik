#ifndef __VEC_H__
#define __VEC_H__

#include <stdint.h>
#include <stdlib.h>
#include <debug.h>
#include <string.h>
#include <ti/screen.h>
#include <ti/error.h>

#include "u.h"

namespace vec {
	template<typename T>
	struct vec {
		T *buf;
		size_t i;
		size_t sz;

		vec() {
			i = 0, sz = 1;
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

		void clear() {
			i = 0, sz = 8;
			free(buf);
			buf = (T*)malloc(sizeof(T) * sz);
			if (buf == nullptr) dbg_printf("malloc() failed\n");
			else dbg_printf("malloc() ok\n");
		}

		void push(T x) {
			if (i >= sz) {
				sz += 1;
				buf = (T*)realloc(buf, sizeof(T) * sz);
				if (buf == nullptr) {
					dbg_printf("realloc() failed\n");
					fatal(OS_E_MEMORY);
				} else dbg_printf("realloc() ok\n");
			}

			buf[i] = x;
			i++;
		}

		option<T> at(size_t idx) {
			if (idx < i) {
				return option<T>(buf[idx]);
			} else {
				return option<T>();
			}
		}

		inline size_t size() {
			return sz;
		}

		inline size_t len() {
			return i;
		}

		template<typename F>
		void for_each(F f) {
			for (size_t j = 0; j < i; j++) {
				f(buf[j]);
			}
		}
	};
}

#endif
