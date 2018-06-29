#include "internal.h"
#include <limits.h>

/* new API */
int __safe_usub(unsigned long long a, unsigned long long b, unsigned long long *c)
{
	if(a >= b)
	{
		*c = a - b;
		return 0;
	}
	return -1;
}

int __safe_udiv(unsigned long long a, unsigned long long b, unsigned long long *c)
{
	if(b != 0)
	{
		*c = a / b;
		return 0;
	}
	return -1;
}

#if 0
int __safe_sub(size_t a, size_t b, size_t *c)
{
	if (a >= b)
	{
		*c = a - b;
		return 0;
	}
	return -1;
}

int __safe_add(size_t a, size_t b, size_t *c, size_t lim)
{
	size_t tmp = 0;
	int r = __safe_sub(lim, a, &tmp);
	if (r == 0 && tmp >= b)
	{
		*c = a + b;
		return 0;
	}
	return -1;
}

int __safe_div(size_t a, size_t b, size_t *c)
{
	if (b == 0){
		/* divide by zero */
		*c = 0;
		return 0;
	} else if ( a < b )
	{
		*c = 0;
		return 0;
	}
	*c = a / b;
	return 0;
}

int __safe_mul(size_t a, size_t b, size_t *c, size_t lim)
{ 
	size_t tmp = 0;
	__safe_div(lim, a, &tmp);
	if (tmp >= b) {
		*c = a * b;
		return 0;
	}
	else if (tmp == 0) {
		*c = 0;
		return 0;
	}
	return -1;
}
#endif

/* old API */
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
		return i; // divide by zero, return original number
	} else if ( i < x ) {
		return 0; // division will go past zero, return 0
	}
	return i / x; // division fits, perform it
}

size_t _safe_multiply(size_t i, size_t x, size_t lim)
{
	size_t tmp = _safe_division(lim, i);
	if (tmp >= x) { // Division was greater than or equal to x so
		return i * x; // so perform the multiplication.
	}
	else if (tmp == 0) { // The (uinteger) division won't fit so 0 was returned
		return lim; // therefore return the maximum saturation
		//return 0; // therefore return 0 as in multiplication by zero.
	}
	return lim; // return the maximum saturation
}

size_t _safe_upow(size_t i, size_t j)
{
	size_t t = 1;
	while (j--)
		t += _safe_multiply(t, i, ((size_t)-1));
	return t;
}

