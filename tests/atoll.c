#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

int main(void)
{
	char string[1024];
	sprintf(string, "%lld", LLONG_MAX);
	printf("LLONG_MAX = %s\n", string);
	sprintf(string, "%lld", LLONG_MIN);
	printf("LLONG_MIN = %s\n", string);
	return 0;
}
