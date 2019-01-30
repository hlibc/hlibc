#include <time.h>
#include <stdio.h>

char *asctime(const struct tm *timeptr)
{
	static char buf[40];
	sprintf(buf,  "%.3s %.3s%3d %.2d:%.2d:%.2d %d\n",
	timeptr->tm_wday,
	timeptr->tm_mon,
	timeptr->tm_mday,
	timeptr->tm_hour,
	timeptr->tm_min,
	timeptr->tm_sec,
	1900 + timeptr->tm_year);
	return buf;
}
