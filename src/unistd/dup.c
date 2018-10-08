#include <sys/syscall.h>
#include <unistd.h>

int dup(int fd)
{
	return __syscall(SYS_dup, fd);
}

