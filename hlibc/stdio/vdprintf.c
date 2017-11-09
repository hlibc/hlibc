#include <stdio.h> 

int vdprintf(int fd, const char *fmt, va_list argptr)
{
	int ret = 0;
	ret = _printf_inter(stdin + fd, NULL, 0, 0, fmt, argptr);
	va_end(argptr);
	return ret;
}
