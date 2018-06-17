#include <stdio.h>

int main(void)
{
	char *s = "This is a string literal";
	char b[1024];
	size_t len = snprintf(b, 5, "%s", s);
	printf ("'%s' -- and snprintf returned %zu\n", b, len);
	return 0;
}
