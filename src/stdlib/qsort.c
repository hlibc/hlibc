#include <stdlib.h>

struct qsort
{
	char* arr;
	size_t len;
	size_t size;
	int (*cmp) (const void *, const void *);
};

static char *element(struct qsort *qs, size_t i)
{
	return &qs->arr[qs->size * i];
}

static void swap(struct qsort *qs, size_t A, size_t B)
{
	char *a = element(qs, A);
	char *b = element(qs, B);
	size_t i = 0;
	char tmp;

	for( ; i < qs->size ; ++i )
	{
		tmp = a[i];
		a[i] = b[i];
		b[i] = tmp;
	}
}

void qsort(void *base, size_t nmemb, size_t size, int (*compar) (const void *, const void *))
{
	struct qsort qs;

	qs.arr = base;
	qs.len = nmemb;
	qs.size = size;
	qs.cmp = compar;
}
