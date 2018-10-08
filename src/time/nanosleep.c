#include <sys/syscall.h>
#include <time.h>

int nanosleep(const struct timespec *rqtp, struct timespec *rmtp)
{
        return __syscall(SYS_nanosleep, rqtp, rmtp);
}

