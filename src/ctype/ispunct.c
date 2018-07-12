#include <ctype.h>
#include "../internal/internal.h"

int ispunct(int x)
{	
	if (!(x >= '!' && x <= '~'))
		return 0;
	if (__isalnum[x] == -1)
		return 1;
	return 0;
}
