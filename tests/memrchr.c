/* Copyright 2017, Mohammad M. Rakib */ 

#include <stdio.h>
#include <string.h>

int main(void)
{
	char *str = "Example string";
	char *pch;

	pch = (char*)memchr(str, 'p', strlen(str));

	if (pch != NULL)
		if ((pch - str + 1) == 5) return 0;
		else                      return 1;
	else
		return 1;

	return 0;
}
