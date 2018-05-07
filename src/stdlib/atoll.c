#include <ctype.h>
#include <stdlib.h>
long long strtoll(const char *s, char **end, int base)
{
	long long ans = 0;
	*end = _tol_driver(s, base, &ans);
	return ans;
}

long long atoll(const char *s)
{
	long long ans = 0;
	_tol_driver(s, 10, &ans);
	return ans;
}
