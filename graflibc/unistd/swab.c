#include <unistd.h>

void swab(const void *from, void *to, ssize_t n)
{
	ssize_t i = 0;
	const char *fromm = from;
	char tmp;
	char tmpp;
	char *too = to;
	for (i = 0; i < n; i += 2)
	{
		tmp = *(fromm + i);
		tmpp = *(fromm + i + 1);
		*(too + i) = tmpp;
		*(too + i + 1) = tmp;
	}
}
