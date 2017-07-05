#include <gstdio.h>

void gsetbuf(GFILE *fp, char *buf)
{
	gsetvbuf(fp, buf, 0, BUFSIZ);
}
