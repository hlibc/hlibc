#include "internal.h"
#include <limits.h>

/* new API */
int __safe_sub(intmax_t a, intmax_t b, intmax_t *c)
{
	/*
		-500 - -500 == 0
		A negative minus a negative will always fit
	*/
	if(a < 0 && b < 0 )
	{
		*c = a - b;
		return 0;
	}
	/*
		-500 - +250 == -750
		SIZE_MIN = 1000
		-1000 - -500 == -500
		flip -250
		-500 < -250 so it fits 
		A negative minus a positive needs the positive flipped
		and if the positive as a negative is less than the original
		then it fits
	*/
	if (a < 0 && b > 0)
	{ 
		intmax_t t = INTMAX_MIN - a;
		if (t <= -b)
		{
			*c = a - b;
			return 0;
		}
		return -1;
	}
	return -1;
}

int __safe_mul(intmax_t a, intmax_t b, intmax_t *c)
{
	if(1)
	{
		*c = a * b;
		return 0;
	}
	return -1;
}
int __safe_add(intmax_t a, intmax_t b, intmax_t *c)
{
	if(1)
	{
		*c = a + b;
		return 0;
	}
	return -1;
}

int __safe_div(intmax_t a, intmax_t b, intmax_t *c)
{
	if(b != 0 && b != INTMAX_MIN)
	{
		*c = a / b;
		return 0;
	}
	return -1;
}

int __safe_usub(uintmax_t a, uintmax_t b, uintmax_t *c)
{
	if(a >= b) {
		*c = a - b;
		return 0;
	}
	return -1;
}

int __safe_uadd(uintmax_t a, uintmax_t b, uintmax_t *c, uintmax_t lim)
{
	if (__safe_usub(lim, a, &b) == -1)
		return -1;
	if(a >= b) {
		*c = a + b;
		return 0;
	}
	return -1;
}

int __safe_udiv(uintmax_t a, uintmax_t b, uintmax_t *c)
{
	if(b != 0)
	{
		*c = a / b;
		return 0;
	}
	return -1;
}

int __safe_umul(uintmax_t a, uintmax_t b, uintmax_t *c, uintmax_t lim)
{
	if(a == 0 || lim / a >= b)
	{
		*c = a * b;
		return 0;
	}
	return -1;
}

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

