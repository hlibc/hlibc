#include <string.h>

char *rindex(const char *s, int c)
{
	int i = 0;
	while (s[i] != '\0')
		++i;
	++i;
	while (s[i] != c && i >= 0)
		--i;
	if (i == 0 && s[i] != c)
		return NULL;
	return i + s;
}
