#include "../internal/internal.h"
#include <limits.h>
#include <string.h>
#include <stdlib.h>
int __fscanf_inter(FILE *restrict stream, const char *restrict format, va_list ap)
{
	char *p = NULL;
	size_t i = 0;
	size_t bound = INT_MAX;
	char *sval = NULL;
	char s[1000] = { 0 };
	size_t j = 0;
	int c = 0;
	int *ints = NULL;
	
	for (p = (char *)format; *p && i < bound; p++) {
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
			break;
		case 'd': 
			ints = va_arg(ap, int *);
			for (s[0] = 0, c = 0, j = 0;((c = fgetc(stream)) != ' ');++j) {
				s[j] = c;
			}
			s[j] = 0;
			*ints = strtol(s, NULL, 10);
			break;
		}
	}
	return i;
}


int fscanf(FILE *stream, const char *fmt, ...)
{
	int ret = 0;
        va_list argptr;
        va_start(argptr, fmt);
        ret = __fscanf_inter(stream, fmt, argptr);
        va_end(argptr);
        return ret;
}
