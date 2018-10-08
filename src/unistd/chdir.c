#include <sys/syscall.h>
#include <unistd.h>

int chdir(const char *path)
{
	return __syscall(SYS_chdir, path);
}


