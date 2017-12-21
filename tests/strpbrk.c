/* Copyright 2017, Mohammad M. Rakib */

#include <string.h>

int main(void)
{
	char *s = "Example string";
	char *accept = "amb";

	if ((*(strpbrk(s, accept))) == 'm') return 0;
	else                                 return 1;

	return 0;
}
