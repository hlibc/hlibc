#include <time.h>
#include <stdio.h>

char *asctime(const struct tm *timeptr)
{
	static char buf[40];
	strftime(buf, sizeof(buf), "%a %b %e %H:%M:%S %Y\n", timeptr);
	return buf;
}
