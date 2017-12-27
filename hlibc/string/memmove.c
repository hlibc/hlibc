#include <stddef.h>

#include <string.h>

void *memmove(void *to, const void *from, size_t size)
{
	unsigned char *p1 = (unsigned char *)to;
	const unsigned char *p2 = (const unsigned char *)from;

	if (from < to) { // copy from tail to head, in case there is an overlap
		p1 += size;
		p2 += size;
		while (size-- != 0) {
			*--p1 = *--p2;
		}
	}
	else { // copy from head to tail
		while (size-- != 0) {
			*p1++ = *p2++;
		}
	}
	return (to);
}
