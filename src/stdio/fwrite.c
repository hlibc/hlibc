#include "../internal/internal.h"

size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *fp)
{
	size_t request = size * nmemb;
	size_t ret = 0;
	size_t j = 0;
	size_t k = 0;
	const char *t = ptr;
	if ((fp->lnbuf)) {
		for (k=0; k<request; ++k) {
			if (t[k] == '\n') {
				ret += write(fp->fd, t + j, k - j + 1);
				j = k + 1;
			}
		}
		if (j < k) {
			ret += write(fp->fd, t + j, k - j);
		}
	}
	else {
		ret = write(fp->fd, ptr, request);
	}
	return ret / size;
}

