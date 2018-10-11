#include <sys/syscall.h>

int execve(const char *path, char *const argv[], char *const envp[])
{
        return __syscall(SYS_execve, path, argv, envp);
}

