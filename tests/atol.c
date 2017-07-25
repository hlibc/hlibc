#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

int main(int argc, char *argv[])
{
	printf("123456789 = %ld\n", atol("123456789"));
	printf("1234567898 = %ld\n", atol("1234567898"));
	printf("123456789876 = %ld\n", atol("123456789876"));
	printf("12345678987654321 = %ld\n", atol("12345678987654321"));

	printf("LONG_MAX = %ld\n", LONG_MAX);
	printf("LONG_MIN = %ld\n", LONG_MIN);

	printf("2147483647 %ld\n", atol("2147483647"));
	printf("-2147483648 %ld\n", atol("-2147483648")); 
	
	printf("123456 %ld\n", atol("123456"));
	printf("-123456 %ld\n", atol("-123456"));
	return 0;
}
