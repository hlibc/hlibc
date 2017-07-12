#include <pthread.h>
#include "libc.h" 
#include "pthread_impl.h"
#include <stdio.h>

static struct atfork_funcs {
	void (*prepare)(void);
	void (*parent)(void);
	void (*child)(void);
	struct atfork_funcs *prev, *next;
} *funcs;

static int lock[2];

void __fork_handler(int who)
{ 
}

int pthread_atfork(void (*prepare)(void), void (*parent)(void), void (*child)(void))
{ 
	return 0;
}
static void dummy_0()
{
}

weak_alias(dummy_0, __synccall_lock);
weak_alias(dummy_0, __synccall_unlock);
weak_alias(dummy_0, __pthread_tsd_run_dtors);

void pthread_exit(void *result)
{
}

void __do_cleanup_push(struct __ptcb *, void (*)(void *), void *); 

void __do_cleanup_pop(struct __ptcb *, int); 

static int start(void *p)
{
}

#define ROUND(x) (((x)+PAGE_SIZE-1)&-PAGE_SIZE)

/* pthread_key_create.c overrides this */
static const size_t dummyno = 0;
weak_alias(dummyno, __pthread_tsd_size);

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

static void dummy(void *p)
{
}

int pthread_join(pthread_t t, void **res)
{ 
	return 0;
} 

static struct pthread main_thread;

/* pthread_key_create.c overrides this */
static const void *dummyray[1] = { 0 };
weak_alias(dummy, __pthread_tsd_main);

static int init_main_thread()
{
	if (__set_thread_area(&main_thread) < 0) return -1;
	main_thread.canceldisable = libc.canceldisable;
	main_thread.tsd = (void **)__pthread_tsd_main;
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

weak_alias(__pthread_self_def, pthread_self);
weak_alias(__pthread_self_def, __pthread_self_init);

void __testcancel(void);

void pthread_testcancel()
{
	__testcancel();
} 

static long sccp(long nr, long u, long v, long w, long x, long y, long z)
{ 
	return 0;
}

weak_alias(sccp, __syscall_cp);

static void dummy_1()
{
}

weak_alias(dummy_1, __testcancel);


void __cancel()
{
}

long __syscall_cp_asm(volatile void *, long, long, long, long, long, long, long); 

static void _sigaddset(sigset_t *set, int sig)
{ 
}

static void cancel_handler(int sig, siginfo_t *si, void *ctx)
{ 
} 

static void init_cancellation()
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
	__do_cleanup_push(cb, f, x);
}

void _pthread_cleanup_pop(struct __ptcb *cb, int run)
{
	__do_cleanup_pop(cb, run);
	if (run) cb->__f(cb->__x);
} 

weak_alias(dummy_1, __do_cleanup_push);
weak_alias(dummy_1, __do_cleanup_pop);
