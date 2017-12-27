#include <stdlib.h>

div_t div(int numerator, int denominator)
{
	div_t ret;
	lldiv_t ret_ = lldiv(numerator, denominator);

	ret.quot = ret_.quot;
	ret.rem = ret_.rem;

	return ret;
}
