#ifndef LIBC_H
#define LIBC_H

#include <stdlib.h>
#include <stdio.h>

struct __libc { 
	size_t *auxv;
	int (*atexit)(void (*)(void));
	void (*fini)(void);
	void (*ldso_fini)(void);
};


#if !defined(__PIC__) || 100*__GNUC__+__GNUC_MINOR__ >= 303 || defined(__PCC__) || defined(__TINYC__)

#ifdef __PIC__
#if __GNUC__ < 4
#define BROKEN_VISIBILITY 1
#endif
#define ATTR_LIBC_VISIBILITY __attribute__((visibility("hidden"))) 
#else
#define ATTR_LIBC_VISIBILITY
#endif

extern struct __libc __libc ATTR_LIBC_VISIBILITY;
#define libc __libc

#else

#define USE_LIBC_ACCESSOR
#define ATTR_LIBC_VISIBILITY
extern struct __libc *__libc_loc(void) __attribute__((const));
#define libc (*__libc_loc())

#endif 

extern char **__environ;
#define environ __environ

#endif


#ifndef _SYSCALL_H
#define _SYSCALL_H

/* This header is mostly useless leftover wrapper cruft */
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/syscall.h>
#include <stdint.h>
int brk(void *);
void *sbrk(intptr_t);

#define socketcall __socketcall

#endif
