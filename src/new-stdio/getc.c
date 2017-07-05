#include <gstdio.h> 
int ggetc(GFILE *fp)
{
	if ((--(fp)->len >= 0)) 
		return (unsigned char) *(fp)->rp++;

	return _fillbuf(fp);
}
