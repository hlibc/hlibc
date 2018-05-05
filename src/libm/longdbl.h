#ifndef _LDHACK_H
#define _LDHACK_H

#include <float.h>
#include <stdint.h>

#if LDBL_MANT_DIG == 53 && LDBL_MAX_EXP == 1024
#elif LDBL_MANT_DIG == 64 && LDBL_MAX_EXP == 16384
union ldshape {
	long double value;
	struct {
		uint64_t m;
		uint16_t exp:15;
		uint16_t sign:1;
		uint16_t pad;
	} bits;
};
#elif LDBL_MANT_DIG == 113 && LDBL_MAX_EXP == 16384
union ldshape {
	long double value;
	struct {
		uint64_t mlo;
		uint64_t mhi:48;
		uint16_t exp:15;
		uint16_t sign:1;
	} bits;
};
#else
#error Unsupported long double representation
#endif


// FIXME: hacks to make freebsd+openbsd long double code happy

// union and macros for freebsd


union IEEEl2bits {
	long double e;
	struct {
		uint32_t manl:32;
		uint32_t manh:32;
		uint32_t exp:15;
		uint32_t sign:1;
		uint32_t pad:16;
	} bits;
	struct {
		uint64_t man:64;
		uint32_t expsign:16;
		uint32_t pad:16;
	} xbits;
};

#if LDBL_MANT_DIG == 64 && LDBL_MAX_EXP == 16384
#define LDBL_MANL_SIZE 32
#define LDBL_MANH_SIZE 32
#define LDBL_NBIT (1ull << LDBL_MANH_SIZE-1)
#undef LDBL_IMPLICIT_NBIT
#define mask_nbit_l(u) ((u).bits.manh &= ~LDBL_NBIT)

#elif LDBL_MANT_DIG == 113 && LDBL_MAX_EXP == 16384

#define LDBL_MANL_SIZE 64
#define LDBL_MANH_SIZE 48
#define LDBL_NBIT (1ull << LDBL_MANH_SIZE)
#define LDBL_IMPLICIT_NBIT 1
#define mask_nbit_l(u)

#endif


// macros for openbsd

#define GET_LDOUBLE_WORDS(se,mh,ml, f) do{ \
	union IEEEl2bits u; \
	u.e = (f); \
	(se) = u.xbits.expsign; \
	(mh) = u.bits.manh; \
	(ml) = u.bits.manl; \
}while(0)

#define SET_LDOUBLE_WORDS(f,  se,mh,ml) do{ \
	union IEEEl2bits u; \
	u.xbits.expsign = (se); \
	u.bits.manh = (mh); \
	u.bits.manl = (ml); \
	(f) = u.e; \
}while(0)

#define GET_LDOUBLE_EXP(se, f) do{ \
	union IEEEl2bits u; \
	u.e = (f); \
	(se) = u.xbits.expsign; \
}while(0)

#define SET_LDOUBLE_EXP(f, se) do{ \
	union IEEEl2bits u; \
	u.e = (f); \
	u.xbits.expsign = (se); \
	(f) = u.e; \
}while(0)

#endif
