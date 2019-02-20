/*
	setjmp.h
	Copyright (c) 2019, zhiayang
*/

#ifndef _SETJMP_H
#define _SETJMP_H

#include <bits/types.h>

int setjmp(jmp_buf env);
void longjmp(jmp_buf env, int val);

#endif
