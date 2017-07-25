#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

int main(int argc, char *argv[])
{
	printf("123456789 = %d\n", atoi("123456789"));
	printf("1234567898 = %d\n", atoi("1234567898"));
	printf("123456789876 = %d\n", atoi("123456789876"));
	printf("12345678987654321 = %d\n", atoi("12345678987654321"));

	printf("INT_MAX = %d\n", INT_MAX);
	printf("INT_MIN = %d\n", INT_MIN);

	return 0;
}
