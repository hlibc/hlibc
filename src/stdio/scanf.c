#include "../internal/internal.h"
#include <limits.h>
#include <string.h>
#include <stdlib.h>

int __fscanf_inter(const char *str, FILE *restrict stream, const char *restrict format, va_list ap)
{
	char *p = NULL;
	size_t i = 0;
	char *sval = NULL;
	char s[1000] = { 0 };
	size_t j = 0;
	int c = 0;
	int *ints = NULL;
	
	for (p = (char *)format; *p; p++) {
		if (*p != '%') {
			   fgetc(stream);
			   continue;
		}
		++p;
		switch (*p) {
                case 's':
			sval = va_arg(ap, char *);
			for (c = 0, j = 0;((c = fgetc(stream)) != ' ');++j) {
				sval[j] = c;
			}
			i+=j;
			break;
		case 'd': 
			ints = va_arg(ap, int *);
			for (s[0] = 0, c = 0, j = 0;((c = fgetc(stream)) != ' ');++j) {
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

