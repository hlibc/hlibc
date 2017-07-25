#include <stdlib.h>
#include <ctype.h>

int atoi(const char *s)
{
	size_t i;
	int ret;
	i = ret = 0;
	for (i = 0; s[i] && isdigit(s[i]); ++i)
		ret = 10 * ret + (s[i] - '0');
	return ret;
} 
