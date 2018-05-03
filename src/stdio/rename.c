#include <unistd.h>
#include "syscall.h"
#include <fcntl.h>

int rename(const char *o, const char *n)
{
#ifdef	SYS_rename
	return syscall(SYS_rename, o, n);
#else
	return syscall(SYS_renameat, AT_FDCWD, o, AT_FDCWD, n);
#endif
}

