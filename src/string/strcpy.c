#include <stddef.h>
#include <string.h>

char *strcpy(char *s, const char *t)
{
	for (; (*s = *t); s++, t++) {
		;
	}
	return s;
}
