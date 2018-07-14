#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <errno.h>
int main(void)
{
	char *s1 = "   -12315299'end of the string has noise'";
	long long ans = 0;
	ans = strtoll(s1, &s1, 10);
	printf("%lld\n", ans);
	printf("end of string== %s\n", s1);
	char *s2 = "0x2F4";
	ans = strtoll(s2, &s2, 16);
	printf("%x\n", (unsigned int)ans);
	printf("%x\n", 0xff);
	char *s3 = "2F4";
	ans = strtoll(s3, &s3, 16);
	printf("%x\n", (unsigned int)ans);
	printf("%x\n", 0x2F4);
	char *s4 = "0x2ff4cb6";
	ans = strtoll(s4, &s4, 19);
	printf("%x\n", (unsigned int)ans);
	printf("%x\n", 0x2F4);
	printf("123 ====\n");
	char *s5 = "123";
	ans = strtoll(s5, &s5, 10);
	printf("%lld\n", ans);
	printf("%lld\n", 123ll);
	printf("123 ====\n");

	printf("testing strtoll's ability to handle full numerical ranges..\n");
	long long a = LLONG_MAX;
	char string[1024] = { 0 };
	char *s = string;
	sprintf(s, "%lld", a);
	ans = strtoll(s, &s, 10);
	printf("%lld\n", ans);
	a = LLONG_MIN;
	sprintf(s, "%lld", a);
	ans = strtoll(s, &s, 10);
	printf("%lld\n", ans);
	printf("should be %lld and %lld\n", LLONG_MAX, LLONG_MIN);


	printf("testing strtoll overflow detection...\n");
	a = LLONG_MAX;
	sprintf(s, "1%lld", a);
	ans = strtoll(s, &s, 10);
	if (errno == ERANGE)
		printf("ERANGE was set by strtol\n");
	printf("%lld\n", ans);
	printf("above should be LLONG_MAX which = %lld\n", LLONG_MAX);
	
	a = LLONG_MIN;
	sprintf(s, "%lld99", a);
	ans = strtoll(s, &s, 10);
	if (errno == ERANGE)
		printf("ERANGE was set by strtol\n");
	printf("%lld\n", ans);
	printf("above should be LLONG_MIN which is = %lld\n", LLONG_MIN);

	char *b = "0x00080000";
	char *c = "0x00950000";
	ans = strtoll(b, &b, 16);
	printf("%x\n", ans);
	ans = strtoll(c, &c, 16);
	printf("%x\n", ans);
	return 0;
}

