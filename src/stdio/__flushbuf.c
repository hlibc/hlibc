#include "../internal/internal.h"
#include <stdlib.h>

int __flushbuf(int x, FILE *fp)
{
	size_t bufsize;
	bufsize = (fp->f.unbuf) ? 1 : BUFSIZ;

	if (fp->buf == NULL) {
		if ((fp->buf = malloc(bufsize)) == NULL) {
			return EOF;
		}
		fp->lp = fp->rp = fp->buf;
	}
	else if (fp->f.write) {
		if (write(fp->fd, fp->buf, fp->rp - fp->buf) < 0) {
			fp->f.err = 1;
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

