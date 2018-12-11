#include <time.h>
#include <sys/syscall.h>
#include "../internal/internal.h"
#include <limits.h>

clock_t clock()
{
        struct timespec t = {0};
	long total = 0;
        if (clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t))
                return -1;
	if (__safe_umul_sz(t.tv_sec, 1000000, (size_t *)&total, LONG_MAX) == -1)
		return -1;
	if (__safe_uadd_sz(total, t.tv_nsec / 1000, (size_t *)&total, LONG_MAX) == -1)
		return -1;
        return total;
}

