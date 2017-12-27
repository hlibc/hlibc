#include <stdlib.h>

ldiv_t ldiv(long int numerator, long int denominator)
{
	ldiv_t ret;
	lldiv_t ret_ = lldiv(numerator, denominator);

	ret.quot = ret_.quot;
	ret.rem = ret_.rem;

	return ret;
}
