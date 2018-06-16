#include "../internal/internal.h"

int fflush(FILE *fp)
{
	int ret = 0;
	size_t i = 0;
	/* fflush(NULL) flushes all fd */
	if (fp == NULL) {
		for (fp = stdout; i < FOPEN_MAX; ++fp, ++i) {
			if (fp->buf != NULL) {
				ret = __flushbuf(EOF, fp);
			}
		}
	}
	else if (fp->f.write == 1) {
		ret = __flushbuf(EOF, fp);
	}

	fp->len = BUFSIZ;
	if (fp->f.unbuf == 1)
		fp->len = 1;
	return ret;
}
