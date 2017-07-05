#include <gstdio.h>

int gpclose(GFILE *fp)
{
	int ret = 0;
	pid_t pid = fp->pid;

	if (waitpid(pid,&ret,0) >= 0)
		return ret;
	fp->pid = 0;

	gfclose(fp);
	gfflush(NULL);
	return -1;
}
