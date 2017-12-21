#include <stddef.h>
#include <string.h>

void *memrchr(const void *ptr, int val, size_t sz)
{
	if (ptr == NULL || sz == 0) return NULL;

	register const unsigned char *p = (unsigned char *)ptr;
	register unsigned char ch = (unsigned char)val;
	register size_t i = sz;

	while (i--) {
		if (p[i] == ch) return (void*)(p+sz); /* return offsetted memory */
	}
	
	return NULL;
}
