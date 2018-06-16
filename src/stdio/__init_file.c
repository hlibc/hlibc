#include "../internal/internal.h"

FILE *__init_file(FILE *o)
{
        o->read = o->write = o->lnbuf = o->unbuf = o->eof = o->err = o->len = 0;
        o->pid = o->ungot = o->ungotten[0] = 0;
        o->buf = o->rp = NULL;
        return o;
}

