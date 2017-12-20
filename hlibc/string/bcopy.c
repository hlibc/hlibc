#define _BSD_SOURCE
#include <string.h>

void bcopy(void *dest, void *src, size_t n)
{
	memmove(dest, src, n);
}

