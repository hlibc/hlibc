#include "../internal/internal.h"

FILE *fopen(const char *name, const char *mode)
{
	int fd = 0;
	FILE *o;
	int perms = 0666; // not yet used
	int outfile = 0;
	int seek = -1;

	for (o = _IO_stream; o < _IO_stream + FOPEN_MAX; o++) {
		if (o->read == 0 && o->write == 0) {
			break;
		}
	}
	if (o >= _IO_stream + FOPEN_MAX) {
		return NULL;
	}

	o = __init_file(o);

	while (*mode) {
		switch (*mode++) {
		case 'r':
			outfile |= O_RDONLY;
			o->read = 1;
			switch (*mode) {
			case '+':
				outfile |= O_RDWR;
				o->write = 1;
				break;
			default:
				break;
			}
			break;
		case 'w':
			outfile = O_TRUNC | O_CREAT | O_RDWR;
			o->write = 1;
			switch (*mode) {
			case '+':
				outfile &= ~O_TRUNC; 
				seek = SEEK_END;
				break;
			default:
				break;
			}
			break;
		case 'a':
			outfile = O_CREAT | O_APPEND;
			o->write = 1;
			switch (*mode) {
			case '+':
				outfile |= O_RDWR;
				o->read = 1;
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
		if ((fd = open(name, outfile, perms)) == -1) {
			return NULL;
		}
	}

	if (seek == SEEK_END) {
		lseek(fd, 0L, seek);
	}

	o->fd = fd;

	return o;
}
