#include <sys/syscall.h>
#include <unistd.h>

ssize_t read(int filedes, void *buf, size_t nbyte)
{
        return __syscall(SYS_read, filedes, buf, nbyte);
}

