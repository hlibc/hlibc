#include <ctype.h>
#include <stdlib.h>

int strtoi(const char *nptr, char **endptr, int base)
{
	return strtoll(nptr, endptr, base);
}
