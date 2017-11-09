#include <string.h>

char *index(const char *s, int c)
{
	size_t i = 0;
	while (s[i] != c && s[i] != '\0') {
		++i;
	}
	if (s[i] != c && c != '\0')
		return NULL;
	return i + s;
}

