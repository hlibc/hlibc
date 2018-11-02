#include "../internal/internal.h"
#include <limits.h>


int __fscanf_inter(FILE *restrict stream, const char *restrict format, va_list ap)
{
	char *p = NULL;
	size_t i = 0;
	size_t bound = INT_MAX;
	char *sval = NULL;
	size_t j = 0;
	
	for (p = (char *)format; *p && i < bound; p++) {
		if (*p != '%') {
			   fgetc(stream);
			   continue;
		}
		++p;
		switch (*p) {
                case 's':
			sval = va_arg(ap, char *);
			for (j=0;sval[j];++j)
				fgetc(stream);
			break;
		}
	}
	return 0;
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
