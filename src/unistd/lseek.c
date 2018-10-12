#include <sys/syscall.h>
#include "../internal/internal.h"

off_t lseek(int fildes, off_t offset, int whence)
{
#ifdef SYS__llseek
        off_t res;
	off_t ret;
	if ((ret = syscall(SYS__llseek, fildes, offset>>32, offset, &res, whence) == -1))
		ret = res;
	return ret;
	
#else
        return syscall(SYS_lseek, fildes, offset, whence);
#endif
}


