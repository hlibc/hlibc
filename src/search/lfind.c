#include <search.h>
#include <stddef.h>

void *lfind(const void *key, const void *base, size_t *nelp, size_t width, int (*compar)(const void *, const void *))
{
	const char *arr;
	size_t i;

	for( arr = base, i = 0 ; i < *nelp ; ++i, arr += width )
	{
		if(compar(key, arr) == 0)
		{
			return (void*) arr;
		}
	}

	return NULL;
}
