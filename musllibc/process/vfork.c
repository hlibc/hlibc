#include <unistd.h>
#include "syscall.h"
#include "libc.h"

pid_t vfork(void)
{
	return syscall(SYS_fork);
}

