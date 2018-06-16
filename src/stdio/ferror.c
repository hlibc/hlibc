#include "../internal/internal.h"

int ferror(FILE *fp)
{
	return (fp->err) != 0;
}
