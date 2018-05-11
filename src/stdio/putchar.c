#include "../internal/internal.h"
int putchar(int x)
{
	return putc(x, stdout);
}
