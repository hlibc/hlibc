#ifndef _LDHACK_H
#define _LDHACK_H

#include <float.h>
#include <stdint.h>
// FIXME: hacks to make freebsd+openbsd long double code happy
// union and macros for freebsd
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

#endif
