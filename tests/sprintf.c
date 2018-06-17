#include <stdio.h>

int main(void)
{
	char *s = "This is a string literal";
	char b[1024];
	size_t len = sprintf(b, "%s", s);
	printf ("'%s' -- and its length is %zu\n", s, len);
	return 0;
}
