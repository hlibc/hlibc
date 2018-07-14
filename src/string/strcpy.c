#include <string.h>

char *strcpy(char *d, const char *s)
{
	char *ret = d;
        for (; (*d = *s); d++, s++) {
                ;
        }
        return ret;
}

