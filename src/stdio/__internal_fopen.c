#include "../internal/internal.h"

FILE *__internal_fopen(const char *name, const char *mode, int type)
{
	int fd = 0;
	FILE *o = NULL;
	/* this is 0666 */
	mode_t omode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
	int outfile = 0;
	// type == 1 == fopen, type == 0 == normal, type == 2 == tmpfile
	// O_CREAT and O_EXCL

	if (name == NULL && type == 0)
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
			break;
		case 'w':
			outfile |= O_WRONLY|O_CREAT|O_TRUNC;
			o->write = 1; 
			break;
		case 'a':
			outfile |= O_WRONLY|O_CREAT|O_APPEND;
			o->write = 1; 
			break;
		case 'b':
			break;
		case '+':
			outfile |= O_RDWR;
			outfile &= ~(O_RDONLY|O_WRONLY);
			o->read = o->write = 1; 
			break;
		default:
			__init_file(o);
			return NULL;
		}
	}

	if (type == 0 || type == 2) {
		if (type == 2) /* this is used by tmpfile */
			outfile |= O_CREAT|O_EXCL;
		if ((fd = open(name, outfile, omode)) == -1) {
			return NULL;
		}
	}else {
		o->write = o->read = 1; 
	}

	o->fd = fd;

	return o;
}

