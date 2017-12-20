#define _BSD_SOURCE
#include <string.h>

void bcopy(void *src, void *dest, size_t n)
{
	memmove(dest, src, n);
}

