#include <stddef.h>
#include <string.h>

/* Copyright (c) 2017, Iain Hill */

void *memchr(const void *str, int c, size_t n)
{
	size_t i = 0;
	const unsigned char *s = str;

	for (; i < n; i++, s++) {
		if (*s == c) {
			return (unsigned char *)s;
		}
	}
	return NULL;
}
