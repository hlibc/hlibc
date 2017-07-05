#include <gstdio.h>

GFILE *gpopen(const char *command, const char *type)
{
	GFILE *ret;
	int pipefd[2] = { 0 };
	char *argv[] = { "/bin/sh", "-c", NULL, NULL};

	if ((ret = gfopen(NULL, type)) == NULL)
		return NULL;
	if (command == NULL)
		return NULL;
	if ((pipe(pipefd)) == -1)
		goto errorplace;
	if ((ret->pid = fork()) == -1)
		goto errorplace;

	ret->fd = pipefd[0];

	if (ret->pid == 0)
	{
		argv[2] = (char *)command;
		if ((close(pipefd[0])) == -1)
			goto errorplace;
		if ((dup2(pipefd[1], 1)) == -1)
			goto errorplace;
		if ((close(pipefd[1])) == -1)
			goto errorplace;
		execvp(argv[0], argv);
		_exit(1);
	}
	else
	{
		close(pipefd[1]);
	}
	
	return ret;

	errorplace:
		gfclose(ret);
		return NULL;
}		
