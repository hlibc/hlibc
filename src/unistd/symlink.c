#include <sys/syscall.h>
#include <unistd.h>
#include <fcntl.h>

int symlink(const char *path1, const char *path2)
{
#ifdef SYS_symlink
        return syscall(SYS_symlink, path1, path2);
#else
        return syscall(SYS_symlinkat, path1, AT_FDCWD, path2);
#endif
}
