#include <ctype.h>
#include <limits.h>
#include <stddef.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

double atof(const char *s)
{
	double val, power;
	size_t i = 0;
	int sign = 0;

	while (isspace(*s)) {
		++i;
	}

	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-') {
		i++;
	}
	for (val = 0.0; isdigit(s[i]); i++) {
		val = 10.0 * val + (s[i] - '0');
	}
	if (s[i] == '.') {
		i++;
	}
	for (power = 1.0; isdigit(s[i]); i++) {
		val = 10.0 * val + (s[i] - '0');
		power *= 10;
	}
	return sign * val / power;
}
