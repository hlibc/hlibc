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
		goto eof; 
	/* read error */
	}else if ((ret == -1)) {
		fp->flags |= _ERR;
		goto eof;
	}

	/* return the first char and incr */
	fp->len = ret - 1;
	return (unsigned char)*fp->rp++;

	/* end of file OR error condition */
	eof:
	fp->len = 0; 
        return EOF;
}

