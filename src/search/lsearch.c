#include <search.h>
#include <string.h>

void *lsearch(const void *key, void *base, size_t *nelp, size_t width, int (*compar)(const void *, const void *))
{
	char* elem = lfind(key, base, nelp, width, compar);

	if(elem == NULL)
	{
		elem = base;
		elem += (*nelp)++ * width;
		memcpy(elem, key, width);
	}

	return elem;
}
