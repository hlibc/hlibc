#include <stdio.h> 

int fprintf(FILE *stream, const char *fmt, ...)
{
	int ret = 0;
	va_list argptr;
	va_start(argptr, fmt);
	ret = _printf_inter(stream, NULL, 0, 0, fmt, argptr);
	va_end(argptr);
	return ret;
}
