#include <sys/syscall.h>
#include <unistd.h>

int pipe(int filedes[2])
{
#ifdef  SYS_pipe
        return __syscall(SYS_pipe, filedes);
#else
        return __syscall(SYS_pipe2, filedes, 0);
#endif
}


