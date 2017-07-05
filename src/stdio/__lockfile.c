#include "stdio_impl.h"
#include "pthread_impl.h"

int __lockfile(FILE *f)
{
	int owner;
	


	__wait(&f->lock, &f->waiters, owner, 1);
	return 1;
}

void __unlockfile(FILE *f)
{
	a_store(&f->lock, 0);
	if (f->waiters) __wake(&f->lock, 1, 1);
}
