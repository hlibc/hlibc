#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

int main(int argc, char *argv[])
{
	char string[1024];
        sprintf(string, "%lld", LLONG_MAX);
        printf("LLONG_MAX = %s\n", string);
        sprintf(string, "%lld", LLONG_MIN);
        printf("LLONG_MIN = %s\n", string);

	/*
	printf("123456789 = %lld\n", atoll("123456789"));
	printf("1234567898 = %lld\n", atoll("1234567898"));
	printf("123456789876 = %lld\n", atoll("123456789876"));
	printf("12345678987654321 = %lld\n", atoll("12345678987654321"));
	printf("12345678987654321 = %lld\n", atoll("     12345678987654321"));
	printf("9223372036854775807 %lld\n", atoll("9223372036854775807"));
	printf("-9223372036854775808 %lld\n", atoll("-9223372036854775808"));
	printf("123456 %lld\n", atoll("123456"));
	printf("-123456 %lld\n", atoll("-123456"));
	*/
	return 0;
}
