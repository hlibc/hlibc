#include <stdio.h>
#include <time.h>

size_t strftime(char *s, size_t max, const char *fmt, const struct tm *t)
{
	static char *__days[] = {
		"Sunday",
		"Monday",
		"Tuesday",
		"Wednesday",
		"Thursday",
		"Friday",
		"Saturday"
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
	size_t len = 0;
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
				p = __days[t->tm_wday];
				len = 3;
				goto dostrn_deep;
			case 'A':
				p = __days[t->tm_wday];
				goto dostr_deep;
			case 'b':
				p = __mons[t->tm_mon];
				len = 3;
				goto dostrn_deep;
			case 'B':
				p = __mons[t->tm_mon];
				goto dostr_deep;
			case 'c': 
				if ((r = strftime(s, max - ret, "%X %x", t)) <= 0)
					return r;
				s += r;
				ret += r;
				break;
			case 'd':
				sprintf(tmpbuf, "%02d", t->tm_mday); 
				goto dostr;
			case 'e':
				sprintf(tmpbuf, "%2d", t->tm_mday); 
				goto dostr;
			case 'H':
				sprintf(tmpbuf, "%02d", t->tm_hour); 
				goto dostr;
			case 'I':
				sprintf(tmpbuf, "%02d", ((t->tm_hour + 11) % 12) + 1); 
				goto dostr;
			case 'j':
				sprintf(tmpbuf, "%03d", t->tm_yday + 1); 
				goto dostr;
			case 'm':
				sprintf(tmpbuf, "%02d", t->tm_mon + 1); 
				goto dostr;
			case 'M':
				sprintf(tmpbuf, "%02d", t->tm_min); 
				goto dostr;
			case 'p':
				if (t->tm_hour < 12)
					p = "AM";
				else
					p = "PM";
				goto dostr;
			case 'S':
				sprintf(tmpbuf, "%02d", t->tm_sec); 
				goto dostr;
			case 'U':
			case 'W':
				vary = t->tm_wday - t->tm_yday % 7;
				if (*fmt == 'W')
					vary--;
				vary = (vary + 7) % 7;
				sprintf(tmpbuf, "%02d", (t->tm_yday + vary) / 7); 
				goto dostr;
			case 'w':
				sprintf(tmpbuf, "%02d", t->tm_wday); 
				goto dostr;
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
				goto dostr;
			case 'Y':
				sprintf(tmpbuf, "%d", t->tm_year + 1900); 
				goto dostr;
			case 'Z':
				break;
			case '%':
				if (ret < max) {
					*s++ = '%';
					ret++;
				}
				break;
			dostr:
				p = tmpbuf;
			dostr_deep:
				len = max;
				goto dostrn_deep;
			dostrn:
				p = tmpbuf;
			dostrn_deep:
				while (len-- > 0 && *p) {
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
