#include "../internal/internal.h"
#include <stdlib.h>

int __fillbuf(FILE *o)
{
	size_t bufsize = BUFSIZ;
	ssize_t ret = 0;
	if (o->read && o->eof || o->err)
		return EOF;
	if (o->unbuf)
		bufsize = 1;
	if (o->buf == NULL) {
		if ((o->buf = malloc(bufsize)) == NULL) {
			return EOF;
		}
	}

	o->rp = o->buf;
	ret = read(o->fd, o->rp, bufsize);

	/* zero length read */
	if (ret == 0) { 
		o->eof = 1;
		o->len = 1;
		return EOF;
	/* read error */
	}else if ((ret == -1)) { 
		o->err = 1;
		o->len = 1;
		return EOF;
	}

	/* return the first char and incr ->rp past it */
	o->len = ret;
	return (unsigned char)*o->rp++;
}

