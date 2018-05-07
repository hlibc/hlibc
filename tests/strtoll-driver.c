#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	char *s1 = "   -12315299'end of the string has noise'";
	long long ans = 0; 
	ans = strtoll(s1, &s1, 10);
	printf("%lld\n", ans);
	printf("end of string== %s\n", s1);
	return 0;
}

