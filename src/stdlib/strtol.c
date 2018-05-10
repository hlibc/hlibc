#include <ctype.h>
#include <stdlib.h>

long strtol(const char *s, char **end, int base)
{
	return strtoll(s, end, base);
}

