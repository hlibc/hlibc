#include "../internal/internal.h"
#include <stdlib.h>

int _flushbuf(int x, FILE *fp)
{
	int bufsize; 
	bufsize = (fp->flags & _UNBUF) ? 1 : BUFSIZ;

	if (fp->buf == NULL) {
		if ((fp->buf = malloc(bufsize)) == NULL)
                        return EOF;

		fp->lp = fp->rp = fp->buf;
	}
	else if (fp->flags & _WRITE && fp->rp - fp->buf)
	{
		if (write(fp->fd, fp->buf, fp->rp - fp->buf) < 0)
		{
			fp->flags |= _ERR;
			return EOF;
		}
	}

	fp->rp  = fp->buf;
	fp->len = bufsize - 1;
	if (x != EOF)
		*fp->rp++ = (char)x;
	return x;
}
