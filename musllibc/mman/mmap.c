#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>
#include <limits.h>
#include "syscall.h"
#include "libc.h"

void *mmap(void *start, size_t len, int prot, int flags, int fd, off_t off)
{
	void *ret;
	if (sizeof(off_t) > sizeof(long))
		if (((long)off & 0xfff) | ((long)((unsigned long long)off>>(12 + 8*(sizeof(off_t)-sizeof(long))))))
			start = (void *)-1;
	// locking mechanism was here -cmg
#ifdef SYS_mmap2
	ret = (void *)syscall(SYS_mmap2, start, len, prot, flags, fd, off>>12);
#else
	ret = (void *)syscall(SYS_mmap, start, len, prot, flags, fd, off);
#endif
	// locking mechanism was here -cmg
	return ret;
}

