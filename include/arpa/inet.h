#ifndef _ARPA_INET_H
#define _ARPA_INET_H
#include <endian.h>

#define htons __le_bswap16
#define ntohs __le_bswap16
#define htonl __le_bswap32
#define ntohl __le_bswap32
#endif
