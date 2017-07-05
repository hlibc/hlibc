#include <gstdio.h>

int gputc(int x, GFILE *fp)
{
	if ((--(fp)->len >= 0))
	{
		if (x == '\n' && (fp->flags & _LNBUF))
		{
			*(fp)->rp++ = x;
			return _flushbuf(EOF, fp);
		}
		return *(fp)->rp++ = x;
	}
	return _flushbuf(x, fp);
}

