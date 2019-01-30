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
 "Saturday",
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
 "December",
 };

size_t
strftime(s, maxsize, format, timeptr)
char *s;
size_t maxsize;
const char *format;
const struct tm *timeptr;
{
register char *fp = format;
register char *dp = s;
register size_t ret = 0;

if(format == ((void*)0) || s == ((void*)0) || maxsize <= 0)
 return 0;



while(*fp != '\0')
 {
 char *p;
 int len;
 char tmpbuf[10];

 if(*fp != '%')
  {
  (ret < maxsize ? (*dp++ = (*fp++), ret++) : 0);
  continue;
  }

 fp++;

 switch(*fp)
  {

  case 'a':
   p = weekdays[timeptr->tm_wday]; len = 3; goto dostrn;
   break;

  case 'A':
   p = weekdays[timeptr->tm_wday]; goto dostr;
   break;

  case 'b':
   p = months[timeptr->tm_mon]; len = 3; goto dostrn;
   break;

  case 'B':
   p = months[timeptr->tm_mon]; goto dostr;
   break;

  case 'c':
   { size_t r = strftime(dp, maxsize - ret, "%X %x", timeptr); if(r <= 0) return r; dp += r; ret += r; };
   break;

  case 'd':
   sprintf(tmpbuf, "%02d", timeptr->tm_mday); p = tmpbuf; goto dostr;
   break;

  case 'e':
   sprintf(tmpbuf, "%2d", timeptr->tm_mday); p = tmpbuf; goto dostr;
   break;

  case 'H':
   sprintf(tmpbuf, "%02d", timeptr->tm_hour); p = tmpbuf; goto dostr;
   break;

  case 'I':
   sprintf(tmpbuf, "%02d", ((timeptr->tm_hour + 11) % 12) + 1); p = tmpbuf; goto dostr;
   break;

  case 'j':
   sprintf(tmpbuf, "%03d", timeptr->tm_yday + 1); p = tmpbuf; goto dostr;
   break;

  case 'm':
   sprintf(tmpbuf, "%02d", timeptr->tm_mon + 1); p = tmpbuf; goto dostr;
   break;

  case 'M':
   sprintf(tmpbuf, "%02d", timeptr->tm_min); p = tmpbuf; goto dostr;
   break;

  case 'p':
   p = timeptr->tm_hour < 12 ? "AM" : "PM"; goto dostr;

   break;

  case 'S':
   sprintf(tmpbuf, "%02d", timeptr->tm_sec); p = tmpbuf; goto dostr;
   break;

  case 'U':
  case 'W':
   {
   int fudge = timeptr->tm_wday - timeptr->tm_yday % 7;
   if(*fp == 'W')
    fudge--;
   fudge = (fudge + 7) % 7;
   sprintf(tmpbuf, "%02d", (timeptr->tm_yday + fudge) / 7); p = tmpbuf; goto dostr;
   break;
   }

  case 'w':
   sprintf(tmpbuf, "%02d", timeptr->tm_wday); p = tmpbuf; goto dostr;
   break;

  case 'x':
   { size_t r = strftime(dp, maxsize - ret, "%B %d, %Y", timeptr); if(r <= 0) return r; dp += r; ret += r; };
   break;

  case 'X':
   { size_t r = strftime(dp, maxsize - ret, "%H:%M:%S", timeptr); if(r <= 0) return r; dp += r; ret += r; };
   break;

  case 'y':
   sprintf(tmpbuf, "%02d", timeptr->tm_year % 100); p = tmpbuf; goto dostr;
   break;

  case 'Y':
   sprintf(tmpbuf, "%d", timeptr->tm_year + 1900); p = tmpbuf; goto dostr;
   break;

  case 'Z':

   break;

  case '%':
   (ret < maxsize ? (*dp++ = ('%'), ret++) : 0);
   break;

dostr: while(*p != '\0')
    (ret < maxsize ? (*dp++ = (*p++), ret++) : 0);
   break;

dostrn: while(len-- > 0)
    (ret < maxsize ? (*dp++ = (*p++), ret++) : 0);
   break;
  }

 fp++;
 }

if(ret >= maxsize)
 {
 s[maxsize - 1] = '\0';
 return 0;
 }

*dp = '\0';

return ret;
}
