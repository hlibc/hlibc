#include "internal.h"

size_t _safe_subtraction(size_t a, size_t b)
{
	if (a >= b)
		return a - b;
	return 0;
}

size_t _safe_addition(size_t a, size_t b, size_t lim)
{
	if (lim - a >= b)
		return a + b;
	return 0;
}

size_t _safe_division(size_t i, size_t x)
{
	if (x == 0) {
		return i;
	}
	return i / x;
}

size_t _safe_multiply(size_t i, size_t x, size_t lim)
{
	size_t tmp = _safe_division(lim, i);
	if (tmp >= x) {
		return i * x;
	}
	else if (tmp == 0) {
		return 0;
	}
	return lim;
}
