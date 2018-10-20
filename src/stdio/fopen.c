#include "../internal/internal.h"

FILE *fopen(const char *name, const char *mode)
{
	int fd = 0;
	FILE *o;
	int perms = 0666;
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
				goto end;
			}
			goto end;
		case 'w':
			outfile = O_TRUNC | O_CREAT | O_RDWR;
			o->write = 1;
			switch (*mode) {
			case '+':
				o->read = 1;
				outfile &= ~O_TRUNC;
				seek = SEEK_END;
				goto end;
			}
			goto end;
		case 'a':
			outfile = O_CREAT | O_APPEND;
			o->write = 1;
			seek = SEEK_END;
			switch (*mode) {
			case '+':
				outfile |= O_RDWR;
				o->read = 1;
				goto end;
			}
			goto end;
		default:
			return NULL;
		}
	}
	end:
	if (name != NULL) {
		if ((fd = open(name, outfile, perms)) == -1) {
			return NULL;
		}
	}else {
		/* activate popen mode FIXME */
		o->write = o->read = 1; 
	}

	if (seek == SEEK_END) {
		lseek(fd, 0L, seek);
	}

	o->fd = fd;

	return o;
}
