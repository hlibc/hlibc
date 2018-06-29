#include "bswap.h"

int main(void)
{
#ifdef _HAS_HLIBC_ENDIAN
    if(__bswap16(LE16) != BE16)
    {
        return 1;
    }

    if(__bswap32(LE32) != BE32)
    {
        return 1;
    }

    if(__bswap64(LE64) != BE64)
    {
        return 1;
    }
#endif

    return 0;
}
