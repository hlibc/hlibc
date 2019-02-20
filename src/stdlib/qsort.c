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

	if(nmemb > 1)
	{
		qs.arr = base;
		qs.len = nmemb;
		qs.size = size;
		qs.cmp = compar;
		sort(&qs);
	}
}

static size_t parent(size_t i)
{
	return (i - 1) / 2;
}

static size_t leftchild(size_t i)
{
	return (i * 2) + 1;
}

static size_t rightchild(size_t i)
{
	return (i * 2) + 2;
}

static void siftdown(qsort_t *qs, size_t root, size_t end)
{
	size_t node;
	size_t lchild;
	size_t rchild;

	node = root;

	while((rchild = rightchild(node)) <= end)
	{
		lchild = leftchild(node);
		node = (compare(qs, rchild, lchild) > 0) ? rchild : lchild;
	}

	if((lchild = leftchild(node)) <= end)
	{
		node = lchild;
	}

	while(compare(qs, root, node) > 0)
	{
		node = parent(node);
	}

	while(node > root)
	{
		swap(qs, node, root);
		node = parent(node);
	}
}

static void heapify(qsort_t *qs)
{
	size_t end;
	size_t node;

	node = parent(end = qs->len - 1);

	while(node > 0)
	{
		siftdown(qs, node--, end);
	}

	siftdown(qs, node, end);
}

static void sort(qsort_t *qs)
{
	size_t node;

	heapify(qs);

	node = qs->len - 1;

	while(node > 0)
	{
		swap(qs, 0, node);
		siftdown(qs, 0, --node);
	}
}
