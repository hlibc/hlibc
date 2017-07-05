#include <gstdio.h> 

int gfeof(GFILE *fp)
{
	if ((fp->flags & _EOF) != 0)
		return 0;
	return 1;
}
