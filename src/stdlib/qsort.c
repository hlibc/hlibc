#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _stack {
	char **buf;
	size_t ptr;
	size_t len;
} Stack;

typedef int (*comp)(const void *, const void *);
char *_partition(char *l, char *r, size_t width, comp fn);
void _swap(char *i, char *j, size_t width);
void stack_new(Stack *s, size_t len);
void stack_free(Stack *s);
void stack_grow(Stack *s);
void stack_push(Stack *s, char *ptr);
char *stack_pop(Stack *s);

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  qsort
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/*
 * qsort: generic qsort function.
 */
void qsort(void *base, size_t nel, size_t width, comp fn)
{
	Stack stack, *buf;
	char *b, *e, *l, *r, *p;
	buf = &stack;

	/* nel the total count becomes an index, if there is nothing to sort;
	 * return. */
	if (nel > 1)
		nel--;
	else
		return;

	stack_new(buf, nel);

	b = base;
	e = b+nel*width;

	stack_push(buf, b);
	stack_push(buf, e);

	/* When the stack is empty the sorting is complete */
	while (buf->ptr > 0)
	{
		r = stack_pop(buf);
		l = stack_pop(buf);

		/* Divide and sort */
		p = _partition(l, r, width, fn);

		if(p > b)
			if ((fn)(p-width, l) > 0) {
				stack_push(buf, l);
				stack_push(buf, p-width);
			}

		if (p < e)
			if ((fn)(p+width, r) < 0) {
				stack_push(buf, p+width);
				stack_push(buf, r);
			}
	}
	stack_free(buf);
}

/*
 * _partition: Divides and sorts the given array, l and r are the extremities of
 * the worked section of the array and the width is the size of each array item
 * in bytes.
 */
char *_partition(char *l, char *r, size_t width, comp fn)
{
	char *i;
	int t;

	for (i = l, t = 0; i < r; i += width, t = 0)
		if ((t = (fn)(i, r)) < 0) {
			_swap(l, i, width);
			l += width;
		} else if (t == 0) {
			/* If the comparison returns 0, swap only if l and i
			 * are not the same object; This check avoids a lot of
			 * unessasary swapping. */
			if (l != i)
				_swap(l, i, width);
			l += width;
		}

	_swap(l, r, width);

	return l;
}

/*
 * Swap for 'width' places.
 */
void _swap(char *l, char *r, size_t width)
{
	char tmp[256];
	size_t len;

	while (width) {
		len = (sizeof tmp < width) ? sizeof tmp : width;
		memcpy(tmp, l, len);
		memcpy(l, r, len);
		memcpy(r, tmp, len);
		l += len;
		r += len;
		width -= len;
	}
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  Stack
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void stack_new(Stack *s, size_t len)
{
	s->len = len;
	s->ptr = 0;
	s->buf = malloc(len * sizeof(char*));
}

void stack_free(Stack *s)
{
	free(s->buf);
}

void stack_grow(Stack *s)
{
	s->len += s->len;
	s->buf = realloc(s->buf, s->len);
}

void stack_push(Stack *s, char *ptr)
{
	if (s->ptr == s->len)
		stack_grow(s);
	
	s->ptr++;
	s->buf[(s->ptr - 1)] = ptr;
}

char *stack_pop(Stack *s)
{
	return s->buf[(s->ptr--) - 1];
}

