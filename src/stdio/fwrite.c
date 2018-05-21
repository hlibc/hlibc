#include "../internal/internal.h"

size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *fp)
{
	size_t request = size * nmemb;
	size_t ret = 0;
	size_t i = 0;
	size_t j = 0;
	size_t k = 0;
	char *t = ptr;
	if ((fp->flags & _LNBUF)) {
		for (i=0; i<request;++i, ++k) {
			if (t[k] == '\n') {
				ret += write(fp->fd, t + j, i);
				j = i;
				i = 0;
			}
		}
	}
	else {
		ret = write(fp->fd, ptr, request);
	}
	return ret / size;
}

