#include <stdio.h>
#include <time.h>

/*
	This strftime implementation is in its early stages
	* and + are not implemented.
*/

size_t strftime(char *s, size_t max, const char *fmt, const struct tm *t)
{
	static char *days3[] = {
		"Sun",
		"Mon",
		"Tue",
		"Wed",
		"Thu",
		"Fri",
		"Sat"
	};
	static char *days[] = {
		"Sunday",
		"Monday",
		"Tuesday",
		"Wednesday",
		"Thursday",
		"Friday",
		"Saturday"
	};
	static char *mons3[] = {
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
	static char *mons[] = {
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
	static char *ampm[] = {
		"AM",
		"PM"
	};
	size_t ret = 0;
	size_t tmp = 0;
	int vary = 0;
	char *p = NULL;
	char tmpbuf[64];
	char *st = s; /* save the caller's pointer position */

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
				p = days3[t->tm_wday];
				goto string_deep;
			case 'A':
				p = days[t->tm_wday];
				goto string_deep;
			case 'b':
				p = mons3[t->tm_mon];
				goto string_deep;
			case 'B':
				p = mons[t->tm_mon];
				goto string_deep;
			case 'c': 
				if ((tmp = strftime(s, max - ret, "%X %x", t)) <= 0)
					return tmp;
				s += tmp;
				ret += tmp;
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
					p = ampm[0];
				else
					p = ampm[1];
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
				if ((tmp = strftime(s, max - ret, "%B %d, %Y", t)) <= 0)
					return tmp;
				s += tmp;
				ret += tmp;
				break;
			case 'X':
				if ((tmp = strftime(s, max - ret, "%H:%M:%S", t)) <= 0)
					return tmp;
				s += tmp;
				ret += tmp;
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
				/* TODO: should these be <= ?, and can it be a condition of the outer loop */
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
	
	if (ret > max) {
		/* when ret > max, C99 says to return 0 and the contents are unspecified */
		/* we nul terminate in order to suppress potential security flaws */
		st[max - 1] = 0;
		return 0;
	}

	*s = 0;

	return ret;
}


