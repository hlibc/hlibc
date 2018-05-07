#include <ctype.h>
#include <stdlib.h>

long long atoll(const char *s)
{
	long long ans = 0;
	_tol_driver(s, 10, &ans);
	return ans;
}
