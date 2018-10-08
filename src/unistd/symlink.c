#include <sys/syscall.h>
#include <unistd.h>

int symlink(const char *path1, const char *path2)
{
#ifdef SYS_symlink
        return __syscall(SYS_symlink, path1, path2);
#else
        return __syscall(SYS_symlinkat, path1, AT_FDCWD, path2);
#endif
}
