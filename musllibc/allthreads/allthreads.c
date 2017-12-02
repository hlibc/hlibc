#include <pthread.h>
#include "libc.h" 
#include "pthread_impl.h"
#include <stdio.h>

int pthread_atfork(void (*prepare)(void), void (*parent)(void), void (*child)(void))
{ 
	return 0;
}

void pthread_exit(void *result)
{
}

void __do_cleanup_push(struct __ptcb *, void (*)(void *), void *); 

void __do_cleanup_pop(struct __ptcb *, int); 

static int start(void *p)
{
} 

static void init_file_lock(FILE *f)
{ 
}

int pthread_create(pthread_t *res, const pthread_attr_t *attr, void *(*entry)(void *), void *arg)
{ 
	return 0;
} 

int pthread_join(pthread_t t, void **res)
{ 
	return 0;
} 

static struct pthread main_thread;

/* pthread_key_create.c overrides this */
static int init_main_thread()
{
	if (__set_thread_area(&main_thread) < 0) return -1;
	main_thread.canceldisable = libc.canceldisable;
	main_thread.tsd = NULL;
	main_thread.errno_ptr = __errno_location();
	main_thread.self = &main_thread;
	main_thread.tid = main_thread.pid =
		__syscall(SYS_set_tid_address, &main_thread.tid);
	libc.main_thread = &main_thread;
	return 0;
}

pthread_t __pthread_self_def()
{
	static int init, failed;
	if (!init) {
		if (failed) return 0;
		if (init_main_thread() < 0) failed = 1;
		if (failed) return 0;
		init = 1;
	}
	return __pthread_self();
}

void pthread_testcancel()
{
} 

void __cancel()
{
}

int pthread_cancel(pthread_t t)
{
	return 0;
} 

void _pthread_cleanup_push(struct __ptcb *cb, void (*f)(void *), void *x)
{
	cb->__f = f;
	cb->__x = x;
}

void _pthread_cleanup_pop(struct __ptcb *cb, int run)
{
	if (run) cb->__f(cb->__x);
} 



