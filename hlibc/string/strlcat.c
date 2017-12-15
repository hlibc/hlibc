#include <string.h>

size_t strlcat(char *dst, const char *src, size_t dstsize);
{
	size_t len = strnlen(dst, dstsize-1);
	dstsize -= len;
	return strlcpy(dst + len, src, dstsize);
}
