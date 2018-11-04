#include "../internal/internal.h"

int vfscanf(FILE *stream, const char *fmt, va_list ap)
{
	int ret = 0;
	ret = __fscanf_inter(NULL, stream, fmt, ap);
	va_end(ap);
	return ret;
}

