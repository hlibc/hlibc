#include "../internal/internal.h"
#include <stdlib.h>

int __flushbuf(int x, FILE *fp)
{
	size_t bufsize = BUFSIZ;

	if (fp->unbuf)
		bufsize = 1;
	if (fp->buf == NULL) {
		if ((fp->buf = malloc(bufsize)) == NULL) {
			return EOF;
		}
		fp->lp = fp->rp = fp->buf;
	}
	else if (fp->write) {
		if (write(fp->fd, fp->buf, fp->rp - fp->buf) < 0) {
			fp->err = 1;
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

