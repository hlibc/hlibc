#include "stdio_impl.h"

int fputc(int c, FILE *f)
{ 
	c = putc_unlocked(c, f);
	return c;
}

weak_alias(fputc, putc);
