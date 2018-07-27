#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef int (*comp)(const void *, const void *);
static void swap(void *v, size_t i, size_t j, size_t width);

/*
 * qsort:	generic qsort function.
 */
void qsort(void *base, size_t nel, size_t width, comp fn)
{
	unsigned char *b = (void*)base;
	size_t i, left, last;

	left = 0;
	if (nel)
		nel--;

	if (left >= nel)
		return;

	swap(b, left, nel/2, width);

	last = left;
	for (i = left+1; i <= nel; i++)
		if ((fn)(&b[i*width], &b[left*width]) < 0)
			swap(b, ++last, i, width);

	swap(b, left, last, width);

	qsort(b+(left*width), last-left, width, fn);
	qsort(b+((last+1)*width), nel-last, width, fn);
}

/*
 * Swap for 'width' places, 'i' to 'j' on the given string.
 */
static void swap(void *string, size_t i, size_t j, size_t width)
{
	if (i == j)
		return; /* return directly if swap is not required */

	unsigned char t;
	unsigned char *s = string;

	i = i*width;
	j = j*width;

	size_t k;
	for (k = 0; k < width; k++) {
		t        = *(s+k+i);
		*(s+k+i) = *(s+k+j);
		*(s+k+j) = t;
	}
}
