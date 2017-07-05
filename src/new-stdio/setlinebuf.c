#include <gstdio.h>

void gsetlinebuf(GFILE *fp)
{
	gsetvbuf(fp, NULL, _LNBUF, BUFSIZ);
}
