#include <gstdio.h> 

int gfileno(GFILE *fp)
{
	return fp->fd;
} 

