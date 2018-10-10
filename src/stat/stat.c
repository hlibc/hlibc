#include <sys/syscall.h>
#include <signal.h>
#include <syscall.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>


int stat(const char *restrict path, struct stat *restrict buf)
{
#ifdef  SYS_stat
	return __syscall(SYS_stat, path, buf);
#else
	return __syscall(SYS_fstatat, AT_FDCWD, path, buf, 0);
#endif
}

