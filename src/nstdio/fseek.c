#include <stdio.h>

/* TODO: Ensure that the FILE struct is completely reset */

int fseek(FILE *fp, long offset, int whence)
{
	int ret = 0;
	_flushbuf(EOF, fp);
	if ((lseek(fp->fd, offset, whence)) == -1)
		ret = -1;
	return ret;
}

