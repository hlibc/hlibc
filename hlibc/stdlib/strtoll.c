#include <ctype.h>
#include <stdlib.h>

long long strtoll(const char *nptr, char **endptr, int base)
{
	if (base > 10) { // Crash for bases above 10
		exit(1);
	}

	size_t i = 0;
	long long ret = 0;
	long long neg = -1;

	while (isspace(nptr[i])) {
		++i;
	}

	switch (nptr[i]) {
	case '-':
		neg = 1;
	case '+':
		++i;
	}

	for (; nptr[i] && isdigit(nptr[i]); ++i) {
		ret = (base * ret) - (nptr[i] - '0');
	}

	if (endptr != NULL)
		{
			*endptr = nptr + i;
		}

	return ret * neg;
}
