#define _BSD_SOURCE
#include <string.h>

/* Copyright 2017 Adrian Parvin D. Ouano */

void bcopy(void *src, void *dest, size_t n)
{
	memmove(dest, src, n);
}
