#include <stdio.h> 
int getc(FILE *fp)
{
	if ((--(fp)->len >= 0)) 
		return (unsigned char) *(fp)->rp++;

	return _fillbuf(fp);
}
