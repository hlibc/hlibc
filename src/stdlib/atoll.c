#include <ctype.h>
#include <stdlib.h>

long long atoll(const char *s)
{
	long long ans = 0;
	//strtol(s, (char **)NULL, 10);
	_tol_driver(s, 10, &ans);
	return ans;
}
