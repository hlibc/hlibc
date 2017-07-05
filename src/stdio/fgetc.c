#include "stdio_impl.h"

int fgetc(FILE *f)
{
	int c; 
	c = getc_unlocked(f);
	return c;
}

weak_alias(fgetc, getc);
