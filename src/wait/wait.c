#include <sys/wait.h>
#include <sys/syscall.h>
#include <sys/resource.h>

pid_t wait(int *stat_loc)
{
        return waitpid((pid_t)-1, stat_loc, 0);
}
