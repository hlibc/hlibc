#include <sys/syscall.h>
#include <unistd.h>

int close(int fd)
{
	return __syscall(SYS_close, fd);
}

