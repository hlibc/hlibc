#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

int main(int argc, char *argv[])
{
	char string[1024];
	sprintf(string, "%d", INT_MAX);
	printf("INT_MAX = %s\n", string);
	sprintf(string, "%d", INT_MIN);
	printf("INT_MIN = %s\n", string); 
	/*
	printf("123456789 = %d\n", atoi("123456789"));
	printf("1234567898 = %d\n", atoi("1234567898"));
	printf("123456789876 = %d\n", atoi("123456789876"));
	printf("2147483647 %d\n", atoi("2147483647"));
	printf("-2147483648 %d\n", atoi("-2147483648"));
	printf("123456 %d\n", atoi("123456"));
	printf("-123456 %d\n", atoi("-123456"));
	*/
	return 0;
}
