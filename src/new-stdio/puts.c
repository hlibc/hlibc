#include <gstdio.h> 

int gputs(const char *s)
{
	return __puts_inter(s, gstdout, '\n');
}

