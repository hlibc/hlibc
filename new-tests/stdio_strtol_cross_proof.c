#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

void test_conv_long(char *test, long num)
{
	char p[1024] = { 0 };
	char *s = p;
	sprintf(s, "%ld", num);
	if (strtol(s, &s, 0) == num)
		printf("strtol and sprintf properly juggle %s\n", test);
	else
		printf("strtol and sprintf don't juggle %s\n", test);
	
}

void test_conv_llong(char *test, long long num)
{
	char p[1024] = { 0 };
	char *s = p;
	sprintf(s, "%lld", num);
	if (strtoll(s, &s, 0) == num)
		printf("strtoll and sprintf properly juggle %s\n", test);
	else
		printf("strtoll and sprintf don't juggle %s\n", test);
	
}

int main(void)
{
	test_conv_long("LLONG_MAX", LLONG_MAX);
	test_conv_long("LLONG_MIN", LLONG_MIN);
	test_conv_long("LLONG_MIN / -2", LLONG_MIN / -2);
	test_conv_long("LLONG_MAX / 2", LLONG_MAX / 2);
	
	test_conv_llong("LLONG_MAX", LLONG_MAX);
	test_conv_llong("LLONG_MIN", LLONG_MIN);
	test_conv_llong("LLONG_MIN / -2", LLONG_MIN / -2);
	test_conv_llong("LLONG_MAX / 2", LLONG_MAX / 2);
	return 0;
}
