#include <inttypes.h>

/*
	Copyright 2017 Evgeniy Popov
*/

intmax_t imaxabs(intmax_t num)
{
	if (num < 0) {
		return -num;
	}
	return num;
}
