#include <sys/syscall.h>

int execv(const char *path, char *const argv[])
{
        return execve(path, argv, __environ);
}

