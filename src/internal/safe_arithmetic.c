#include "internal.h"
#include <limits.h>

/*
it's unsafe if the divident is INT_MIN and the divisor is -1
*/

int __safe_sub(intmax_t a, intmax_t b, intmax_t *c)
{
	/*
		(-a - -b)
		-500 - -500 == 0
		A negative minus a negative will always fit
		as it always seeks to transform the negative 
		operand toward and over 0
	*/
	if(a < 0 && b < 0 ) {
		*c = a - b;
		return 0;
	}

	/*
		(-a - b)
		 a = -500, b = +250, lim = 1000, t = unknown 
		1) -500 - +250 = -750
		   a - b = -750

		2) -1000 - -500 = -500
		   lim - b = t
		
		3) flip -250
		   b = -b
		
		4) if -500 < -250 so it fits 
		   if t < b

		A negative minus a positive needs the positive flipped
		and if the positive as a negative is less than the result
		of the minimum minus the left operand then it fits
	*/
	if (a < 0 && b > 0) {
		if ((INTMAX_MIN - a) <= -b)
		{
			*c = a - b;
			return 0;
		}
		return -1;
	}

	/*
		(a + b)
		a and b are positive so subtractions will always fit
	*/
	if (a > 0 && b > 0) {
		*c = a - b;
		return 0;
		
	}
	
	/*
		(a - -b)
		a is positive and b is negative so subtractions have the properties 
		of addition and can use the unsigned variant
	*/
	if (a > 0 && b < 0) {
		return __safe_uadd(a, b, (uintmax_t *)c, INTMAX_MAX);
	}
		
	return -1;
}
int __safe_add(intmax_t a, intmax_t b, intmax_t *c)
{
	/*
		(a + b)
		this is the conventional case so call out to the unsigned API
	*/
	if (a > 0 && b > 0)
		return __safe_uadd(a, b, c, INTMAX_MAX); 
		
	/*
		(-a + -b)
		-100 + -100 == -200
		this will cause overflow and needs a check!

		-500 + -250 and lim is -1000
		-1000  - - 500 == -500
		-500 < - 250 ... so it fits
		else it is an overflow
	*/
	if (a < 0 && b < 0) {
		if (INTMAX_MIN - a < b ) {
			*c = a + b;
			return 0;
		}
		return -1;
	}

	/*
		(a + -b)
		100 + -900 == -800
		this should always fit as long as -b is *valid*
	*/
	/*
		(-a + b)
		-100 + 1000 == 900
		a negative plus a postive will always fit 
	*/
	*c = a + b;
	return 0;
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

int __safe_mul(intmax_t a, intmax_t b, intmax_t *c)
{
	/*
		(a * b) == c 
		normal case, check with division
	*/
	/*
		(a * -b) == -c
		100 * -300
		-1000 / 100 == -10 
		-lim / a == -x
		if (b > x)
		then a * -b fits into c (negative -c)
	*/
	if (a > 0 && b < 0)
	{
		intmax_t t = INTMAX_MIN / a;
		if (b > t)
		{
			*c = a * b;
			return 0;
		}
		return -1;
	}
	/*
		(-a * -b) == c

		MIN / -a == x
		x will go -a time into MIN
		so if b > -x
		then a * b will fit
	*/
	if (a < 0 && b < 0)
	{
		intmax_t t = INTMAX_MIN / a;
		if (b > -t)
		{
			*c = a * b;
			return 0;
		}
		return -1;
	}
	/*
		(-a * b) == -c
	*/
	if(1)
	{
		*c = a * b;
		return 0;
	}
	return -1;
}
/* define the bodies of the unsigned safe arithmetic functions as macros */
#define __safe_usubinter \
	if(a >= b) { \
		*c = a - b; \
		return 0;  \
	} \
	return -1;

#define __safe_umulinter \
	if(a == 0 || lim / a >= b) \
	{ \
		*c = a * b; \
		return 0; \
	} \
	return -1;

#define __safe_udivinter \
	if(b != 0) \
	{ \
		*c = a / b; \
		return 0; \
	} \
	return -1; \

#define __safe_uaddinter \
	if(lim - a >= b) { \
		*c = a + b; \
		return 0; \
	} \
	return -1;

/* apply the unsigned safe macros to various size types */
int __safe_usub(uintmax_t a, uintmax_t b, uintmax_t *c)
{ 
	__safe_usubinter;
}

int __safe_uadd(uintmax_t a, uintmax_t b, uintmax_t *c, uintmax_t lim)
{ 
	__safe_uaddinter;
}

int __safe_udiv(uintmax_t a, uintmax_t b, uintmax_t *c)
{
	__safe_udivinter;
}

int __safe_umul(uintmax_t a, uintmax_t b, uintmax_t *c, uintmax_t lim)
{
	__safe_umulinter;
}

int __safe_usub_sz(size_t a, size_t b, size_t *c)
{
	__safe_usubinter;
}

int __safe_uadd_sz(size_t a, size_t b, size_t *c, size_t lim)
{
	__safe_uaddinter;
}

int __safe_udiv_sz(size_t a, size_t b, size_t *c)
{
	__safe_udivinter;
}

int __safe_umul_sz(size_t a, size_t b, size_t *c, size_t lim)
{
	__safe_umulinter;
}

