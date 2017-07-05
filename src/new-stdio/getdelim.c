#include <gstdio.h> 
#include <gstdlib.h>

ssize_t ggetdelim(char **lineptr, size_t *n, char delim, GFILE *fp)
{
        size_t len = 0;
        char *pos = NULL;
        ssize_t ret = -1;
        size_t chunk = BUFSIZ;
        int c = 0;

        if (!*lineptr)
        {
                *n = chunk;
                if (!(*lineptr = malloc (chunk)))
                        return -1;
        }

        len = *n;
        pos = *lineptr;

        for ( ; c != delim ;len--, pos++)
        {
                read (fp->fd, &c, 1);
                if (c == 0 || c == -1)
                        c = EOF;

                if (len == 0)
                {
                        *n += chunk;
                        len = chunk;
                        if (!(*lineptr = realloc (*lineptr, *n)))
                                return ret;
                        pos = *lineptr;
                }

                if (c == EOF )
                {
                        if (pos == *lineptr)
                                return ret;
                        else
                                break;
                }
                *pos = c;
        }

        *pos = '\0';

        ret = pos - (*lineptr);
        return ret;
}

