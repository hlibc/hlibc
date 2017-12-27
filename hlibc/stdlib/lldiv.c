#include <stdlib.h>
/*
        Copyright 2017 Adrian Parvin D. Ouano
*/
lldiv_t lldiv(long long numerator, long long denominator)
{
	lldiv_t ret;

	ret.quot = numerator/denominator;

	#ifdef HARDWARE_MULTIPLIER
	ret.rem = numerator - ret.quot*denominator;
	#else
	ret.rem = numerator%denominator;
	#endif

	return ret;
}
