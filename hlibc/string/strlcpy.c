#include <string.h>

size_t strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t i = 0;

	for (; i < dstsize-1  && src[i] != '\0' && dst[i] != '\0'; i++) {
		dst[i] = src[i];
	}
	dst[i++] = '\0';

	return i;
}
