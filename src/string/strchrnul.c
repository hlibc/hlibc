#include <stddef.h>
#include <string.h>

/* Copyright (c) 2017, Iain Hill */

char *strchrnul(const char *s, int c)
{
	for ( ; *s != '\0'; s++)
		if(*s == c)
			return (char*)s;

	return (char*)s;
}

