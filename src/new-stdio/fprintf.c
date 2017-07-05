#include <gstdio.h> 

int gfprintf(GFILE *stream, const char *fmt, ...)
{
	int ret = 0;
	va_list argptr;
	va_start(argptr, fmt);
	ret = _gprintf_inter(stream, NULL, 0, 0, fmt, argptr);
	va_end(argptr);
	return ret;
}
