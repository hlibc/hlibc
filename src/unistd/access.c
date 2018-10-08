#include <unistd.h>
#include <sys/syscall.h>
#include <fcntl.h>

int access(const char *path, int amode)
{
#ifdef  SYS_access
	return __syscall(SYS_access, path, amode);
#else
	return __syscall(SYS_faccessat, AT_FDCWD, path, amode, 0);
#endif
}


