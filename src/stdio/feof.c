#include "../internal/internal.h"

int feof(FILE *fp)
{
	if ((fp->f.eof) != 0) {
		return 0;
	}
	return 1;
}
