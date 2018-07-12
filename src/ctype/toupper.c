#include <ctype.h>

int toupper(int x)
{
	if (islower(x)) 
		return ('A' + x - 'a');
	return x;
}
