#include <ctype.h>

int tolower(int x)
{
	if (isupper(x))
		return ('a' + x - 'A');
	return x;
}
