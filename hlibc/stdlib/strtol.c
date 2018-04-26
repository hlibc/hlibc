#include <ctype.h>
#include <stdlib.h>

long strtol(const char *nptr, char **endptr, int base)
{
	return strtoll(nptr, endptr, base);
}
