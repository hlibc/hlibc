#include <errno.h>
#include <string.h>
#include "../internal/internal.h"

char *strerror(int m)
{
	if (m < 133 && m > 0)
		return __errno_table[m];
	else
		return "Error not known by hlibc";
}
