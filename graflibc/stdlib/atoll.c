#include <stdlib.h>
#include <ctype.h>

long long atoll(const char *s)
{ 
	size_t i;
	long long ret;
	i = ret = 0;
	long long neg = 1;
	
	if (isspace(s[i]))
		++i;

	if (s[i] == '-')
	{
		++i;
		neg = -1;
	}
	
	for (; s[i] && isdigit(s[i]); ++i)
		ret = 10 * ret + (s[i] - '0');

	return ret * neg;
}
