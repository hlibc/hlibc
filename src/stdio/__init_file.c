#include "../internal/internal.h"

FILE *__init_file(FILE *f)
{
        f->read = f->write = f->lnbuf = f->unbuf = f->eof = f->err = f->len = 0;
        f->pid = f->ungot = f->ungotten[0] = 0;
        f->buf = f->rp = NULL;
        return f;
}

