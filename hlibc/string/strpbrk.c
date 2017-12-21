/* Copyright 2017, Mohammad M. Rakib */

#include <string.h>

char *strpbrk(char *haystack, char *needles)
{
	if (haystack == NULL || needles == NULL) return NULL;

	size_t hlen = strlen(haystack);
	size_t nlen = strlen(needles);
	int firstpos;

	for (int i = 0; i < hlen; i++) {
		for (int j = 0; j < nlen; j++) {
			if (haystack[i] == needles[j]) firstpos = j;
		}
	}

	return (haystack + firstpos);
}
