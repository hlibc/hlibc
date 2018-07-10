#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

int main(void)
{
	char string[1024];
	sprintf(string, "%ld", LONG_MAX);
	printf("LONG_MAX = %s\n", string);
	sprintf(string, "%ld", LONG_MIN);
	printf("LONG_MIN = %s\n", string);
	return 0;
}
