#include <ctype.h>
#include "../internal/internal.h"

int isxdigit(int x)
{
	if (!(x >= '0' && x <= 'f'))
		return 0;
	if (__isxdigit[x] != -1)
		return 1;
	return 0;
}
