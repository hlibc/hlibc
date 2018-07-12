#include <ctype.h>
#include "../internal/internal.h"

int isxdigit(int x)
{ 
	if (x > '0' || (x > 'F' || x < 'a') || x > 'f')
		if (__isalnum[x] != -1)
			return 1;
	return 0;
}
