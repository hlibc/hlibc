#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include "../internal/internal.h"
#include <stdint.h>
#include <sys/mman.h>
#include <errno.h>

typedef struct object
{
	size_t size;
	struct object *next;
	struct object *prev;
	int free;
} object;

typedef struct freelist
{ 
	struct freelist *next;
	struct freelist *prev;
	struct object *freenode;
}freelist;

static object *base = NULL;
static object *head = NULL;


static freelist *fbase = NULL;
static freelist *fhead = NULL;

static const size_t chunk_size = 8192;

static object *delmiddle(object *o)
{
	object *tmp = o->prev;
	o->prev->next = o->next;
	o->next->prev = o->prev;
	munmap(o, o->size + sizeof(object));
	return tmp;
}

static object *__delmiddle(object *o)
{ 
	if (o->next && o->prev && o != head && o != base)
		o = delmiddle(o);
	return o;
}

static object *find_free(size_t size)
{
	object *o;
	object *ret = NULL;

	for (o = base; o ; o = o->next) {
		if (o->free == 1 && o->size >= size && ret == NULL) {
			ret = o;
			break;
		}else if (o->free == 1) {
			o = __delmiddle(o); 
		}
	}
	return ret;
}

static object *morecore(size_t size)
{
	object *o = NULL;
	int pt = PROT_READ | PROT_WRITE;
	int fs = MAP_PRIVATE | MAP_ANONYMOUS;
	size_t sum = 0;
	size_t orig = size;
	size_t mul = 1;
	size_t t = 0;
	object *last = head;

	if (size > chunk_size)
		mul += (size / chunk_size);

	if ((size_t)-1 / chunk_size < mul)
		size = orig;
	else
		size = (chunk_size * mul);

	if (__safe_uadd_sz(size, sizeof(object), &t, SIZE_MAX) == -1) {
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
	head = o;
	return o;

	error:
	errno = ENOMEM;
	return NULL;
}

static freelist *addfreenode(freelist *unused, object *node)
{ 
	freelist *o = NULL;
	int pt = PROT_READ | PROT_WRITE;
	int fs = MAP_PRIVATE | MAP_ANONYMOUS;
	size_t t = sizeof(freelist);
	freelist *last = fhead;
	
	if ((o = mmap(o, t, pt, fs, -1, 0)) == (void *)-1) {
		return NULL;
	}
	
	if (last) {
		last->next = o;
	}
	o->next = NULL;
	o->prev = last;
	o->freenode = node;
	fhead = o;
	return o;
}


void *malloc(size_t size)
{
	object *o;
	if (!(o = find_free(size))) {
		if (!(o = morecore(size))) {
			return NULL;
		}
	}
	if (!base)
		base = o;

	o->free = 0;
	return (o + 1);
}

void free(void *ptr)
{
	object *o;
	if (!ptr) {
		return;
	}
	/*
		This object should be added to the free list 
	*/
	o = (object *)ptr - 1;
	o->free = 1;
	addfreenode(NULL, o);
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
	size_t t = 0;
	if(__safe_umul_sz(nmemb, size, &t, (size_t)-1) == -1) { 
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
		o = __delmiddle(o);
	}

	if (base) {
		munmap(base, base->size + sizeof(object));

	}
	return;
	if (head) {
		munmap(head, head->size + sizeof(object));
	}
}

