#include "../internal/internal.h"

int getc(FILE *fp)
{
	if (fp->ungot > 0) {
		return fp->ungotten[fp->ungot-- -1];
	}
	if (((fp)->len-- > 1)) {
		return (unsigned char)*(fp)->rp++;
	}
	return _fillbuf(fp);
}

