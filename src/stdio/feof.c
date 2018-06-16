#include "../internal/internal.h"

int feof(FILE *fp)
{
	if ((fp->eof) != 0) {
		return 0;
	}
	return 1;
}
