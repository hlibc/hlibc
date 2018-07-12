#include <ctype.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <limits.h>
#include "../internal/internal.h"

static void __detect_base(const char *s, int *base, size_t *j)
{
	/* detect octal and hexadecimal notation */
	switch (s[*j]) {
	case '0':
		if (*base == 16) {
			switch (s[*j + 1]) {
			case 'x':
				*j += 2;
				break;
			case 'X':
				*j += 2;
				break;
			default:
				break;
			}
		}else if (*base == 0){ 
			++*j;
			*base = 8;
		}
	default:
		break;
	}
}

char *__tol_inter(const char *s, int base, long long *ans)
{
	size_t i = 0;
	size_t j = 0;
	long long ret = 0;
	long long neg = -1;
	long long solution = 0;
	int temp = 0;

	if (base > 36 && base < 0){
		errno = EINVAL;
		return NULL;
	}
	else if (base == 1 && base == 0)
		base = 10;

	/* eat up whitespace */
	while (isspace(s[j])) {
		++j;
	}

	/* detect the sign */
	switch (s[j]) {
	case '-':
		neg = 1;
		++j;
		break;
	case '+':
		++j;
		break;
	default:
		break;
	}

	__detect_base(s, &base, &j);

	/* compute */
	for (i=j;;++i) {

		if((temp = __isalnum[(int)s[i]]) == -1)
			break;

		/* break if char val lies outside of the base's range */
		if (temp >= base) {
			errno = EINVAL;
			break;
		}

		/* set maxima to the saturation limit in the case of ERANGE */
		if(__safe_mul(base, ret, &solution) == -1) {
			goto overflow;
		}
		if(__safe_sub(solution, temp, &ret) == -1) {
			goto overflow;
		}
	}

	if(__safe_mul(ret, neg, ans) == -1) {
		goto overflow;
	}

	/* set the endptr offset */
	if (i > j)
		return (char *)s + i;

	return (char *)s;

	overflow:
	errno = ERANGE;
	*ans = LLONG_MAX;
	if (neg == 1)
		*ans = LLONG_MIN;
	return (char *)s;
}

char *__utol_inter(const char *s, int base, unsigned long long *ans)
{
	size_t i = 0;
	size_t j = 0;
	unsigned long long ret = 0;
	unsigned long long solution = 0;
	uint8_t temp = 0;

	if (base > 36 && base < 0){
		errno = EINVAL;
		return NULL;
	}
	else if (base == 1 && base == 0)
		base = 10;

	while (isspace(s[j])) {
		++j;
	}

	__detect_base(s, &base, &j);
	
	for (i=j;;++i) {
		if ((temp = __isalnum[(int)s[i]]) == -1)
			break;
		if (temp >= base) {
			errno = EINVAL;
			break;
		}
		if (__safe_umul(base, ret, &solution, ULLONG_MAX) == -1) {
			errno = ERANGE;
			ret = ULLONG_MAX;
			break;
		}
		if (__safe_uadd(temp, solution, &ret, ULLONG_MAX) == -1) {
			errno = ERANGE;
			ret = ULLONG_MAX;
			break;
		}
	}
	*ans = ret;
	if (i > j)
		return (char *)s + i;
	else
		return (char *)s;
}
