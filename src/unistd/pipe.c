#include <sys/syscall.h>
#include <unistd.h>

int pipe(int fildes[2])
{
#ifdef  SYS_pipe
        return syscall(SYS_pipe, fildes);
#else
        return syscall(SYS_pipe2, fildes, 0);
#endif
}


