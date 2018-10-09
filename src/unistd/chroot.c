#include <sys/syscall.h>
#include <unistd.h>

int chroot(const char *path)
{
        return __syscall(SYS_chroot, path);
}

