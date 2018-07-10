#define __BYTE_ORDER 4321
#include <arpa/inet.h>

enum
{
    LE16 = 0x1122ULL,
    BE16 = 0x2211ULL,
    LE32 = 0x11223344ULL,
    BE32 = 0x44332211ULL,
    LE64 = 0x1122334455667788ULL,
    BE64 = 0x8877665544332211ULL
};

int main(void)
{
#ifdef _HAS_HLIBC_ENDIAN
    return
	__le_bswap16(LE16) != LE16 ||
	__le_bswap32(LE32) != LE32 ||
	__le_bswap64(LE64) != LE64 ||
	__be_bswap16(LE16) != BE16 ||
	__be_bswap32(LE32) != BE32 ||
	__be_bswap64(LE64) != BE64 ||
	       htons(LE16) != LE16 ||
	       ntohs(LE16) != LE16 ||
	       htonl(LE32) != LE32 ||
	       ntohl(LE32) != LE32;
#else
    return 0;
#endif
}
