#include <ctype.h>
#include <stdlib.h>
char *_tol_driver(const char *s, int base, long long *ans);
long long atoll(const char *s)
{
	long long ans = 0;
	_tol_driver(s, 10, &ans);
	return ans;
}
