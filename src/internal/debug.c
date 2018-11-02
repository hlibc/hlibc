#include "../internal/internal.h"

void __debug(int reset)
{
        static size_t i = 0;
        char s[100] = { 0 };
        char *d = s;
        if (reset == 1)
                i = 0;
        write(2, "level ", 6);
        size_t len = __uint2str(s, i++, 10);
        write(2, s, len);
        write(2, "\n", 1);
}


