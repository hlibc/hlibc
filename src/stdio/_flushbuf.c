#include "../internal/internal.h"
#include <stdlib.h>

int _flushbuf(int x, FILE *fp)
{
	size_t bufsize;
	bufsize = (fp->flags & _UNBUF) ? 1 : BUFSIZ;

	if (fp->buf == NULL) {
		if ((fp->buf = malloc(bufsize)) == NULL) {
			return EOF;
		}
		fp->lp = fp->rp = fp->buf;
	}
	else if (fp->flags & _WRITE) {
		if (write(fp->fd, fp->buf, fp->rp - fp->buf) < 0) {
			fp->flags |= _ERR;
			return EOF;
		}
	}

	fp->rp = fp->buf;
	fp->len = bufsize;
	if (x != EOF) {
		*fp->rp++ = (char)x;
	}
	return x;
}

