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
#include <complex.h>
#include "longdbl.h"

union fshape {
	float value;
	uint32_t bits;
};

union dshape {
	double value;
	uint64_t bits;
};
#if LDBL_MANT_DIG == 53 && LDBL_MAX_EXP == 1024
#elif LDBL_MANT_DIG == 64 && LDBL_MAX_EXP == 16384 && __BYTE_ORDER == __LITTLE_ENDIAN
union ldshape {
        long double f;
        struct {
                uint64_t m;
                uint16_t se;
        } i;
};
#elif LDBL_MANT_DIG == 113 && LDBL_MAX_EXP == 16384 && __BYTE_ORDER == __LITTLE_ENDIAN
union ldshape {
        long double f;
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
#elif LDBL_MANT_DIG == 113 && LDBL_MAX_EXP == 16384 && __BYTE_ORDER == __BIG_ENDIAN
union ldshape {
        long double f;
        struct {
                uint16_t se;
                uint16_t top;
                uint32_t mid;
                uint64_t lo;
        } i;
        struct {
                uint64_t hi;
                uint64_t lo;
        } i2;
};
#else
#error Unsupported long double representation
#endif

/*
#ifdef LDBL_MANT_DIG == 113 && LDBL_MAX_EXP == 16384 && __BYTE_ORDER == __LITTLE_ENDIAN
union ldshape {
        long double f;
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
#elif LDBL_MANT_DIG == 113 && LDBL_MAX_EXP == 16384 && __BYTE_ORDER == __BIG_ENDIAN
union ldshape {
        long double f;
        struct {
                uint16_t se;
                uint16_t top;
                uint32_t mid;
                uint64_t lo;
        } i;
        struct {
                uint64_t hi;
                uint64_t lo;
        } i2;
};
#endif
/*
#define FORCE_EVAL(x) do {                          \
	if (sizeof(x) == sizeof(float)) {           \
		volatile float __x;                 \
		__x = (x);                          \
	} else if (sizeof(x) == sizeof(double)) {   \
		volatile double __x;                \
		__x = (x);                          \
	} else {                                    \
		volatile long double __x;           \
		__x = (x);                          \
	}                                           \
} while(0)

/* Get two 32 bit ints from a double.  */
#define EXTRACT_WORDS(hi,lo,d)                                  \
do {                                                            \
  union dshape __u;                                             \
  __u.value = (d);                                              \
  (hi) = __u.bits >> 32;                                        \
  (lo) = (uint32_t)__u.bits;                                    \
} while (0)

/* Get a 64 bit int from a double.  */
#define EXTRACT_WORD64(i,d)                                     \
do {                                                            \
  union dshape __u;                                             \
  __u.value = (d);                                              \
  (i) = __u.bits;                                               \
} while (0)

/* Get the more significant 32 bit int from a double.  */
#define GET_HIGH_WORD(i,d)                                      \
do {                                                            \
  union dshape __u;                                             \
  __u.value = (d);                                              \
  (i) = __u.bits >> 32;                                         \
} while (0)

/* Get the less significant 32 bit int from a double.  */
#define GET_LOW_WORD(i,d)                                       \
do {                                                            \
  union dshape __u;                                             \
  __u.value = (d);                                              \
  (i) = (uint32_t)__u.bits;                                     \
} while (0)

/* Set a double from two 32 bit ints.  */
#define INSERT_WORDS(d,hi,lo)                                   \
do {                                                            \
  union dshape __u;                                             \
  __u.bits = ((uint64_t)(hi) << 32) | (uint32_t)(lo);           \
  (d) = __u.value;                                              \
} while (0)

/* Set a double from a 64 bit int.  */
#define INSERT_WORD64(d,i)                                      \
do {                                                            \
  union dshape __u;                                             \
  __u.bits = (i);                                               \
  (d) = __u.value;                                              \
} while (0)

/* Set the more significant 32 bits of a double from an int.  */
#define SET_HIGH_WORD(d,hi)                                     \
do {                                                            \
  union dshape __u;                                             \
  __u.value = (d);                                              \
  __u.bits &= 0xffffffff;                                       \
  __u.bits |= (uint64_t)(hi) << 32;                             \
  (d) = __u.value;                                              \
} while (0)

/* Set the less significant 32 bits of a double from an int.  */
#define SET_LOW_WORD(d,lo)                                      \
do {                                                            \
  union dshape __u;                                             \
  __u.value = (d);                                              \
  __u.bits &= 0xffffffff00000000ull;                            \
  __u.bits |= (uint32_t)(lo);                                   \
  (d) = __u.value;                                              \
} while (0)

/* Get a 32 bit int from a float.  */
#define GET_FLOAT_WORD(i,d)                                     \
do {                                                            \
  union fshape __u;                                             \
  __u.value = (d);                                              \
  (i) = __u.bits;                                               \
} while (0)

/* Set a float from a 32 bit int.  */
#define SET_FLOAT_WORD(d,i)                                     \
do {                                                            \
  union fshape __u;                                             \
  __u.bits = (i);                                               \
  (d) = __u.value;                                              \
} while (0)

/* fdlibm kernel functions */ 
double __sin_kernel(double,double,int);
double __cos_kernel(double,double);
double __tan_kernel(double,double,int);
/* polynomial evaluation */
long double __polevll(long double, const long double *, int);
long double __p1evll(long double, const long double *, int);

// FIXME: not needed when -fexcess-precision=standard is supported (>=gcc4.5)
/*
 * Attempt to get strict C99 semantics for assignment with non-C99 compilers.
 */
#if 1
#define STRICT_ASSIGN(type, lval, rval) do {    \
        volatile type __v = (rval);             \
        (lval) = __v;                           \
} while (0)
#else
#define STRICT_ASSIGN(type, lval, rval) ((lval) = (type)(rval))
#endif

/* x + y*I is not supported properly by gcc */
#define cpack(x,y) ((union dcomplex){.a={(x),(y)}}.z)
#define cpackf(x,y) ((union fcomplex){.a={(x),(y)}}.z)
#define cpackl(x,y) ((union lcomplex){.a={(x),(y)}}.z)

int __rem_pio2_large(double *, double *, int, int, int);
int __rem_pio2(double, double *);
double floor(double);
#define _HAS_HLIBC_MATH
double h_cos(double);
#endif
