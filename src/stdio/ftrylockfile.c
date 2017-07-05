#include "stdio_impl.h"

int ftrylockfile(FILE *f)
{ 
	if (f->lock < 0) f->lock = 0;
	if (f->lock )
		return -1;
	f->lockcount = 1;
	return 0;
}
