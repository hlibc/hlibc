#include <sys/mman.h>
#include <sys/syscall.h>

void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset)
{ 
#ifdef SYS_mmap2
	return (void *)syscall(SYS_mmap2, addr, length, prot, flags, fd, offset>>12);
#else
	return (void *)syscall(SYS_mmap, addr, length, prot, flags, fd, offset);
#endif
}
