#include "../internal/internal.h"

int fclose(FILE *fp)
{
	int ret = 0;
	if (fp != NULL) {
		fflush(fp);
		fp->len = 0;
		fp->ungot = 0;
		fp->read = 0;
		fp->write = 0;
		if (fp->pid == 0) {
			if (!(close(fp->fd))){
				ret = EOF;
			}
		}
		fp->pid = 0;
	}
	return ret;
}

