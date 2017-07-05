#include <gstdio.h> 
#include <gstdlib.h>

ssize_t ggetline(char **lineptr, size_t *n, GFILE *fp)
{
        return ggetdelim(lineptr, n, '\n', fp);
}
