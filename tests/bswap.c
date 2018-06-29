#include <endian.h>

int main(void)
{
#ifdef _HAS_HLIBC_ENDIAN
    if(__bswap16(0x1122) != 0x2211)
    {
        return 1;
    }

    if(__bswap32(0x11223344) != 0x44332211)
    {
        return 1;
    }

    if(__bswap64(0x1122334455667788ULL) != 0x8877665544332211ULL)
    {
        return 1;
    }
#endif

    return 0;
}
