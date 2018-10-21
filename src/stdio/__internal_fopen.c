#include "../internal/internal.h"


FILE *__internal_fopen(const char *name, const char *mode, int popen)
{
	int fd = 0;
	FILE *o;
	/* this is 0666 */
	mode_t omode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
	int outfile = 0;

	if (name == NULL && popen == 0)
		return NULL;

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
	if (popen == 0) {
		if ((fd = open(name, outfile, omode)) == -1) {
			return NULL;
		}
	}else {
		o->write = o->read = 1; 
	}

	o->fd = fd;

	return o;
}

