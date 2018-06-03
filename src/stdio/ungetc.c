#include "../internal/internal.h"

int ungetc(int c, FILE *fp)
{
	if (c == EOF)
		return c;
	//fp->flags &= ~_EOF;
	fp->ungot = 1;
	fp->ungotten[0] = c;
	
	return c;
}

