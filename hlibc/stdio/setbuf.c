#include "../internal/internal.h"

void setbuf(FILE *fp, char *buf)
{
	setvbuf(fp, buf, 0, BUFSIZ);
}
