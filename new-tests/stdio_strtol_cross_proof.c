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

void test_conv_ulong(char *test, unsigned long num)
{
	char p[1024] = { 0 };
	char *s = p;
	sprintf(s, "%lu", num);
	if (strtoul(s, &s, 0) == num)
		printf("strtoul and sprintf properly juggle %s\n", test);
	else
		printf("strtoul and sprintf don't juggle %s\n", test);
	
}

void test_conv_ullong(char *test, unsigned long long num)
{
	char p[1024] = { 0 };
	char *s = p;
	sprintf(s, "%llu", num);
	if (strtoull(s, &s, 0) == num)
		printf("strtoull and sprintf properly juggle %s\n", test);
	else
		printf("strtoull and sprintf don't juggle %s\n", test);
	
}

int main(void)
{
	//test_conv_long("1", 1); // fails!
	test_conv_long("12", 12);
	test_conv_long("123", 123);
	test_conv_long("1234", 1234);
	test_conv_long("LONG_MAX", LONG_MAX);
	test_conv_long("LONG_MIN", LONG_MIN);
	test_conv_long("LONG_MIN / -2", LONG_MIN / -2);
	test_conv_long("LONG_MAX / 2", LONG_MAX / 2);
	
	test_conv_llong("LLONG_MAX", LLONG_MAX);
	test_conv_llong("LLONG_MIN", LLONG_MIN);
	test_conv_llong("LLONG_MIN / -2", LLONG_MIN / -2);
	test_conv_llong("LLONG_MAX / 2", LLONG_MAX / 2);
	
	test_conv_ulong("ULONG_MAX", ULONG_MAX);
	test_conv_ulong("ULONG_MAX / 2", ULONG_MAX / 2);

	test_conv_ullong("ULLONG_MAX", ULLONG_MAX);
	test_conv_ullong("ULLONG_MAX / 2", ULLONG_MAX / 2);
	return 0;
}
