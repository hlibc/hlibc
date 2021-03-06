#include <stddef.h>
#include <stdlib.h>
#include <string.h>

char *strdup(const char *s)
{
	char *ret;
	size_t len = strlen(s) + 1;

	if (!(ret = malloc(len))) {
		return NULL;
	}

	memcpy(ret, s, len);
	return ret;
}
