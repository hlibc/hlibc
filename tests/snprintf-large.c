#include <stdio.h>

int main(void)
{
	size_t n = 5252123125;
	char b[1024];
	size_t len = snprintf(b, 5, "%zu", n);
	printf ("'%s' -- and snprintf returned %zu\n", b, len);
	return 0;
}
