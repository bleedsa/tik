#ifndef __U_H__
#define __U_H__

#include <string.h>

template<typename T, typename E>
struct result {
	union {
		T o;
		E e;
	};
	bool is_o;

	result(T x) {
		o = x;
		is_o = true;
	}

	result(E x) {
		e = x;
		is_o = false;
	}

	result& operator=(const result& x) {
		is_o = x.is_o;
		if (is_o) o = x.o;
		else e = x.e;
	}

	~result() {
	}

	inline bool is_ok() { return is_o; }

	inline T ok()  { return o; }
	inline E err() { return e; }
};

#endif
