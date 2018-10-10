#include <sys/types.h>
#include <sys/stat.h>
#include <sys/syscall.h>

int fstat(int fd, struct stat *buf)
{
        return __syscall(SYS_fstat, fd, buf);
}

