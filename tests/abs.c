/* Copyright 2017, Mohammad M. Rakib */

#include <stdlib.h>

int main(void)
{
	int a = -5;
	long b = -11;
	long long c = -42;

	if (abs(a) == 5) return 0;
	else             return 1;

	if (labs(a) == 11) return 0;
	else               return 1;

	if (llabs(a) == 42) return 0;
	else                return 1;

	return 0;
}
