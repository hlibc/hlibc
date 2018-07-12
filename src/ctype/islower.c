#include <ctype.h>
#include "../internal/internal.h"

int islower(int x)
{
	if (x >= 'a' && x <= 'z')
		return 1;
	return 0;
}
