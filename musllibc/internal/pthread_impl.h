#ifndef _PTHREAD_IMPL_H
#define _PTHREAD_IMPL_H

#include <pthread.h>
#include <sched.h>
#include <signal.h>
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>
#include <limits.h>
#include <inttypes.h>
#include <setjmp.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include "libc.h"
#include "syscall.h"
#include "atomic.h"
#include "futex.h"

#define pthread __pthread

struct pthread {
	struct pthread *self;
	void *dtv, *unused1, *unused2;
	uintptr_t sysinfo;
	uintptr_t canary;
	pid_t tid, pid;
	int tsd_used, errno_val, *errno_ptr;
	/* All cancellation-related fields must remain together, in order */
	volatile uintptr_t cp_sp, cp_ip;
	volatile int cancel, canceldisable, cancelasync;
	unsigned char *map_base;
	size_t map_size;
	void *start_arg;
	void *(*start)(void *);
	void *result;
	int detached;
	int exitlock;
	struct __ptcb *cancelbuf;
	void **tsd;
	pthread_attr_t attr;
	volatile int dead;
	struct {
		void **head;
		long off;
		void *pending;
	} robust_list;
	int unblock_cancel;
	int delete_timer;
	locale_t locale;
	int killlock;
};

struct __timer {
	int timerid;
	pthread_t thread;
};

#include "pthread_arch.h"

pthread_t __pthread_self_init(void);
#define DEFAULT_STACK_SIZE (16384-PAGE_SIZE)
#define DEFAULT_GUARD_SIZE PAGE_SIZE

#endif
