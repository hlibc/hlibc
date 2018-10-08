#include <sys/syscall.h>
#include <unistd.h>

ssize_t read(int fildes, void *buf, size_t nbyte)
{
        return __syscall(SYS_read, fildes, buf, nbyte);
}

