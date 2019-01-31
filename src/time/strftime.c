#include <stdio.h>
#include <time.h>

size_t strftime(char *s, size_t max, const char *fmt, const struct tm *t)
{
	static char *__days3[] = {
		"Sun",
		"Mon",
		"Tues",
		"Wed",
		"Thu",
		"Fri",
		"Sat"
	};
	static char *__days[] = {
		"Sunday",
		"Monday",
		"Tuesday",
		"Wednesday",
		"Thursday",
		"Friday",
		"Saturday"
	};
	static char *__mons3[] = {
		"Jan",
		"Feb",
		"Mar",
		"Apr",
		"May",
		"Jun",
		"Jul",
		"Aug",
		"Sep",
		"Oct",
		"Nov",
		"Dec"
	};
	static char *__mons[] = {
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
	size_t ret = 0;
	size_t r = 0;
	int vary = 0;
	char *p = NULL;
	char tmpbuf[64];

	if (fmt == NULL || s == NULL || max <= 0)
		return 0;

	while (*fmt) {
		if (*fmt != '%') {
			if (ret < max) {
				*s++ = *fmt++;
				ret++;
			}
			continue;
		}

		switch(*++fmt) { 
			case 'a':
				p = __days3[t->tm_wday];
				goto string_deep;
			case 'A':
				p = __days[t->tm_wday];
				goto string_deep;
			case 'b':
				p = __mons3[t->tm_mon];
				goto string_deep;
			case 'B':
				p = __mons[t->tm_mon];
				goto string_deep;
			case 'c': 
				if ((r = strftime(s, max - ret, "%X %x", t)) <= 0)
					return r;
				s += r;
				ret += r;
				break;
			case 'd':
				sprintf(tmpbuf, "%02d", t->tm_mday); 
				goto string;
			case 'e':
				sprintf(tmpbuf, "%2d", t->tm_mday); 
				goto string;
			case 'H':
				sprintf(tmpbuf, "%02d", t->tm_hour); 
				goto string;
			case 'I':
				sprintf(tmpbuf, "%02d", ((t->tm_hour + 11) % 12) + 1); 
				goto string;
			case 'j':
				sprintf(tmpbuf, "%03d", t->tm_yday + 1); 
				goto string;
			case 'm':
				sprintf(tmpbuf, "%02d", t->tm_mon + 1); 
				goto string;
			case 'M':
				sprintf(tmpbuf, "%02d", t->tm_min); 
				goto string;
			case 'p':
				if (t->tm_hour < 12)
					p = "AM";
				else
					p = "PM";
				goto string;
			case 'S':
				sprintf(tmpbuf, "%02d", t->tm_sec); 
				goto string;
			case 'U':
			case 'W':
				vary = t->tm_wday - t->tm_yday % 7;
				if (*fmt == 'W')
					vary--;
				vary = (vary + 7) % 7;
				sprintf(tmpbuf, "%02d", (t->tm_yday + vary) / 7); 
				goto string;
			case 'w':
				sprintf(tmpbuf, "%02d", t->tm_wday); 
				goto string;
			case 'x':
				if ((r = strftime(s, max - ret, "%B %d, %Y", t)) <= 0)
					return r;
				s += r;
				ret += r;
				break;
			case 'X':
				if ((r = strftime(s, max - ret, "%H:%M:%S", t)) <= 0)
					return r;
				s += r;
				ret += r;
				break;
			case 'y':
				sprintf(tmpbuf, "%02d", t->tm_year % 100); 
				goto string;
			case 'Y':
				sprintf(tmpbuf, "%d", t->tm_year + 1900); 
				goto string;
			case 'Z':
				break;
			case '%':
				if (ret < max) {
					*s++ = '%';
					ret++;
				}
				break;
			string:
				p = tmpbuf;
			string_deep:
				while (*p) {
					if (ret < max) {
						*s++ = *p++;
						ret++;
					}
				}
				break;
		}
		fmt++;
	}
	
	if (ret >= max) {
		s[max - 1] = 0;
		return 0;
	}

	*s = 0;

	return ret;
}
