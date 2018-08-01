#include <stddef.h>
#include <string.h>

char *strncat(char *s1, const char *s2, size_t len)
{
	char *dst = s1;
	size_t count = 0;

	while(*dst != '\0') {
		++dst;
	}

	for(; count < len && *s2 != '\0'; ++count) {
		*dst++ = *s2++;
	}

	*dst = '\0';
	return s1;
}
