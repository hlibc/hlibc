#include <ctype.h>
#include <stdlib.h>

long strtol(const char *s, char **end, int base)
{
	long ans = 0;
	*end = _tol_driver(s, base, &ans);
	return ans;
}

