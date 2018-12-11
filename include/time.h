#ifndef	_TIME_H
#define _TIME_H

#include <bits/types.h>
#ifndef NULL
#define NULL ((void*)0)
#endif
struct tm
{
	int tm_sec;
	int tm_min;
	int tm_hour;
	int tm_mday;
	int tm_mon;
	int tm_year;
	int tm_wday;
	int tm_yday;
	int tm_isdst;
	long __tm_gmtoff;
	const char *__tm_zone;
};

clock_t clock (void);
time_t time (time_t *);

#define CLOCK_REALTIME           0
#define CLOCK_MONOTONIC          1
#define CLOCK_PROCESS_CPUTIME_ID 2
#define CLOCK_THREAD_CPUTIME_ID  3

#define TIMER_ABSTIME 1

int nanosleep (const struct timespec *, struct timespec *);

int clock_gettime (clockid_t, struct timespec *);
#endif

