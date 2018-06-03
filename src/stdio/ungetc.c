#include "../internal/internal.h"

int ungetc(int c, FILE *fp)
{
	if (c == EOF)
		return c;
	fp->flags &= ~_EOF;
	fp->ungotten[fp->ungot++] = c;
	return c;
}

