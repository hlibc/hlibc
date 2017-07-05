#include <gstdio.h> 

int gferror(GFILE *fp)
{
	if ((fp->flags & _ERR) != 0)
		return 0;
	return 1;
} 

