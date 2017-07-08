#include <stdio.h>

int setvbuf(FILE *fp, char *buf, int mode, size_t size)
{
	fp->buf = buf;
	fp->flags = mode;
	fp->len = size;
	return 0;
}

