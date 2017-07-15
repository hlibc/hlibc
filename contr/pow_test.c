#include <stdio.h>

#include <math.h>

int main(void)
{
	double n = 4;
	printf("This number should be (16.000000): %lf    (4^3)\n", pow(n, 2));
	printf("This number should be (15.580524): %lf    (3.3^2.3)\n", pow(3.3, 2.3));
}
