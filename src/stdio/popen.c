#include "../internal/internal.h"
#include <unistd.h>

FILE *popen(const char *command, const char *type)
{
	FILE *o;
	int pipefd[2] = { 0 };
	char *argv[] = { "/bin/sh", "-c", NULL, NULL };

	if ((o = __internal_fopen(NULL, type, 1)) == NULL) {
		return NULL;
	}
	if (command == NULL) {
		return NULL;
	}
	if ((pipe(pipefd)) == -1) {
		goto error;
	}
	if ((o->pid = fork()) == -1) {
		goto error;
	}

	o->fd = pipefd[0];

	if (o->pid == 0) {
		argv[2] = (char *)command;
		if ((close(pipefd[0])) == -1) {
			goto error;
		}
		if ((dup2(pipefd[1], 1)) == -1) {
			goto error;
		}
		if ((close(pipefd[1])) == -1) {
			goto error;
		}
		execvp(argv[0], argv);
		_exit(127);
	}
	else {
		close(pipefd[1]);
	}

	return o;

	error:
	fclose(o);
	return NULL;
}
