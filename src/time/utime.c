#include <utime.h>
#include <fcntl.h>
#include "syscall.h"

int utime(const char *path, const struct utimbuf *times)
{
#ifdef	SYS_utime
	return syscall(SYS_utime, path, times);
#else
	return syscall(SYS_utimensat, AT_FDCWD, path, times);
#endif
}
