#include <ctype.h>
#include <stdlib.h>

long long atoll(const char *s)
{
	long long ans = 0;
	ans = strtoll(s, NULL, 10);
	return ans;
}
