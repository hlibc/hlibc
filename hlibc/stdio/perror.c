/* Copyright 2017, Mohammad M. Rakib */

#include <stdio.h>
#include <errno.h>

void perror(const char *str)
{
	if (str == NULL || *str == '\0') {
		return;
	}

	int errnum = errno;
	char *emsg = strerror(errnum);

	fprintf(stderr, "%s: %s\n", str, emsg);
}
