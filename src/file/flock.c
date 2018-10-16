#include <sys/file.h>
#include <sys/syscall.h>
#include "../internal/internal.h"

int flock(int fd, int operation)
{
        return syscall(SYS_flock, fd, operation);
}

