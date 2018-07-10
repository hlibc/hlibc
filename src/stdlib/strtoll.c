#include <ctype.h>
#include <stdlib.h>
char *__tol_inter(const char *s, int base, long long *ans);
long long strtoll(const char *s, char **end, int base)
{
	long long ans = 0;
	if (end)
    	    *end = __tol_inter(s, base, &ans);
	else
		__tol_inter(s, base, &ans);
	return ans;
}

