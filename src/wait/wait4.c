#include <sys/wait.h>
#include <sys/syscall.h>
#include <sys/resource.h>

pid_t wait4(pid_t pid, int *status, int options, struct rusage *usage)
{
        return __syscall(SYS_wait4, pid, status, options, usage);
}

