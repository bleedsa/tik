#ifndef __U_H__
#define __U_H__

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

	~result() {
	}

	inline bool is_ok() { return is_o; }

	inline T ok()  { return o; }
	inline E err() { return e; }
};

#endif
