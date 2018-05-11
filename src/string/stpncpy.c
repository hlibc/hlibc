#include <string.h>

char *stpncpy(char *dest, const char *src, size_t n)
{
	char *p;
	for (; *src != '\0' && n > 0; --n) {
		*dest++ = *src++;
	}

	p = dest;
	while (n-- > 0) {
		*p++ = '\0';
	}
	*dest = '\0';
	return dest;
}
