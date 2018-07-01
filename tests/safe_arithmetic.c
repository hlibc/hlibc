#include <stdio.h>

#include <math.h>
#include <stdint.h>
int main(void)
{
	int a = 100;
	int b = 100;
	int c = 0;

#ifdef _HAS_HLIBC_MATH
	if (__safe_add(a, b, &c) == -1)
		printf("Overflow\n");
	else
		printf("Success %d\n", c);
	
	if (__safe_sub(a, b, &c) == -1)
		printf("Overflow\n");
	else
		printf("Success %d\n", c);
#endif
	
	return 0;
}
