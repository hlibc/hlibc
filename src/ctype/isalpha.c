#include <ctype.h>
#include "../internal/internal.h"

int isalpha(int x)
{
	if (!(x >= 'A' && x <= 'z'))
		return 0;
	if (__isalnum[x] != -1)
		return 1;
	return 0;
}
