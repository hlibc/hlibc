#include <stddef.h> 
#include <string.h>

size_t strnlen(const char *s, size_t lim)
{
        size_t i = 0;
        while ( s[i] != '\0' && i < lim)
                ++i;
        return i;
}

