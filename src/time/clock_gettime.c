#include <time.h>
#include <sys/syscall.h>

int clock_gettime(clockid_t clk_id, struct timespec *tp)
{
        return syscall(SYS_clock_gettime, clk_id, tp);
}

