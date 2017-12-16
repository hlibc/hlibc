#define _BSD_SOURCE
#include <stdio.h>
#include <string.h>

int main(void)
{
	const char *func = "strlcpy()";
	const char *pass = "pass";
	const char *fail = "fail";
	char src[] = "123456789";
	char dst[255];
	int len = 0, in = 5;

	len = strlcpy(dst, src, in);
	printf("%s, %3d = %s, %3d\t%s test ~ %s\n", src, in, dst, len,
		   func, (len == in-1)? pass : fail);
	in = 10;
	len = strlcpy(dst, src, in);
	printf("%s, %3d = %s, %3d\t%s test ~ %s\n", src, in, dst, len,
		   func, (len == strlen(src)) ? pass : fail);
	in = 20;
	len = strlcpy(dst, src, in);
	printf("%s, %3d = %s, %3d\t%s test ~ %s\n", src, in, dst, len,
		   func, (len == strlen(src)) ? pass : fail);
	return 0;
}
