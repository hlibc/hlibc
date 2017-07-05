#include <gstdio.h> 

int gvfprintf(GFILE *stream, const char *fmt, va_list argptr)
{
	int ret = 0;
	ret = _gprintf_inter(stream, NULL, 0, 0, fmt, argptr);
	va_end(argptr);
	return ret;
}
