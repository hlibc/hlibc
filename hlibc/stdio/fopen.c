#include "../internal/internal.h"

FILE *fopen(const char *name, const char *mode)
{
	int fd = 0;
	FILE *fp;
	int perms     = 0666; // not yet used
	const char *p = mode;
	int oflags    = 0;
	int iflags    = 0;
	int seek      = -1;

	for (fp = _IO_stream; fp < _IO_stream + FOPEN_MAX; fp++) {
		if ((fp->flags & (_READ | _WRITE)) == 0)
			break;
	}
	if (fp >= _IO_stream + FOPEN_MAX) {
		return NULL;
	}

	while (*p) {
		switch (*p++) {
		case 'r':
			oflags = O_RDONLY;
			iflags = _READ;
			switch (*p) {
			case '+':
				oflags = O_RDWR;
				iflags = _READ | _WRITE;
				break;
			default:
				break;
			}
			break;
		case 'w':

			oflags = O_TRUNC | O_CREAT | O_RDWR;
			iflags = _WRITE;
			switch (*p) {
			case '+':
				oflags = O_RDWR | O_CREAT;
				iflags = _WRITE;
				seek   = SEEK_END;
				break;
			default:
				break;
			}
			break;
		case 'a':
			oflags = O_CREAT | O_APPEND;
			iflags = _WRITE;
			switch (*p) {
			case '+':
				oflags = O_CREAT | O_APPEND | O_RDWR;
				iflags = _READ | _WRITE;
				break;
			default:
				break;
			}
			seek = SEEK_END;
			break;
		default:
			return NULL;
		}
	}

	if (name != NULL) {
		if ((fd = open(name, oflags, perms)) == -1) {
			return NULL;
		}
	}

	if (seek == SEEK_END) {
		lseek(fd, 0L, seek);
	}

	fp->len = 0;
	fp->rp = fp->buf = NULL;
	fp->flags	= iflags;
	fp->fd		 = fd;

	return fp;
}
