#include <sys/syscall.h>
#include <unistd.h>

int pipe(int fildes[2])
{
#ifdef  SYS_pipe
        return __syscall(SYS_pipe, fildes);
#else
        return __syscall(SYS_pipe2, fildes, 0);
#endif
}


