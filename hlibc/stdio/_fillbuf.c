#include "../internal/internal.h"
#include <stdlib.h>

int _fillbuf(FILE *fp)
{
	int bufsize		   = 0;
	static char *buffer = NULL;
	if ((buffer == NULL)) {
		if (!(buffer = calloc(1,BUFSIZ))) {
			return EOF;
		}
	}

	if ((fp->flags & (_READ | _EOF | _ERR)) != _READ)
		return EOF;
	bufsize = (fp->flags & _UNBUF) ? 1 : BUFSIZ;
	if (fp->buf == NULL)
		fp->buf = buffer;
	fp->rp		= fp->buf;
	fp->len		= read(fp->fd, fp->rp, bufsize);

	if (--fp->len < 0) {
		if (fp->len == -1)
			fp->flags |= _EOF;
		else
			fp->flags |= _ERR;
		fp->len = 0;
		fflush(NULL);
		return EOF;
	}

	return (unsigned char)*fp->rp++;
}
