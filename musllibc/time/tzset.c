#include <time.h>
#include <ctype.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include "libc.h"

#include "__time.h"

long  __timezone = 0;
int   __daylight = 0;
char *__tzname[2] = { 0, 0 };
int   __dst_offset = 0;

weak_alias(__timezone, timezone);
weak_alias(__daylight, daylight);
weak_alias(__tzname, tzname);

static char std_name[TZNAME_MAX+1];
static char dst_name[TZNAME_MAX+1];

/* all elements are zero-based */
static struct rule {
	signed char month;
	signed char week;
	short day;
	int time;
} __dst_start, __dst_end;

static void zname(char *d, char **s)
{

}

static int hhmmss(char **s)
{
	
}

static int dstrule(struct rule *rule, char **s)
{
}

void tzset(void)
{
	
}

void __tzset(void)
{
}

static int is_leap(int year)
{
}

static int cutoff_yday(struct tm *tm, struct rule *rule)
{
}

struct tm *__dst_adjust(struct tm *tm)
{
}
