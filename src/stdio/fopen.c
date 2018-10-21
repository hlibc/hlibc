#include "../internal/internal.h"

FILE *fopen(const char *name, const char *mode)
{
	return __internal_fopen(name, mode, 0);
}
