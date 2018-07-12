#include <ctype.h>
#include <stdlib.h>
char *__utol_inter(const char *s, int base, unsigned long long *ans);
unsigned long strtoul(const char *s, char **end, int base)
{
	unsigned long ans = 0;
	if (end && *end)
    	    *end = __utol_inter(s, base, &ans);
	else
		__utol_inter(s, base, &ans);
	return ans;
}

