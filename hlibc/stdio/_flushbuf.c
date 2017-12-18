#include "../internal/internal.h"
#include <stdlib.h>

int _flushbuf(int x, FILE *fp)
{
	int bufsize;
	static char *buffer = NULL;
	if ((buffer == NULL)) {
		if (!(buffer = malloc(BUFSIZ))) {
			return EOF;
		}
	}

	bufsize			   = (fp->flags & _UNBUF) ? 1 : BUFSIZ;

	if (fp->buf == NULL) {
		fp->buf = buffer;
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
