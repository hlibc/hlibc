#include "pthread_impl.h"
#include <stdio.h>

static void dummy_0()
{
}
weak_alias(dummy_0, __synccall_lock);
weak_alias(dummy_0, __synccall_unlock);
weak_alias(dummy_0, __pthread_tsd_run_dtors);

void pthread_exit(void *result)
{
}

void __do_cleanup_push(struct __ptcb *cb, void (*f)(void *), void *x)
{
}

void __do_cleanup_pop(struct __ptcb *cb, int run)
{ 
}

static int start(void *p)
{
}

#define ROUND(x) (((x)+PAGE_SIZE-1)&-PAGE_SIZE)

/* pthread_key_create.c overrides this */
static const size_t dummy = 0;
weak_alias(dummy, __pthread_tsd_size);

static FILE *const dummy_file = 0;
weak_alias(dummy_file, __stdin_used);
weak_alias(dummy_file, __stdout_used);
weak_alias(dummy_file, __stderr_used);

static void init_file_lock(FILE *f)
{ 
}

int pthread_create(pthread_t *res, const pthread_attr_t *attr, void *(*entry)(void *), void *arg)
{ 
	return 0;
}
