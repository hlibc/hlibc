#include <string.h>
#include <stdio.h>
#include <errno.h>
/*
	Copyright 2017 Adrian Parvin D. Ouano
	Copyright 2017 Christopher M. Graff
*/

void perror(const char *s)
{
	char *colon = ": ";

	if (s == NULL || s[0] == '\0')
	{
		s = "";
		colon = "";
	}

	fprintf(stderr, "%s%s%s\n", s, colon, strerror(errno));
}
