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
} object;

typedef struct flist
{
	struct flist *next; 
	struct flist *prev; 
	object *node;
}flist;

static flist *fbase = NULL;
static flist *fhead = NULL;

static flist *delmiddle(flist *o)
{
	flist *tmp = o->prev;
	o->prev->next = o->next;
	o->next->prev = o->prev;
	munmap(o, sizeof(flist));
	return tmp;
}

static void * __mmap_inter(size_t size)
{
	static const int pt = PROT_READ | PROT_WRITE;
	static const int fs = MAP_PRIVATE | MAP_ANONYMOUS;
	void *o = NULL;
	if ((o = mmap(o, size, pt, fs, -1, 0)) == (void *)-1) {
		return NULL;
	}
	return o;
}

static int addfreenode(object *node)
{
	flist *o = NULL; 
	flist *last = fhead;

	if (!(o = __mmap_inter(sizeof(flist)))) {
		return 1;
	}

	if (last) {
		last->next = o;
	}
	o->next = NULL;
	o->prev = last;
	o->node = node;
	fhead = o;
	if (!(fbase)) {
		fbase = o; 
	}
	return 0;
}

static object *findfree(size_t size)
{
	object *t = NULL;
	object *ret = NULL;
	flist *o = NULL;

	for (o = fbase; o ; o = o->next) { 
		t = o->node;
		if (t == NULL || o == fbase || o == fhead)
			continue;
		if (t->size >= size )
		{
			o = delmiddle(o);
			ret = t;
			break;
		}else {
			munmap(t, t->size + sizeof(object));
			o = delmiddle(o);
		}
	}
	return ret;
}

static object *morecore(size_t size)
{
	object *o = NULL; 
	if (!(o = __mmap_inter(size + sizeof(object)))) {
		goto error;
	} 
	o->size = size;
	return o;

	error:
	errno = ENOMEM;
	return NULL;
}

void *malloc(size_t size)
{
	object *o;
	if (!(o = findfree(size))) {
		if (!(o = morecore(size))) {
			return NULL;
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
	addfreenode(o);
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

