#include <stddef.h>
#include <string.h>

int strncmp(const char *s, const char *t, size_t n)
{
	size_t i = 0;
	for (; n && i<(n - 1) && *s == *t ; s++, t++, i++) {
		if (*s == '\0' || *s == 0 || *t == 0) {
			break;
		}
	}
	return *s - *t;
}

