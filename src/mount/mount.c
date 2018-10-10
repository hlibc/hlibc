#include <sys/syscall.h>
#include <sys/mount.h>
int mount(const char *source, const char *target,
                 const char *filesystemtype, unsigned long mountflags,
                 const void *data) 
{
        return __syscall(SYS_mount, source, target, filesystemtype, mountflags, data);
}
