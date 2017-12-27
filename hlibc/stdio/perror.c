#include <string.h>
#include <stdio.h>
#include <errno.h>

void perror(const char *s)
{
	char *colon = ": ";

	if (s == NULL || s[0] == '\0')
	{
		s = "";
		colon = "";
	}

	fprintf(stderr, "%s %s %s", s, colon, strerror(errno));
}
