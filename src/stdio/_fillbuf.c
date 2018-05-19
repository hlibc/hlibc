#include "../internal/internal.h"
#include <stdlib.h>
int _fillbuf(FILE *fp)
{
	size_t bufsize;

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
	fp->len = read(fp->fd, fp->rp, bufsize);

	if (--fp->len < 0) {
		if (fp->len == -1) {
			fp->flags |= _EOF;
		}
		else {
			fp->flags |= _ERR;
		}
		fp->len = 0;
		//fflush(fp);
		return EOF;
	}

	return (unsigned char)*fp->rp++;
}
