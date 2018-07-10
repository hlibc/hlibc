/* Copyright 2017, Mohammad M. Rakib */

#include <string.h>

int main(void)
{
	const char *s = "hellomyfriend";

	char *pch = strstr(s, "my");

	if (strncmp("myfriend", pch, strlen(s)) == 0) return 0;
	else					 return 1;

	return 0;
}
