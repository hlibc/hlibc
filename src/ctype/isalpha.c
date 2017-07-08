#include <ctype.h>

int isalpha(int x) 
{ 
	if (isupper(x) || islower(x))
		return 1;
	return 0;
}
