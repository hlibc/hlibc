#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

extern char **environ;
extern char **__env_map;

int unsetenv(const char *name)
{
	int i, j;
	size_t l = strlen(name);

	if (!*name || strchr(name, '=')) {
		errno = EINVAL;
		return -1;
	}
again:
	for (i=0; environ[i] && (memcmp(name, environ[i], l) || environ[i][l] != '='); i++);
	if (environ[i]) {
		if (__env_map) {
			for (j=0; __env_map[j] && __env_map[j] != environ[i]; j++);
			free (__env_map[j]);
			for (; __env_map[j]; j++)
				__env_map[j] = __env_map[j+1];
		}
		for (; environ[i]; i++)
			environ[i] = environ[i+1];
		goto again;
	}
	return 0;
}
