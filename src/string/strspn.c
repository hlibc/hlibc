#include <stddef.h>
#include <string.h>

size_t strspn(const char *s1, const char *accept)
{
        size_t i = 0;
        size_t j = 0;

        for ( ; *(s1+i) ; i++)
        {
                for (j = 0 ; *(accept+j) ; j++)
                        if(*(s1+i) == *(accept+j))
                                break;
                if (!*(accept+j))
                        return i;
        }
        return i;
}

