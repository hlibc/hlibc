#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include "../internal/internal.h"
#include <stdint.h>
#include <sys/mman.h>
#include <errno.h>

static const size_t chunk_size = 512;

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

// shoot for a 64 unit granularity [512, 32768]
#define HASH 16777216
#define WRAP 32768
#define HASHSIZE 512

static flist *hashtab[HASHSIZE];
static flist *_fhead[HASHSIZE];

static size_t hash(size_t i)
{ 
	i %= HASH; // this should call a new table
	return i / WRAP;
}

static flist *delmiddle(flist *o)
{
	flist *tmp = o->prev;
	o->prev->next = o->next;
	o->next->prev = o->prev;
	munmap(o, sizeof(flist));
	return tmp;
}

static int addfreenode(object *node)
{
	size_t hashv = hash(node->size);
	flist *o = NULL; 
	flist *last = _fhead[hashv]; 

	if (!(o = __mmap_inter(sizeof(flist)))) {
		return 1;
	}

	if (last) {
		last->next = o;
	}
	o->next = NULL;
	o->prev = last;
	o->node = node; 
	_fhead[hashv] = o;
	if (!(hashtab[hashv])) { 
		 hashtab[hashv] = o;
	}
	return 0;
}

static object *findfree(size_t size)
{
	object *t = NULL;
	object *ret = NULL; 
	size_t i = hash(size);
	flist *o = NULL;

	for (; i < HASHSIZE && ret == NULL; ++i, d = 1) {
		for (o = hashtab[i]; o ; o = o->next) {
			t = o->node;
			if (t == NULL || o == _fhead[i] || o == hashtab[i])
				continue;
			if (t->size >= size && ret == NULL) {
				o = delmiddle(o);
				ret = t;
				break;
			}else {
				
				o = delmiddle(o);
				munmap(t, t->size + sizeof(object));
			}
		}
	}
	return ret;
}

static object *morecore(size_t size)
{
	object *o = NULL; 

	size_t sum = 0;
	size_t orig = size;
	size_t mul = 1;
	size_t t = 0;

	if (size > chunk_size)
		mul += (size / chunk_size);

	if ((size_t)-1 / chunk_size < mul)
		size = orig;
	else {
		size = (chunk_size * mul);
	}

	if (__safe_uadd_sz(size, sizeof(object), &t, SIZE_MAX) == -1) {
		goto error;
	}

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

