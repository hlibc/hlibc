#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include "../internal/internal.h"
#include "../../musllibc/internal/syscall.h"
#include <sys/mman.h>
#include <errno.h>

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
	if (size < 64) {
		size = 64;
	}
	if ((o = mmap(o, size + sizeof(object), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0))
	    == (void *)-1) {
		return NULL;
	}
	if (last) {
		last->next = o;
	}

	o->size = size;
	o->next = NULL;
	o->prev = last;
	o->free = 0;
	return o;
}
void *malloc(size_t size)
{
	object *o;
	object *last;
	if (size <= 0) {
		return NULL;
	}

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

void *calloc(size_t nelem, size_t elsize)
{
	size_t size = 0;
	void *ptr;
	size = _safe_multiply(nelem, elsize, (size_t)-1);
	if (!(ptr = malloc(size))) {
		return NULL;
	}
	else {
		memset(ptr, 0, size);
	}

	return ptr;
}

void _destroy_malloc()
{
	object *p = NULL;
	p = _traverse_list(p);
	if (base) {
		munmap(base, base->size + sizeof(object));
	}
}
