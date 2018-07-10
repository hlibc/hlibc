#include <ctype.h>
#include <stdlib.h>
char *__tol_inter(const char *, int, long long *);
long long atoll(const char *s)
{
	long long ans = 0;
	__tol_inter(s, 10, &ans);
	return ans;
}
