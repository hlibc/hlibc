#include <sys/syscall.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int dup2(int fildes, int fildes2)
{
	int ret;
#ifdef SYS_dup2
	for (;(ret = syscall(SYS_dup2, fildes, fildes2)) == -EBUSY;)
		;
#else
	for (;(ret = syscall(SYS_dup3, fildes, fildes2, 0)) == -EBUSY;)
		;
#endif
	return ret;
}


