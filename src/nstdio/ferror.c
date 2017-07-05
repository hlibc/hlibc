#include <stdio.h> 

int ferror(FILE *fp)
{
	if ((fp->flags & _ERR) != 0)
		return 0;
	return 1;
} 

