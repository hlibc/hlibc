/* Copyright 2017, Mohammad M. Rakib */

#include <string.h>

char *strstr(const char *haystack, const char *needle)
{
	const char *h = haystack;
	const char *n = needle;

	while (*haystack) {
		while (*n++ && (*h == *n)) h++;

		if (!*n) return (char *)haystack;

		haystack++;
		h = haystack;
		n = needle;
	}

	return NULL;
}
