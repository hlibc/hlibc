#include <stddef.h>
#include <string.h>

int strncmp(const char *s, const char *t, size_t n)
{
	size_t i = 0;

        for ( ; *s == *t && i < n; s++, t++, i++)
                if (*s == '\0')
                        return 0;
        return *s - *t;
}
