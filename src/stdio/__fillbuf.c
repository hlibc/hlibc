#include "../internal/internal.h"
#include <stdlib.h>

int __fillbuf(FILE *fp)
{
	size_t bufsize;
	ssize_t ret = 0; 
	if (fp->read && fp->eof || fp->err)
		return EOF;
	bufsize = (fp->unbuf) ? 1 : BUFSIZ;
	if (fp->buf == NULL) {
		if ((fp->buf = malloc(bufsize)) == NULL) {
			return EOF;
		}
	}

	fp->rp = fp->buf;
	ret = read(fp->fd, fp->rp, bufsize);

	/* zero length read */
	if (ret == 0) { 
		fp->eof = 1;
		fp->len = 1;
		return EOF;
	/* read error */
	}else if ((ret == -1)) { 
		fp->err = 1;
		fp->len = 1;
		return EOF;
	}

	/* return the first char and incr ->rp past it */
	fp->len = ret;
	return (unsigned char)*fp->rp++;
}

