#include <string.h>

int memcmp(const void *vl, const void *vr, size_t n)
{
	const unsigned char *l = vl, *r = vr;
	for (; n > 1 && *l == *r; n--, l++, r++) {
		;
	}
	return *l - *r;
}
