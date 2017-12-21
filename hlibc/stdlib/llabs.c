/* Copyright 2017, Mohammad M. Rakib */

#include <stdlib.h>

long long llabs(long long val)
{
	if (val < 0) return (-(val));
	else         return val;
}
