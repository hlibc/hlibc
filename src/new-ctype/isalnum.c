#include <ctype.h>
int isalnum(int x)
{ 
	if (isalpha(x) || isdigit(x))
		return 1;
	return 0;
}
