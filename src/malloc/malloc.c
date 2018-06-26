#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include "../internal/internal.h"
#include <stdint.h>
#include <sys/mman.h>
#include <errno.h>

#define __HLIBC_PAGE 10000

typedef struct object
{
	size_t size;
	struct object *next;
	struct object *prev;
	int free;
} object;

object *base = NULL;

object *delmiddle(object *o)
{
	object *tmp = o->prev;
	o->prev->next = o->next;
	o->next->prev = o->prev;
	munmap(o, o->size + sizeof(object));
	return tmp;
}

object *delhead(object *o)
{
	object *tmp = o->next;
	o->next->prev = NULL;
	munmap(o, o->size + sizeof(object));
	/* "base" must be reset if the head of the list is deleted */
	base = tmp;
	return tmp;
}

object *deltail(object *o)
{
	object *tmp = o->prev;
	o->prev->next = NULL;
	munmap(o, o->size + sizeof(object));
	return tmp;
}

object *_traverse_list(object *o)
{
	for (o = base; o; o = o->next) {
		if (o->free == 1) {
			if (o->next == NULL) {
				o = deltail(o);
			}
			else if (o->prev == NULL) {
				o = delhead(o);
			}
			else {
				o = delmiddle(o);
			}
		}
	}
	return o;
}

object *find_free_object(object **last, size_t size)
{
	object *o;
	for (o = base; o && !(o->free && o->size >= size); o = o->next) {
		*last = o;
	}
	o = _traverse_list(o);
	return o;
}

object *morecore(object *last, size_t size)
{
	object *o = NULL;
	int pt = PROT_READ | PROT_WRITE;
	int fs = MAP_PRIVATE | MAP_ANONYMOUS;
	size_t sum = 0;

	size_t i = 1;
	static size_t real = __HLIBC_PAGE;
	static size_t manylarge = 0;
	static size_t manysmall = 0;

	if (size < __HLIBC_PAGE)
	{
		size = __HLIBC_PAGE;
		manysmall++;
	}

	while (size > real)
	{
		real += __HLIBC_PAGE;
		manylarge++;
		
	}
	if (real != __HLIBC_PAGE && manylarge > manysmall)
	{
		size = real;
	}

	if ((sum = _safe_addition(size, sizeof(object), SIZE_MAX)) == 0) {
		goto error;
	}

	if ((o = mmap(o, sum, pt, fs, -1, 0)) == (void *)-1) {
		goto error;
	}

	if (last) {
		last->next = o;
	}
	o->size = size;
	o->next = NULL;
	o->prev = last;
	o->free = 0;
	return o;

	error:
	errno = ENOMEM;
	return NULL;
}

void *malloc(size_t size)
{
	object *o;
	object *last;

	if (!base) {
		if (!(o = morecore(NULL, size))) {
			return NULL;
		}
		base = o;
	}
	else {
		last = base;
		if (!(o = find_free_object(&last, size))) {
			if (!(o = morecore(last, size))) {
				return NULL;
			}
		}
		else {
			o->free = 0;
		}
	}
	return (o + 1);
}

void free(void *ptr)
{
	object *o;
	if (!ptr) {
		return;
	}
	o = (object *)ptr - 1;
	o->free = 1;
}

void *realloc(void *ptr, size_t size)
{
	void *ret;
	object *o;
	if (!ptr) {
		return malloc(size);
	}

	o = (object *)ptr - 1;
	if (o->size >= size) {
		return ptr;
	}

	if (!(ret = malloc(size))) {
		return NULL;
	}

	memcpy(ret, ptr, o->size);
	free(ptr);
	return ret;
}

void *calloc(size_t nmemb, size_t size)
{
	void *o;
	size = _safe_multiply(nmemb, size, (size_t)-1);
	if (!(o = malloc(size))) {
		return NULL;
	}
	memset(o, 0, size);
	return o;
}

void _destroy_malloc()
{
	object *p = NULL;
	p = _traverse_list(p);
	if (base) {
		munmap(base, base->size + sizeof(object));
	}
}
