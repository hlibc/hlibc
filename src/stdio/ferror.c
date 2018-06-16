#include "../internal/internal.h"

int ferror(FILE *fp)
{
	return (fp->f.err) != 0;
}
