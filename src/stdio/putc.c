#include "../internal/internal.h"

int putc(int x, FILE *fp)
{
	if ((fp->len-- > 1)) {
		if (x == '\n' && (fp->lnbuf == 1)) {
			*(fp)->rp++ = x;
			return __flushbuf(EOF, fp);
		}
		return *(fp)->rp++ = x;
	}
	return __flushbuf(x, fp);
}
