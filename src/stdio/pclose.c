#include <stdio.h>

int pclose(FILE *fp)
{
	int ret = 0;
	pid_t pid = fp->pid;

	if (waitpid(pid,&ret,0) >= 0)
		return ret;
	fp->pid = 0;

	fclose(fp);
	fflush(NULL);
	return -1;
}
