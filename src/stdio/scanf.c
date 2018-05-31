int scanf(const char *format, ...)
{
	int ret = 0;
	va_list argptr;
	va_start(argptr, fmt);
	ret = _scanf_inter(stdin, NULL, 0, 0, fmt, argptr);
	va_end(argptr);
	return ret;
}
