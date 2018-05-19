#include "../internal/internal.h"

int getc(FILE *fp)
{
	if (((fp)->len-- > 1)) {
		return (unsigned char)*(fp)->rp++;
	}
	return _fillbuf(fp);
}

