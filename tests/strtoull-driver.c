#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	char *s1 = "   12315299'end of the string has noise'";
	unsigned long long ans = 0;
	ans = strtoull(s1, &s1, 10);
	printf("%llu\n", ans);
	printf("end of string== %s\n", s1);
	char *s2 = "0x2F4";
	ans = strtoull(s2, &s2, 16);
	printf("%x\n", (unsigned int)ans);
	printf("%x\n", 0xff);
	char *s3 = "2F4";
	ans = strtoull(s3, &s3, 16);
	printf("%x\n", (unsigned int)ans);
	printf("%x\n", 0x2F4);
	char *s4 = "0x2ff4cb6";
	ans = strtoull(s4, &s4, 19);
	printf("%x\n", (unsigned int)ans);
	printf("%x\n", 0x2F4);
	return 0;
}

