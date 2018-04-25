#include <ctype.h>

int isspace(int x)
{
	switch (x) {
	case ' ':
	case '\t':
	case '\n':
	case '\r':
	case '\f':
	case '\v':
		return 1;
	default:
	    return 0;
	}
}
