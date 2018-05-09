#include <ctype.h>

int isblank(int x)
{
	switch (x) {
	case ' ':
	case '\t':
		return 1;
	default:
		return 0;
	}
}