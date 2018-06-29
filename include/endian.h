#ifndef _ENDIAN_H
#define _ENDIAN_H
#include <bits/endian.h>
#include <stdint.h>

#define __LITTLE_ENDIAN 1234
#define __BIG_ENDIAN 4321
#define __PDP_ENDIAN 3412

#if __STDC_VERSION__ >= 199901L
inline
#endif
static uint16_t __bswap16(uint16_t x)
{
    return
        ((x & 0xFF00) >> 8) |
        ((x & 0x00FF) << 8);
}

#if __STDC_VERSION__ >= 199901L
inline
#endif
static uint32_t __bswap32(uint32_t x)
{
    return
        ((x & 0xFF000000) >> 24) |
        ((x & 0x00FF0000) >>  8) |
        ((x & 0x0000FF00) <<  8) |
        ((x & 0x000000FF) << 24);
}

#if __STDC_VERSION__ >= 199901L
inline
#endif
static uint64_t __bswap64(uint64_t x)
{
    return
        ((x & 0xFF00000000000000ULL) >> 56) |
        ((x & 0x00FF000000000000ULL) >> 40) |
        ((x & 0x0000FF0000000000ULL) >> 24) |
        ((x & 0x000000FF00000000ULL) >>  8) |
        ((x & 0x00000000FF000000ULL) <<  8) |
        ((x & 0x0000000000FF0000ULL) << 24) |
        ((x & 0x000000000000FF00ULL) << 40) |
        ((x & 0x00000000000000FFULL) << 56);
}

#if __STDC_VERSION__ >= 199901L
inline
#endif
static uint16_t __le_bswap16(uint16_t x)
{
#if __BYTE_ORDER == __LITTLE_ENDIAN
    return __bswap16(x);
#else
    return x;
#endif
}

#if __STDC_VERSION__ >= 199901L
inline
#endif
static uint32_t __le_bswap32(uint32_t x)
{
#if __BYTE_ORDER == __LITTLE_ENDIAN
    return __bswap32(x);
#else
    return x;
#endif
}

#if __STDC_VERSION__ >= 199901L
inline
#endif
static uint64_t __le_bswap64(uint64_t x)
{
#if __BYTE_ORDER == __LITTLE_ENDIAN
    return __bswap64(x);
#else
    return x;
#endif
}

#if __STDC_VERSION__ >= 199901L
inline
#endif
static uint16_t __be_bswap16(uint16_t x)
{
#if __BYTE_ORDER == __BIG_ENDIAN
    return __bswap16(x);
#else
    return x;
#endif
}

#if __STDC_VERSION__ >= 199901L
inline
#endif
static uint32_t __be_bswap32(uint32_t x)
{
#if __BYTE_ORDER == __BIG_ENDIAN
    return __bswap32(x);
#else
    return x;
#endif
}

#if __STDC_VERSION__ >= 199901L
inline
#endif
static uint64_t __be_bswap64(uint64_t x)
{
#if __BYTE_ORDER == __BIG_ENDIAN
    return __bswap64(x);
#else
    return x;
#endif
}

#if defined(_GNU_SOURCE) || defined(_BSD_SOURCE)
#define BIG_ENDIAN __BIG_ENDIAN
#define LITTLE_ENDIAN __LITTLE_ENDIAN
#define PDP_ENDIAN __PDP_ENDIAN
#define BYTE_ORDER __BYTE_ORDER

#define htobe16 __le_bswap16
#define be16toh __le_bswap16
#define betoh16 __le_bswap16
#define htobe32 __le_bswap32
#define be32toh __le_bswap32
#define betoh32 __le_bswap32
#define htobe64 __le_bswap64
#define be64toh __le_bswap64
#define betoh64 __le_bswap64
#define htole16 __be_bswap16
#define le16toh __be_bswap16
#define letoh16 __be_bswap16
#define htole32 __be_bswap32
#define le32toh __be_bswap32
#define letoh32 __be_bswap32
#define htole64 __be_bswap64
#define le64toh __be_bswap64
#define letoh64 __be_bswap64
#endif

#endif
