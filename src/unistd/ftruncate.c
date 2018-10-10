#include <sys/syscall.h>
#include <sys/types.h>
int ftruncate(int fildes, off_t length)
{
	/* note that the "length" argument is adjusted by some libc impls */
        return __syscall(SYS_ftruncate, fildes, length);
}

