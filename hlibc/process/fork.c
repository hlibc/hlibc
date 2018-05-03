#include <unistd.h> 
#include <signal.h>
#include <syscall.h>
pid_t fork(void)
{
        pid_t ret;
#ifdef SYS_fork
        ret = syscall(SYS_fork);
#else
        ret = syscall(SYS_clone, SIGCHLD, 0);
#endif
	return ret;
}
