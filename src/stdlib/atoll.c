#include <ctype.h>
#include <stdlib.h>
char *_tol_driver(const char *, int, long long *);
long long atoll(const char *s)
{
	long long ans = 0;
	_tol_driver(s, 10, &ans);
	return ans;
}
