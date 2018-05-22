#define _BSD_SOURCE
#include <string.h>
#include <limits.h>

char *strsep(char **stringp, const char *delim)
{
	char delim_array[CHAR_MAX - CHAR_MIN + 1] = {0};
	char * token = *stringp;
	char * p = delim;

	if (*stringp == NULL)
		return NULL;

	for (p = delim; *p != '\0'; ++p)
		delim_array[*p - CHAR_MIN] = 1;

	*stringp = NULL;
	for (p = token; *p != '\0'; ++p) {
		if (delim_array[*p - CHAR_MIN] == 1) {
			*p = '\0';
			*stringp = p + 1;
			break;
		}
	}

	return token;
}
