#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

int main(int argc, char *argv[])
{
	printf("123456789 = %ld\n", atol("123456789"));
	printf("1234567898 = %ld\n", atol("1234567898"));
	printf("123456789876 = %ld\n", atol("123456789876"));
	printf("12345678987654321 = %ld\n", atol("12345678987654321"));
	//LONG_MAX = 9223372036854775807
	//LONG_MIN = -9223372036854775808
	printf("LONG_MAX = %ld\n", LONG_MAX);
	printf("LONG_MIN = %ld\n", LONG_MIN);

	printf("9223372036854775807 %ld\n", atol("9223372036854775807"));
	printf("-9223372036854775808 %ld\n", atol("-9223372036854775808")); 
	
	printf("123456 %ld\n", atol("123456"));
	printf("-123456 %ld\n", atol("-123456"));
	return 0;
}
