#include <time.h>
#include <sys/syscall.h>

time_t time(time_t *tloc)
{
        struct timespec s; 
	syscall(SYS_clock_gettime, CLOCK_REALTIME, &s);
	*tloc = s.tv_sec;
        return *tloc;
}

