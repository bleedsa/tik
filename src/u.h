#ifndef __U_H__
#define __U_H__

#include <stdint.h>
#include <string.h>
#include <ti/error.h>

template<typename T, typename E>
struct result {
	union {
		T o;
		E e;
	};
	bool is_o;

	static result<T, E> mkok(T x) {
		auto r = result();
		r.o = x;
		r.is_o = true;
		return r;
	}

	static result<T, E> mkerr(E x) {
		auto r = result();
		r.e = x;
		r.is_o = false;
		return r;
	}

	result& operator=(const result& x) {
		is_o = x.is_o;
		if (is_o) o = x.o;
		else e = x.e;
		return *this;
	}

	result(const result& x) {
		is_o = x.is_o;
		if (is_o) o = x.o;
		else e = x.e;
	}

	result() {}
	~result() {}

	inline bool is_ok() { return is_o; }

	inline T ok()  { return o; }
	inline E err() { return e; }
};

template<typename T>
struct option {
	union {
		T i;
		uint8_t _n;
	};
	bool e; /* exists */

	option(T x) {
		i = x;
		e = true;
	}

	option() {
		e = false;
	}

	option& operator=(const option& x) {
		e = x.e;
		if (e) i = x.i;
		return *this;
	}

	~option() {
	}

	inline bool is_some() { return e; }
	inline T get() { return i; }
};

template<typename T>
inline bool operator==(const option<T>& x, const option<T>& y) {
	if (x.e == y.e) {
		if (x.e) return x.i == y.i;
		else return true;
	} else return false;
}

using int_t = long int;

static inline auto fatal(uint8_t x) -> void {
	os_ThrowError(x);
}

#endif
