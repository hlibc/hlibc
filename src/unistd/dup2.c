#include <sys/syscall.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int dup2(int filedes, int filedes2)
{
	int ret;
#ifdef SYS_dup2
	for (;(ret = __syscall(SYS_dup2, filedes, filedes2)) == -EBUSY;)
		;
#else
	for (;(ret = __syscall(SYS_dup3, filedes, filedes2, 0)) == -EBUSY;)
		;
#endif
	return __syscall_ret(ret);
}


