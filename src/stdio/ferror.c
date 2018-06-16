#include "../internal/internal.h"

int ferror(FILE *fp)
{
	return (fp->flags & _ERR) != 0;
}
