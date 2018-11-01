#include "../internal/internal.h"
#include <stdlib.h>

int __flushbuf(int x, FILE *o)
{
	size_t bufsize = BUFSIZ;

	if (o->unbuf) {
		bufsize = 1;
		if (o->buf == NULL) {
			o->lp = o->rp = o->buf = o->unmalloced;
		}
	}
	if (o->buf == NULL && o->unbuf == 0) {
		if ((o->buf = malloc(bufsize)) == NULL) {
			errno = ENOMEM;
			return EOF;
		}
		o->lp = o->rp = o->buf;
	}
	else if (o->write) {
		if (write(o->fd, o->buf, o->rp - o->buf) < 0) {
			o->err = 1;
			return EOF;
		}
	}

	o->rp = o->buf;
	o->len = bufsize;
	if (x != EOF) {
		*o->rp++ = (char)x;
	}
	return x;
}

