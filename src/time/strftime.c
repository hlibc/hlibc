#include <stdio.h>
#include <time.h>

static const char *weekdays[] =
{
	"Sunday",
	"Monday",
	"Tuesday",
	"Wednesday",
	"Thursday",
	"Friday",
	"Saturday"
};

static const char *months[] =
{
	"January",
	"February",
	"March",
	"April",
	"May",
	"June",
	"July",
	"August",
	"September",
	"October",
	"November",
	"December"
};

size_t strftime(char *dp, size_t maxsize, const char *fp, const struct tm *timeptr)
{
	size_t ret = 0;
	size_t r = 0;
	int vary = 0;
	char *p;
	size_t len;
	char tmpbuf[10];

	if (fp == NULL || dp == NULL || maxsize <= 0)
		return 0;

	while (*fp)
	{
		if (*fp != '%')
		{
			(ret < maxsize ? (*dp++ = (*fp++), ret++) : 0);
			continue;
		}

		switch(*++fp)
		{ 
			case 'a':
				p = weekdays[timeptr->tm_wday];
				len = 3;
				goto dostrn_deep;
			case 'A':
				p = weekdays[timeptr->tm_wday];
				goto dostr_deep;
			case 'b':
				p = months[timeptr->tm_mon];
				len = 3;
				goto dostrn_deep;
			case 'B':
				p = months[timeptr->tm_mon];
				goto dostr_deep;
			case 'c': 
				r = strftime(dp, maxsize - ret, "%X %x", timeptr);
				if(r <= 0) 
					return r;
				dp += r;
				ret += r;
				break;
			case 'd':
				sprintf(tmpbuf, "%02d", timeptr->tm_mday); 
				goto dostr;
			case 'e':
				sprintf(tmpbuf, "%2d", timeptr->tm_mday); 
				goto dostr;
			case 'H':
				sprintf(tmpbuf, "%02d", timeptr->tm_hour); 
				goto dostr;
			case 'I':
				sprintf(tmpbuf, "%02d", ((timeptr->tm_hour + 11) % 12) + 1); 
				goto dostr;
			case 'j':
				sprintf(tmpbuf, "%03d", timeptr->tm_yday + 1); 
				goto dostr;
			case 'm':
				sprintf(tmpbuf, "%02d", timeptr->tm_mon + 1); 
				goto dostr;
			case 'M':
				sprintf(tmpbuf, "%02d", timeptr->tm_min); 
				goto dostr;
			case 'p':
				p = timeptr->tm_hour < 12 ? "AM" : "PM";
				goto dostr;
			case 'S':
				sprintf(tmpbuf, "%02d", timeptr->tm_sec); 
				goto dostr;
			case 'U':
			case 'W':
				vary = timeptr->tm_wday - timeptr->tm_yday % 7;
				if (*fp == 'W')
					vary--;
				vary = (vary + 7) % 7;
				sprintf(tmpbuf, "%02d", (timeptr->tm_yday + vary) / 7); 
				goto dostr;
			case 'w':
				sprintf(tmpbuf, "%02d", timeptr->tm_wday); 
				goto dostr;
			case 'x':
				r = strftime(dp, maxsize - ret, "%B %d, %Y", timeptr);
				if (r <= 0)
					return r;
				dp += r;
				ret += r;
				break;
			case 'X':
				r = strftime(dp, maxsize - ret, "%H:%M:%S", timeptr);
				if (r <= 0)
					return r;
				dp += r;
				ret += r;
				break;
			case 'y':
				sprintf(tmpbuf, "%02d", timeptr->tm_year % 100); 
				goto dostr;
			case 'Y':
				sprintf(tmpbuf, "%d", timeptr->tm_year + 1900); 
				goto dostr;
			case 'Z':
				break;
			case '%':
				(ret < maxsize ? (*dp++ = ('%'), ret++) : 0);
				break;
			dostr:
				p = tmpbuf;
			dostr_deep:
				while (*p)
					(ret < maxsize ? (*dp++ = (*p++), ret++) : 0);
				break;
			dostrn:
				p = tmpbuf;
			dostrn_deep:
				while (len-- > 0)
					(ret < maxsize ? (*dp++ = (*p++), ret++) : 0);
				break;
		}

		fp++;
	}
	
	if (ret >= maxsize)
	{
		dp[maxsize - 1] = 0;
		return 0;
	}

	*dp = 0;

	return ret;
}
