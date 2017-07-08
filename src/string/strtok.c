#include <stddef.h>

#include <string.h>

char *strtok(char *s, const char *delim)
{

        char *token;
        char *span;
        static char *last;

        int c;
        int hold;

        if (s == NULL)
        {
                s = last;
                if (s == NULL)
                        return NULL;
        }


        c = *s++;

        for (span = (char *)delim; (hold = *span++) != 0;)
        {
                if (c == hold)
                {
                        c = *s++;
                        span = (char *)delim;
                }
        }

        if (c == 0)
                return (last = NULL);

        token = s - 1;

        while ( 1 )
        {
                c = *s++;
                span = (char *)delim;
                do {
                        if ((hold = *span++) == c)
                        {
                                if (c == 0)
                                        s = NULL;
                                else
                                        s[-1] = 0;
                                last = s;
                                return (token);
                        }
                } while (hold != 0);
        }
}

