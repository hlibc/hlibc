#include <gctype.h>
#include <gstdlib.h>
#include <gstddef.h>
#include <gstring.h>
#include <glimits.h>
#include <gstddef.h>

double gatof(const char *s)
{
	double val, power;
	static size_t i = 0;
	int sign = 0;
	if (isspace(*s))
		gatof(s + ++i);
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')
		i++;
	for (val = 0.0; isdigit(s[i]); i++)
		val = 10.0 * val + (s[i] - '0');
	if (s[i] == '.')
		i++;
	for (power = 1.0; isdigit(s[i]); i++) 
	{
		val = 10.0 * val + (s[i] - '0');
		power *= 10;
	}
	return sign * val / power;
}
