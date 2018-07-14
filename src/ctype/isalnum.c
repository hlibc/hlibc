#include <ctype.h>
#include "../internal/internal.h"

int isalnum(int x)
{
	if (!(x >= '0' && x <= 'z'))
		return 0;
	if(__isalnum[x] != -1)
		return 1;
	return 0;
}
