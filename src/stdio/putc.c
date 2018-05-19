#include "../internal/internal.h"

int putc(int x, FILE *fp)
{
	if (((fp)->len-- > 1)) {
		if (x == '\n' && (fp->flags & _LNBUF)) {
			*(fp)->rp++ = x;
			return _flushbuf(EOF, fp);
		}
		return *(fp)->rp++ = x;
	}
	return _flushbuf(x, fp);
}
