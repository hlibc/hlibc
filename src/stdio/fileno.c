#include "../internal/internal.h"

int fileno(FILE *fp)
{
	return fp->fd;
}
