#include <ctype.h>
#include <stdlib.h>
char *_utol_driver(const char *s, int base, unsigned long long *ans);
unsigned long long strtoull(const char *s, char **end, int base)
{
	unsigned long long ans = 0;
	if (end && *end)
    	    *end = _utol_driver(s, base, &ans);
	else
		_utol_driver(s, base, &ans);
	return ans;
}

