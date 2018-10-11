#include <sys/syscall.h>
#include <sys/types.h>
int truncate(int fildes, off_t length)
{
	/* note that the "length" argument is adjusted by some libc impls */
        return syscall(SYS_truncate, fildes, length);
}

