#include <sys/syscall.h>
#include "../internal/internal.h"
#include <string.h>
#include <limits.h>
#include <stdlib.h>

int execvp(const char *file, char *const argv[])
{
	char word[(PATH_MAX + 1) * 2];
	char *token;
	char t[PATH_MAX + 1];
	char *u;
	char *p = (char *)file;
	while (*p++) {
		if (*p == '/')
			return execv(file, argv);
	}

	u = getenv("PATH");
	strcpy(t, u);
	token = strtok(t, ":");
	while (token != NULL) {
		sprintf(word, "%s/%s",token, file);
		if ( access(word, X_OK) == 0)
			return execv(word, argv);
		token = strtok(NULL, ":");
	}
	return -1;
}

