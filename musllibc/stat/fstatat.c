#include <sys/stat.h>
#include "syscall.h"
#include "libc.h"

int fstatat(int fd, const char *path, struct stat *buf, int flag)
{
#ifdef SYS_fstatat
	return syscall(SYS_fstatat, fd, path, buf, flag);
#else
	return syscall(SYS_newfstatat, fd, path, buf, flag);
#endif
}


