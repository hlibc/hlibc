#include "../internal/internal.h"

int puts(const char *s)
{
	return __puts_inter(s, stdout, '\n');
}
