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
