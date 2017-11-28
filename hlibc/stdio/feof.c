#include "../internal/internal.h"

int feof(FILE *fp)
{
	if ((fp->flags & _EOF) != 0)
		return 0;
	return 1;
}
