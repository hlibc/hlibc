#include <dirent.h>
#include "syscall.h"
#include "libc.h"

int getdents(int fd, struct dirent *buf, size_t len)
{
	return syscall(SYS_getdents, fd, buf, len);
}

