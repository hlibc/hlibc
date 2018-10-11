#include <sys/mman.h>
#include <sys/syscall.h>
/*
	TODO: modern C libraries use complex methods to make adjustments to the
	'addr' argument of mmap. hlibc has omitted these until the time that
	tspecifc tests can be created to reproduce the need for adjustments to
	the addr argument. These adjustments are almost certainly requires and
	should be addressed as soon as possible.
*/
void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset)
{ 
	return (void *)__syscall(SYS_mmap, addr, length, prot, flags, fd, offset);
}
