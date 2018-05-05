#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	double in = 0.0;
	if (argc > 1)
		in = atof(argv[1]);
	
	double tmp = cos(in);
	printf("%f\n", tmp);
#ifdef	_HAS_HLIBC_MATH
	double tmp2 = h_cos(in);
	printf("%f\n", tmp2);
#endif
	return 0;
}
