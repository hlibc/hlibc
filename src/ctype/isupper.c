#include <ctype.h>
#include "../internal/internal.h"
int isupper(int x)
{
	if (x >= 'A' && x <= 'Z')
		return 1;
	return 0;
}
