#include <unistd.h>
#include "syscall.h"

pid_t getpgrp(void)
{
#ifdef	SYS_getpgrp
	return syscall(SYS_getpgrp);
#else
	return syscall(SYS_getpgid, 0);
#endif
}
