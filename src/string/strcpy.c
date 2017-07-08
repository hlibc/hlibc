#include <stddef.h> 
#include <string.h>

char *strcpy(char *s, const char *t)
{
        for(;(*s = *t) != '\0'; s++, t++)
                ;
        return s;
}

