#ifndef _MATH_H
#define _MATH_H

#ifdef __cplusplus
extern "C" {
#endif

#define __NEED_float_t
#define __NEED_double_t
#define __NEED___uint16_t
#define __NEED___uint32_t
#define __NEED___uint64_t
#include <bits/alltypes.h>

#if 100*__GNUC__+__GNUC_MINOR__ >= 303
#define NAN       __builtin_nanf("")
#define INFINITY  __builtin_inff()
#else
#define NAN       (0.0f/0.0f)
#define INFINITY  1e40f
#endif

#define HUGE_VALF INFINITY
#define HUGE_VAL  ((double)INFINITY)
#define HUGE_VALL ((long double)INFINITY)

#define MATH_ERRNO  1
#define MATH_ERREXCEPT 2
#define math_errhandling 2

#define FP_ILOGBNAN (-1-(int)(((unsigned)-1)>>1))
#define FP_ILOGB0 FP_ILOGBNAN

#define FP_NAN       0
#define FP_INFINITE  1
#define FP_ZERO      2
#define FP_SUBNORMAL 3
#define FP_NORMAL    4

int __fpclassify(double);
int __fpclassifyf(float);
int __fpclassifyl(long double);

union __float_repr { float __f; __uint32_t __i; };
union __double_repr { double __f; __uint64_t __i; };

#define __FLOAT_BITS(f) (((union __float_repr){ (float)(f) }).__i)
#define __DOUBLE_BITS(f) (((union __double_repr){ (double)(f) }).__i)

#define fpclassify(x) ( \
	sizeof(x) == sizeof(float) ? __fpclassifyf(x) : \
	sizeof(x) == sizeof(double) ? __fpclassify(x) : \
	__fpclassifyl(x) )

#define isinf(x) ( \
	sizeof(x) == sizeof(float) ? (__FLOAT_BITS(x) & 0x7fffffff) == 0x7f800000 : \
	sizeof(x) == sizeof(double) ? (__DOUBLE_BITS(x) & (__uint64_t)-1>>1) == (__uint64_t)0x7ff<<52 : \
	__fpclassifyl(x) == FP_INFINITE)

#define isnan(x) ( \
	sizeof(x) == sizeof(float) ? (__FLOAT_BITS(x) & 0x7fffffff) > 0x7f800000 : \
	sizeof(x) == sizeof(double) ? (__DOUBLE_BITS(x) & (__uint64_t)-1>>1) > (__uint64_t)0x7ff<<52 : \
	__fpclassifyl(x) == FP_NAN)

#define isnormal(x) ( \
	sizeof(x) == sizeof(float) ? ((__FLOAT_BITS(x)+0x00800000) & 0x7fffffff) >= 0x01000000 : \
	sizeof(x) == sizeof(double) ? ((__DOUBLE_BITS(x)+((__uint64_t)1<<52)) & (__uint64_t)-1>>1) >= (__uint64_t)1<<53 : \
	__fpclassifyl(x) == FP_NORMAL)

#define isfinite(x) ( \
	sizeof(x) == sizeof(float) ? (__FLOAT_BITS(x) & 0x7fffffff) < 0x7f800000 : \
	sizeof(x) == sizeof(double) ? (__DOUBLE_BITS(x) & (__uint64_t)-1>>1) < (__uint64_t)0x7ff<<52 : \
	__fpclassifyl(x) > FP_INFINITE)

int __signbit(double);
int __signbitf(float);
int __signbitl(long double);

#define signbit(x) ( \
	sizeof(x) == sizeof(float) ? (int)(__FLOAT_BITS(x)>>31) : \
	sizeof(x) == sizeof(double) ? (int)(__DOUBLE_BITS(x)>>63) : \
	__signbitl(x) )

#define isunordered(x,y) (isnan((x)) ? ((void)(y),1) : isnan((y)))

#if __STDC_VERSION__ >= 199901L
inline
#endif
static int __isrel(long double __x, long double __y, int __rel)
{
	if (isunordered(__x, __y)) return 0;
	if (__rel==-2) return __x < __y;
	if (__rel==2) return __x > __y;
	if (__rel==-1) return __x <= __y;
	if (__rel==1) return __x >= __y;
	return __x != __y;
}

#define isless(x,y) __isrel((x), (y), -2)
#define islessequal(x,y) __isrel((x), (y), -1)
#define islessgreater(x,y) __isrel((x), (y), 0)
#define isgreaterequal(x,y) __isrel((x), (y), 1)
#define isgreater(x,y) __isrel((x), (y), 2)

double      cos(double);
double      fabs(double);
long double frexpl(long double value, int *);
double      pow(double, double);
double      scalbn(double, int);
double      sin(double);
double      sqrt(double);

#if defined(_XOPEN_SOURCE) || defined(_GNU_SOURCE)
#define MAXFLOAT        3.40282347e+38F
#define M_E             2.7182818284590452354   /* e */
#define M_LOG2E         1.4426950408889634074   /* log_2 e */
#define M_LOG10E        0.43429448190325182765  /* log_10 e */
#define M_LN2           0.69314718055994530942  /* log_e 2 */
#define M_LN10          2.30258509299404568402  /* log_e 10 */
#define M_PI            3.14159265358979323846  /* pi */
#define M_PI_2          1.57079632679489661923  /* pi/2 */
#define M_PI_4          0.78539816339744830962  /* pi/4 */
#define M_1_PI          0.31830988618379067154  /* 1/pi */
#define M_2_PI          0.63661977236758134308  /* 2/pi */
#define M_2_SQRTPI      1.12837916709551257390  /* 2/sqrt(pi) */
#define M_SQRT2         1.41421356237309504880  /* sqrt(2) */
#define M_SQRT1_2       0.70710678118654752440  /* 1/sqrt(2) */

extern int signgam;

#ifdef __cplusplus
}
#endif

#endif
