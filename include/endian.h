#ifndef _ENDIAN_H
#define _ENDIAN_H
#include <bits/endian.h>
#include <stdint.h>

#define __LITTLE_ENDIAN 1234
#define __BIG_ENDIAN 4321
#define __PDP_ENDIAN 3412
#define BIG_ENDIAN __BIG_ENDIAN
#define LITTLE_ENDIAN __LITTLE_ENDIAN
#define PDP_ENDIAN __PDP_ENDIAN
#define BYTE_ORDER __BYTE_ORDER

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

#if __BYTE_ORDER == __LITTLE_ENDIAN
#define htobe16(x) __bswap16(x)
#define be16toh(x) __bswap16(x)
#define betoh16(x) __bswap16(x)
#define htobe32(x) __bswap32(x)
#define be32toh(x) __bswap32(x)
#define betoh32(x) __bswap32(x)
#define htobe64(x) __bswap64(x)
#define be64toh(x) __bswap64(x)
#define betoh64(x) __bswap64(x)
#define htole16(x) (uint16_t)(x)
#define le16toh(x) (uint16_t)(x)
#define letoh16(x) (uint16_t)(x)
#define htole32(x) (uint32_t)(x)
#define le32toh(x) (uint32_t)(x)
#define letoh32(x) (uint32_t)(x)
#define htole64(x) (uint64_t)(x)
#define le64toh(x) (uint64_t)(x)
#define letoh64(x) (uint64_t)(x)
#else
#define htobe16(x) (uint16_t)(x)
#define be16toh(x) (uint16_t)(x)
#define betoh16(x) (uint16_t)(x)
#define htobe32(x) (uint32_t)(x)
#define be32toh(x) (uint32_t)(x)
#define betoh32(x) (uint32_t)(x)
#define htobe64(x) (uint64_t)(x)
#define be64toh(x) (uint64_t)(x)
#define betoh64(x) (uint64_t)(x)
#define htole16(x) __bswap16(x)
#define le16toh(x) __bswap16(x)
#define letoh16(x) __bswap16(x)
#define htole32(x) __bswap32(x)
#define le32toh(x) __bswap32(x)
#define letoh32(x) __bswap32(x)
#define htole64(x) __bswap64(x)
#define le64toh(x) __bswap64(x)
#define letoh64(x) __bswap64(x)
#endif

#endif
