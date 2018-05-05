#include <unistd.h>
#include <signal.h>
#include <syscall.h>

int chown(const char *path, uid_t uid, gid_t gid)
{
#ifdef  SYS_chown
        return __syscall(SYS_chown, path, uid, gid);
#else
        return __syscall(SYS_fchownat, AT_FDCWD, path, uid, gid, 0);
#endif
}

