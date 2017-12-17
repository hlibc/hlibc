#define _BSD_SOURCE
#include <stdio.h>
#include <string.h>

int main(void)
{
	const char *func = "strlcat()";
	const char *pass = "pass";
	const char *fail = "fail";
	char src[] = "987654321";
	char dst[255];
	int len = 0, in;

	in = 8;
	strlcpy(dst, "123456789", 10);
	printf("%s, %s, ", dst, src);
	len = strlcat(dst, src, in);
	printf("%3d = %s, %d %s test ~ %s\n", in, dst, len, func,
		   (len == in-1)? pass : fail);
	in = 19;
	strlcpy(dst, "123456789", 10);
	printf("%s, %s, ", dst, src);
	len = strlcat(dst, src, in);
	printf("%3d = %s, %d %s test ~ %s\n", in, dst, len, func,
		   (len == strlen(dst)) ? pass : fail);
	in = 30;
	strlcpy(dst, "123456789", 10);
	printf("%s, %s, ", dst, src);
	len = strlcat(dst, src, in);
	printf("%3d = %s, %d %s test ~ %s\n", in, dst, len, func,
		   (len == strlen(dst)) ? pass : fail);
	return 0;
}
