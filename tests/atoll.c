#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

int main(int argc, char *argv[])
{
	printf("123456789 = %ld\n", atoll("123456789"));
	printf("1234567898 = %ld\n", atoll("1234567898"));
	printf("123456789876 = %ld\n", atoll("123456789876"));
	printf("12345678987654321 = %ld\n", atoll("12345678987654321"));

	printf("LLONG_MAX = %ld\n", LLONG_MAX);
	printf("LLONG_MIN = %ld\n", LLONG_MIN);

	printf("2147483647 %ld\n", atoll("2147483647"));
	printf("-2147483648 %ld\n", atoll("-2147483648")); 
	
	printf("123456 %ld\n", atoll("123456"));
	printf("-123456 %ld\n", atoll("-123456"));
	return 0;
}
