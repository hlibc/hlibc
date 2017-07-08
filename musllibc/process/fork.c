#include <unistd.h>
#include "syscall.h"
#include "libc.h"

pid_t fork(void)
{
	pid_t ret;
	ret = syscall(SYS_fork);
	return ret;
}
