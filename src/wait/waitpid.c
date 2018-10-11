#include <sys/wait.h>
#include <sys/syscall.h>
#include <sys/resource.h>

pid_t waitpid(pid_t pid, int *stat_loc, int options)
{
        return syscall(SYS_wait4, pid, stat_loc, options, 0);
}
