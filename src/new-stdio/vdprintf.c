#include <gstdio.h> 

int gvdprintf(int fd, const char *fmt, va_list argptr)
{
	int ret = 0;
	ret = _gprintf_inter(gstdin + fd, NULL, 0, 0, fmt, argptr);
	va_end(argptr);
	return ret;
}
