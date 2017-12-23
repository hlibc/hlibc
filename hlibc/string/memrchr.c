/* Copyright 2017, Mohammad M. Rakib */

#include <stddef.h>
#include <string.h>

void *memrchr(const void *ptr, int val, size_t sz)
{
	if (ptr == NULL || sz == 0) {
		return NULL;
	}

	const unsigned char *p = (unsigned char *)ptr;
	unsigned char ch = (unsigned char)val;

	while (sz--) {
		if (p[sz] == ch) {
			return (void *)(p + sz); /* return offsetted memory */
		}
	}

	return NULL;
}
