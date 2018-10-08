#include <sys/syscall.h>
#include <unistd.h>

int unlink(const char *path)
{
#ifdef SYS_unlink
        return __syscall(SYS_unlink, path);
#else
        return __syscall(SYS_unlinkat, AT_FDCWD, path, 0);
#endif
}
