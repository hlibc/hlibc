#include <string.h>

void *memccpy(void *dest, const void *src, int c, size_t n)
{
	const char *source = src;
	char *destination = dest;
	size_t i;

	for (i = 0; i < n; ++i)
	{
		if (source[i] != c)
			destination[i] = source[i];
		else
			break;
	}
	if (n == ++i)
		return NULL;

	return destination + i;
}
