#include <sys/syscall.h>
#include <unistd.h>

ssize_t write(int fildes, const void *buf, size_t nbyte)
{
        return syscall(SYS_write, fildes, buf, nbyte);
}


