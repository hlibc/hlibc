#include <stdlib.h>
#include <ctype.h>

int atoi(const char *s)
{
	/* 
		Performs correctly from INT_MIN to INT_MAX 
		
	*/
	size_t i;
	int ret;
	i = ret = 0;
	int neg = 1;
	
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
