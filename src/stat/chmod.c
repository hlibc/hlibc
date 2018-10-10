#include <sys/syscall.h>
#include <sys/stat.h>

int chmod(const char *path, mode_t mode)
{
#ifdef SYS_chmod
	return __syscall(SYS_chmod, path, mode);
#else
	return __syscall(SYS_fchmodat, AT_FDCWD, path, mode);
#endif
}

