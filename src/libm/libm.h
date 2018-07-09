/* origin: FreeBSD /usr/src/lib/msun/src/math_private.h */
/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 */

#ifndef _LIBM_H
#define _LIBM_H

#include <stdint.h>
#include <float.h>
#include <math.h>

union fshape {
	float value;
	uint32_t bits;
};

union dshape {
	double value;
	uint64_t bits;
};

#if LDBL_MANT_DIG == 53 && LDBL_MAX_EXP == 1024
/* ( arm v7 32 bit ) FIXME!!! */
union ldshape {
	long double f;
	struct {
		uint32_t m;
		uint8_t se;
	} i;
};
#elif LDBL_MANT_DIG == 64 && LDBL_MAX_EXP == 16384 && __BYTE_ORDER == __LITTLE_ENDIAN
/* i386, x86_64 */
union ldshape {
	long double f;
	struct {
		uint64_t m;
		uint16_t se;
	} i;
};
#elif LDBL_MANT_DIG == 113 && LDBL_MAX_EXP == 16384 && __BYTE_ORDER == __LITTLE_ENDIAN
/* ( arm v8 64 bit aarch64) */
union ldshape {
	long double f;
	/* these would need to be reversed for big endian! */
	struct {
		
		uint64_t lo;
		uint32_t mid;
		uint16_t top;
		uint16_t se;
	} i;
	struct {
		uint64_t lo;
		uint64_t hi;
	} i2;
};
#else
#error Unsupported long double representation
#endif

/* Get two 32 bit ints from a double.	*/
#define EXTRACT_WORDS(hi,lo,d)			\
do {						\
	union dshape __u;			\
	__u.value = (d);			\
	(hi) = __u.bits >> 32;			\
	(lo) = (uint32_t)__u.bits;		\
} while (0)

/* Get the more significant 32 bit int from a double.	*/
#define GET_HIGH_WORD(i,d)			\
do {						\
	union dshape __u;			\
	__u.value = (d);			\
	(i) = __u.bits >> 32;			\
} while (0)

/* Get the less significant 32 bit int from a double.	*/
#define GET_LOW_WORD(i,d)			\
do {						\
	union dshape __u;			\
	__u.value = (d);			\
	(i) = (uint32_t)__u.bits;		\
} while (0)

/* Set a double from two 32 bit ints.	*/
#define INSERT_WORDS(d,hi,lo)					\
do {								\
	union dshape __u;					\
	__u.bits = ((uint64_t)(hi) << 32) | (uint32_t)(lo);	\
	(d) = __u.value;					\
} while (0)

/* Set the more significant 32 bits of a double from an int.	*/
#define SET_HIGH_WORD(d,hi)			\
do {						\
	union dshape __u;			\
	__u.value = (d);			\
	__u.bits &= 0xffffffff;			\
	__u.bits |= (uint64_t)(hi) << 32;	\
	(d) = __u.value;			\
} while (0)

/* Set the less significant 32 bits of a double from an int.	*/
#define SET_LOW_WORD(d,lo)			\
do {						\
	union dshape __u;			\
	__u.value = (d);			\
	__u.bits &= 0xffffffff00000000ull;	\
	__u.bits |= (uint32_t)(lo);		\
	(d) = __u.value;			\
} while (0)

/* fdlibm kernel functions */ 
double __sin_kernel(double,double,int);
double __cos_kernel(double,double);
double __tan_kernel(double,double,int);

// FIXME: not needed when -fexcess-precision=standard is supported (>=gcc4.5)
/*
 * Attempt to get strict C99 semantics for assignment with non-C99 compilers.
 */
#if 1
#define STRICT_ASSIGN(type, lval, rval) do {	\
	volatile type __v = (rval);		\
	(lval) = __v;				\
} while (0)
#else
#define STRICT_ASSIGN(type, lval, rval) ((lval) = (type)(rval))
#endif

int __rem_pio2_large(double *, double *, int, int, int);
int __rem_pio2(double, double *);
double floor(double);
#define _HAS_HLIBC_MATH
double h_cos(double);
#endif
