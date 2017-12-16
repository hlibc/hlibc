#include <pthread.h>
#include "libc.h" 
#include "pthread_impl.h"
#include <stdio.h>

static struct pthread main_thread;

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

