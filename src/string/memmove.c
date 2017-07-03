#include <stddef.h>

#include <string.h>

void *memmove(void *to, const void *from, size_t size)
{
        unsigned char *p1;
        const unsigned char *p2;

        p1 = (unsigned char *) to;
        p2 = (const unsigned char *) from;

        p2 = p2 + size;

        // Check if there is an overlap or not.
        while (p2 != from && --p2 != to)
                ;


        if (p2 != from)
        {
                p2 = (const unsigned char *) from;
                p2 = p2 + size;
                p1 = p1 + size;

                while (size-- != 0)
                {
                        *--p1 = *--p2;
                }
        }
        else
        {
                while (size-- != 0)
                {
                        *p1++ = *p2++;
                }
        }

        return(to);
}
