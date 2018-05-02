#include <unistd.h>
#include "syscall.h"
#include "libc.h"

pid_t fork(void)
{
        pid_t ret;
#ifdef SYS_fork
        ret = __syscall(SYS_fork);
#else
        ret = __syscall(SYS_clone, SIGCHLD, 0);
#endif
	return ret;
}
