#include "../internal/internal.h"

void setlinebuf(FILE *fp)
{
	setvbuf(fp, NULL, _LNBUF, BUFSIZ);
}
