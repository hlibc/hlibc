#include "../internal/internal.h"

FILE *fopen(const char *name, const char *mode)
{
	int fd = 0;
	FILE *o;
	mode_t omode = 0666;
	int outfile = 0;

	for (o = _IO_stream; o < _IO_stream + FOPEN_MAX; o++) {
		if (o->read == 0 && o->write == 0) {
			break;
		}
	}
	if (o >= _IO_stream + FOPEN_MAX) {
		return NULL;
	}

	o = __init_file(o);

	for (;*mode;++mode) {
		switch (*mode) {
		case 'r':
			outfile |= O_RDONLY;
			o->read = 1; 
			goto i;
		case 'w':
			outfile |= O_TRUNC;
			outfile |= O_CREAT;
			outfile |= O_WRONLY;
			o->write = 1; 
			goto i;
		case 'a':
			outfile |= O_CREAT;
			outfile |= O_APPEND;
			o->write = 1; 
			goto i;
		case 'b':
			goto i;
		case '+':
			outfile |= O_RDWR;
			outfile &= ~O_WRONLY;
			outfile &= ~O_RDONLY;
			o->read = 1;
			o->write = 1; 
			goto i;
		}
		i:;
	}
	if (name != NULL) {
		if ((fd = open(name, outfile, omode)) == -1) {
			return NULL;
		}
	}else {
		/* activate popen mode FIXME */
		o->write = o->read = 1; 
	}

	o->fd = fd;

	return o;
}
