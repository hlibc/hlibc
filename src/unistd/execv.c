#include <sys/syscall.h>
#include "../internal/internal.h"

int execv(const char *path, char *const argv[])
{
        return execve(path, argv, __environ);
}

