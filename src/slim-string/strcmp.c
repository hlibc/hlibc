#include <string.h>

int strcmp(const char *s, const char *t)
{
        for ( ; *s == *t; s++, t++)
                if (*s == '\0')
                        return 0;
        return *s - *t;
}
