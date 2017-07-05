#include <gstdio.h>

int gsetvbuf(GFILE *fp, char *buf, int mode, size_t size)
{
	fp->buf = buf;
	fp->flags = mode;
	fp->len = size;
	return 0;
}

