#include <sys/syscall.h>
#include <unistd.h>

int chroot(const char *path)
{
        return syscall(SYS_chroot, path);
}

