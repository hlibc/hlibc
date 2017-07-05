#include <stddef.h> 
#include <string.h> 
#include <stdlib.h>

char *strndup(const char *s, size_t lim)
{
        char *ret;
        size_t len = strnlen(s, lim) + 1;
        ret = malloc(len);
        memcpy(ret, s, len);
        ret[len] = 0;
        return ret;
}

