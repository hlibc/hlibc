#include <stdlib.h>

typedef struct
{
	char* arr;
	size_t len;
	size_t size;
	int (*cmp) (const void *, const void *);
} qsort_t;

static char *element(qsort_t *qs, size_t i)
{
	return &qs->arr[qs->size * i];
}

static int compare(qsort_t *qs, size_t A, size_t B)
{
	return qs->cmp(element(qs, A), element(qs, B));
}

static void swap(qsort_t *qs, size_t A, size_t B)
{
	char *a;
	char *b;
	size_t i;
	char tmp;

	a = element(qs, A);
	b = element(qs, B);
	i = 0;

	for( ; i < qs->size ; ++i )
	{
		tmp = a[i];
		a[i] = b[i];
		b[i] = tmp;
	}
}

static void sort(qsort_t *qs);

void qsort(void *base, size_t nmemb, size_t size, int (*compar) (const void *, const void *))
{
	qsort_t qs;

	qs.arr = base;
	qs.len = nmemb;
	qs.size = size;
	qs.cmp = compar;

	sort(&qs);
}
