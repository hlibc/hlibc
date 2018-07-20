#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include "../internal/internal.h"
#include <stdint.h>
#include <sys/mman.h>
#include <errno.h>

static const size_t chunk_size = 8192;

typedef struct object
{
	size_t size;
	struct object *next;
	struct object *prev;
	int free;
} object;

static object *base = NULL;

static object *delmiddle(object *o)
{
	object *tmp = o->prev;
	o->prev->next = o->next;
	o->next->prev = o->prev;
	munmap(o, o->size + sizeof(object));
	return tmp;
}

static object *delhead(object *o)
{
	object *tmp = o->next;
	o->next->prev = NULL;
	munmap(o, o->size + sizeof(object));
	/* "base" must be reset if the head of the list is deleted */
	base = tmp;
	return tmp;
}

static object *deltail(object *o)
{
	object *tmp = o->prev;
	o->prev->next = NULL;
	munmap(o, o->size + sizeof(object));
	return tmp;
}

static object *eliminate(object *o)
{
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
	return o;
}

static object *find_free(object **last, size_t size)
{
	object *o;
	int set = 0;
	for (o = base; o ; o = o->next) {
		if (o->free == 1 && o->size >= size && set == 0) {
			set = 1;
		}else 
			o = eliminate(o);
		/* lag one link behind */
		if (set == 0)
		{
			o->free = 0;
			*last = o;
		}
	}
	return o;
}

static object *morecore(object *last, size_t size)
{
	object *o = NULL;
	int pt = PROT_READ | PROT_WRITE;
	int fs = MAP_PRIVATE | MAP_ANONYMOUS;
	size_t sum = 0;
	size_t orig = size;
	size_t mul = 1;
	size_t t = 0;

	if (size > chunk_size)
		mul += (size / chunk_size);

	if ((size_t)-1 / chunk_size < mul)
		size = orig;
	else
		size = (chunk_size * mul);

	if (__safe_uadd_sz(size, sizeof(object), &t, SIZE_MAX) == -1) {
		/* FIXME: this probably should set something other than ENOMEM */
		goto error;
	}

	if ((o = mmap(o, t, pt, fs, -1, 0)) == (void *)-1) {
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
		if (!(o = find_free(&last, size))) {
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

	memcpy(ret, ptr, o->size + sizeof(object));
	free(ptr);
	return ret;
}

void *calloc(size_t nmemb, size_t size)
{
	void *o;
	size_t t = 0;
	if(__safe_umul_sz(nmemb, size, &t, (size_t)-1) == -1) {
		/* FIXME: set errno here? */
		return NULL;
	}
	if (!(o = malloc(t))) {
		return NULL;
	}
	memset(o, 0, t);
	return o;
}

void __destroy_malloc()
{
	object *o = NULL;
	for (o = base; o; o = o->next) {
		o = eliminate(o);
	}
	if (base) {
		munmap(base, base->size + sizeof(object));
	}
}
