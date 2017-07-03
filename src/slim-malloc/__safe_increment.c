#include <stddef.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <limits.h>

size_t _safe_add(size_t i, size_t request, size_t limit)
{
	if ((limit - i) >= request )
		return i + request;
	return limit;
}

size_t _safe_mul(size_t i, size_t request, size_t limit)
{
	if ((limit / request) <= i)
		return i * request; 
	return limit;
}

