#include <stdio.h>

#include <math.h>
#include <stdint.h>
int main(void)
{
	intmax_t a = 100;
	intmax_t b = 100;
	intmax_t c = 0;

#ifdef _HAS_HLIBC_MATH
	if (__safe_add(a, b, &c) == -1)
		printf("Overflow\n");
	else
		printf("Success %jd\n", c);
	
	if (__safe_add(INTMAX_MAX, b, &c) == -1)
                printf("Overflow\n");
        else
                printf("Success %jd\n", c);

	if (__safe_sub(a, b, &c) == -1)
		printf("Overflow\n");
	else
		printf("Success %jd\n", c);
	
	if (__safe_sub(INTMAX_MIN, b, &c) == -1)
		printf("Overflow\n");
	else
		printf("Success %jd\n", c);
	
	if (__safe_sub(INTMAX_MIN + 101, b, &c) == -1)
		printf("Overflow\n");
	else
		printf("Success %jd\n", c);
	
	if (__safe_sub(INTMAX_MIN + 100, b, &c) == -1)
		printf("Overflow\n");
	else
		printf("Success %jd\n", c);

	if (__safe_sub(INTMAX_MIN + 99, b, &c) == -1)
		printf("Overflow\n");
	else
		printf("Success %jd\n", c);


#endif
	
	return 0;
}
