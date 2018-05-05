#include "../internal/internal.h"

int fputc(int x, FILE *fp)
{
	return putc(x, fp);
}
