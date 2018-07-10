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
	__bswap16(LE16) != BE16 ||
	__bswap32(LE32) != BE32 ||
	__bswap64(LE64) != BE64;
#else
    return 0;
#endif
}
