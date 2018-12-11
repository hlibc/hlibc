#include <time.h>
#include <sys/syscall.h>
// TODO: provide arithmetic boundary checks and return a -1
clock_t clock()
{
        struct timespec t = {0};
        if (clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t))
                return -1; 
        return (t.tv_sec * 1000000) + (t.tv_nsec / 1000);
}

