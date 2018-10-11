#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h> 
#include <signal.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h> 
#include <sys/syscall.h>
#include <sys/time.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include "../internal/internal.h"

int clock_gettime(clockid_t clk, struct timespec *ts)
{ 
	int r = syscall(SYS_clock_gettime, clk, ts);
	if (!r)
		return r;
	if (r == -ENOSYS) {
		if (clk == CLOCK_REALTIME) {
			syscall(SYS_gettimeofday, clk, ts, 0);
			ts->tv_nsec = (int)ts->tv_nsec * 1000;
			return 0;
		}
		r = -EINVAL;
	}
	errno = -r;
	return -1;
}

time_t time(time_t *t)
{
	struct timespec ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	if (t) *t = ts.tv_sec;
	return ts.tv_sec;
}

