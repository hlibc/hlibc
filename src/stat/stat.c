#include <unistd.h>
#include <signal.h>
#include <syscall.h>
#include <fcntl.h>

int stat(const char *p, struct stat *b)
{
#ifdef  SYS_stat
	return __syscall(SYS_stat, p, b);
#else
	return __syscall(SYS_fstatat, AT_FDCWD, p, b, 0);
#endif
}

