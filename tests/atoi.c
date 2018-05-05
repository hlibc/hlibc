#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

int main(void)
{
	char string[1024];
	sprintf(string, "%d", INT_MAX);
	printf("INT_MAX = %s\n", string);
	sprintf(string, "%d", INT_MIN);
	printf("INT_MIN = %s\n", string);
	return 0;
}
