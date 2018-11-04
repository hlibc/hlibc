#include "../internal/internal.h"

int vscanf(const char *fmt, va_list ap)
{
	int ret = 0;
	ret = __fscanf_inter(NULL, stdin, fmt, ap);
	va_end(ap);
	return ret;
}

