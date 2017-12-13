#include <string.h>

void swab(const void restrict *_src, void restrict *_dest, ssize_t)
{
	const char *src = src;
	char *des = dest;

	for ( ; n>0; dest+=2, src+=2, n-=2) {
		dest[0] = src[1];
		dest[1] = src[0];
	}
}
