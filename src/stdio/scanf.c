#include "../internal/internal.h"
#include <limits.h>
#include <string.h>
#include <stdlib.h>

typedef int (*__scan)(FILE *o, const char *s);

int __fgetc(FILE *o, const char *s)
{
	(void)s;
	return fgetc(o);
}

int __sscan(FILE *o, const char *s)
{
	(void)o;
	static size_t i = 0;
	return s[i++];
}

int __fscanf_inter(const char *str, FILE *restrict o, const char *restrict fmt, va_list ap)
{
	char *p = NULL;
	size_t i = 0;
	char *sval = NULL;
	char s[1000] = { 0 };
	size_t j = 0;
	int c = 0;
	int *ints = NULL;
	__scan f;

	if (!(str))
		f = __fgetc;
	else
		f = __sscan;
	
	for (p = (char *)fmt; *p; p++) {
		if (*p != '%') {
			/* FIXME */
			f(o, str);
			continue;
		}
		++p;
		switch (*p) {
                case 's':
			sval = va_arg(ap, char *);
			for (c = 0, j = 0;((c = f(o, str)) != ' ');++j) {
				sval[j] = c;
			}
			i+=j;
			break;
		case 'd': 
			ints = va_arg(ap, int *);
			for (s[0] = 0, c = 0, j = 0;((c = f(o, str)) != ' ');++j) {
				s[j] = c;
			}
			s[j] = 0;
			*ints = strtol(s, NULL, 10);
			i+=j;
			break;
		default:
			goto eof;
		}
	}
	return i;
	eof:
	return EOF;
}


int fscanf(FILE *stream, const char *fmt, ...)
{
	int ret = 0;
        va_list argptr;
        va_start(argptr, fmt);
        ret = __fscanf_inter(NULL, stream, fmt, argptr);
        va_end(argptr);
        return ret;
}

int scanf(const char *fmt, ...)
{
	int ret = 0;
        va_list argptr;
        va_start(argptr, fmt);
        ret = __fscanf_inter(NULL, stdin, fmt, argptr);
        va_end(argptr);
        return ret;
}

int sscanf(const char *str, const char *fmt, ...)
{
	int ret = 0;
        va_list argptr;
        va_start(argptr, fmt);
        ret = __fscanf_inter(str, stdin, fmt, argptr);
        va_end(argptr);
        return ret;
}

int vscanf(const char *fmt, va_list ap)
{
	int ret = 0;
	ret = __fscanf_inter(NULL, stdin, fmt, ap);
	va_end(ap);
}

int vsscanf(const char *str, const char *fmt, va_list ap)
{
	int ret = 0;
	ret = __fscanf_inter(str, stdin, fmt, ap);
	va_end(ap);
}

int vfscanf(FILE *stream, const char *fmt, va_list ap)
{
	int ret = 0;
	ret = __fscanf_inter(NULL, stream, fmt, ap);
	va_end(ap);
}

