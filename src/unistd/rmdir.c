#include <sys/syscall.h>
#include <unistd.h>

int rmdir(const char *path)
{
#ifdef SYS_rmdir
        return __syscall(SYS_rmdir, path);
#else
        return __syscall(SYS_unlinkat, AT_FDCWD, path, AT_REMOVEDIR);
#endif
}

