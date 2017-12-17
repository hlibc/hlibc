#define _BSD_SOURCE
#include <string.h>

size_t strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t len = strnlen(dst, dstsize-1);
	len += strlcpy(dst + len, src, dstsize);
	return len;
}
