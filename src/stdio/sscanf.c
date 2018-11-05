#include "../internal/internal.h"


int vsscanf(const char *str, const char *fmt, va_list ap)
{
	int ret = 0;
	ret = __fscanf_inter(str, NULL, fmt, ap);
	va_end(ap);
	return ret;
}

