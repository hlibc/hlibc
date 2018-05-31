#include <string.h>

/*
	Copyright 2017, Bao Hexing 'stpncpy'
*/

char *stpncpy(char *dest, const char *src, size_t n)
{
	for (; *src != '\0' && n > 0; --n) {
		*dest++ = *src++;
	}

	while (n-- > 0) {
		*dest++ = '\0';
	}
	*dest = '\0';
	return dest;
}
