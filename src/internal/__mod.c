#include <inttypes.h>

int32_t __mod(int32_t a, int32_t b)
{
        if (a < b)
                return a;
        else
                return a - (b * (a / b));
}
