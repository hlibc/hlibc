#include <signal.h>
#include "syscall.h"
#include "libc.h"

int sigsuspend(const sigset_t *mask)
{
	return syscall(SYS_rt_sigsuspend, mask, 8);
}
