#include <unistd.h>
#include <sys/mman.h>
#include "syscall.h"
#include "libc.h"

int munmap(void *start, size_t len)
{
	int ret;
	ret = syscall(SYS_munmap, start, len);
	return ret;
}

