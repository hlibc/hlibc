#include "../internal/internal.h"

FILE *__init_file(FILE *o)
{
	o->read = o->write = o->lnbuf = o->unbuf = o->eof = o->err = 0;
	o->pid = o->ungot = o->ungotten[0] = 0;
	o->buf = o->rp = NULL;
	o->len = 1; // this is the actual size_t adjusted "zero"
	return o;
}

