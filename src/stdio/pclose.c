#include "../internal/internal.h"

int pclose(FILE *o)
{
	int ret = 0;
	pid_t pid = o->pid;

	if (waitpid(pid, &ret, 0) >= 0) {
		return ret;
	}
	o->pid = 0;

	fclose(o);
	return -1;
}
