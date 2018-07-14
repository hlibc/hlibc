#include <stdio.h>
#include <math.h>
#include <stdint.h>

int main(void)
{

#ifdef _HAS_HLIBC_MATH
	
	intmax_t a = 100;
	intmax_t b = 100;
	intmax_t c = 0;
	
	printf("========================================\n");
	printf("should equal 200 (100 + 100)\n");
	if (__safe_add(a, b, &c) == -1)
		printf("Overflow\n");
	else
		printf("Success %jd\n", c);
	
	printf("========================================\n");
	printf("should overflow (INTMAX_MAX + 100)\n");
	if (__safe_add(INTMAX_MAX, b, &c) == -1)
		printf("Overflow\n");
	else
		printf("Success %jd\n", c);

	printf("========================================\n");
	printf("should overflow (INTMAX_MIN + -1)\n");
	if (__safe_add(INTMAX_MIN, -1, &c) == -1)
		printf("Overflow\n");
	else
		printf("Success %jd\n", c);

	printf("========================================\n");
	printf("should not overflow ((INTMAX_MIN +100) + -99)\n");
	if (__safe_add(INTMAX_MIN + 100, -99, &c) == -1)
		printf("Overflow\n");
	else
		printf("Success %jd\n", c);

	printf("========================================\n");
	printf("should equal zero (100 - 100)\n");
	if (__safe_sub(a, b, &c) == -1)
		printf("Overflow\n");
	else
		printf("Success %jd\n", c);
	 
	printf("========================================\n");
	printf("should overflow (INTMAX_MIN + 100)\n");
	if (__safe_sub(INTMAX_MIN, b, &c) == -1)
		printf("Overflow\n");
	else
		printf("Success %jd\n", c);
	
	printf("========================================\n");
	printf("should not overflow ((INTMAX_MIN + 100) - 101)\n");
	if (__safe_sub(INTMAX_MIN + 101, b, &c) == -1)
		printf("Overflow\n");
	else
		printf("Success %jd\n", c);
	
	printf("========================================\n");
	printf("should not overflow ((INTMAX_MIN + 100) - 100)\n");
	if (__safe_sub(INTMAX_MIN + 100, b, &c) == -1)
		printf("Overflow\n");
	else
		printf("Success %jd\n", c);

	printf("========================================\n");
	printf("should overflow ((INTMAX_MIN + 99) - 100)\n");
	if (__safe_sub(INTMAX_MIN + 99, b, &c) == -1)
		printf("Overflow\n");
	else
		printf("Success %jd\n", c);


	printf("========================================\n");
	printf("should overflow (INTMAX_MIN - 1)\n");
	if (__safe_sub(INTMAX_MIN, 1, &c) == -1)
		printf("Overflow\n");
	else
		printf("Success %jd\n", c);
	
	printf("========================================\n");
	printf("should not overflow (1 - INTMAX_MAX)\n");
	if (__safe_sub(1, INTMAX_MAX, &c) == -1)
		printf("Overflow\n");
	else
		printf("Success %jd\n", c);
	
	printf("========================================\n");
	printf("should not overflow (1 - (INTMAX_MAX - 1))\n");
	if (__safe_sub(1, INTMAX_MAX -1, &c) == -1)
		printf("Overflow\n");
	else
		printf("Success %jd\n", c);

	printf("========================================\n");
	printf("should not overflow (1 - (INTMAX_MAX - 4))\n");
	if (__safe_sub(1, INTMAX_MAX -4, &c) == -1)
		printf("Overflow\n");
	else
		printf("Success %jd\n", c);

#endif
	
	return 0;
}
