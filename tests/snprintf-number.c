#include <stdio.h>

int main(void)
{
	int n = 52525;
	char b[1024];
	size_t len = snprintf(b, 5, "%d", n);
	printf ("'%s' -- and snprintf returned %zu\n", b, len);
	return 0;
}
