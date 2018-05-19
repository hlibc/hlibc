#include "../internal/internal.h"
#include <stdlib.h>

int _fillbuf(FILE *fp)
{
	size_t bufsize;
	ssize_t ret = 0;

	if ((fp->flags & (_READ | _EOF | _ERR)) != _READ) {
		return EOF;
	}
	bufsize = (fp->flags & _UNBUF) ? 1 : BUFSIZ;
	if (fp->buf == NULL) {
		if ((fp->buf = malloc(bufsize)) == NULL) {
			return EOF;
		}
	}

	fp->rp = fp->buf;
	ret = read(fp->fd, fp->rp, bufsize);

	/* zero length read */
	if (ret == 0) {
		fp->flags |= _EOF;
		fp->len = 1;
		return EOF;
	/* read error */
	}else if ((ret == -1)) {
		fp->flags |= _ERR;
		fp->len = 1;
		return EOF;
	}

	/* return the first char and incr ->rp past it */
	fp->len = ret;
	return (unsigned char)*fp->rp++;
}

