#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include "../internal/internal.h"
#include <stdint.h>
#include <sys/mman.h>
#include <errno.h>
/*
	2^16 = 65536
	65536/512 = 128 

	2^21 = 2097152
	2097152 / 512 = 4096

	2^22 = 4194304
	4194304 / 512 = 8192
*/
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


#define HASH 2097152
#define HASHSIZE (HASH / 512)

static flist *hashtab[HASHSIZE];
static flist *_fhead[HASHSIZE];
static flist *_fbase[HASHSIZE];


static size_t hash(size_t i)
{ 
	i %= HASH;
	return i / 512;
}

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
		_fbase[hashv] = o;
	}
	return 0;
}

static object *findfree(size_t size)
{
	object *t = NULL;
	object *ret = NULL; 
	size_t hashv = hash(size);
	flist *o = NULL;
	
	size_t i = hashv;


	for (; i < HASHSIZE && ret == NULL; ++i) {
		for (o = hashtab[i]; o ; o = o->next) {
			t = o->node;
			if (t == NULL || o == _fhead[i] || o == _fbase[i])
				continue;
			if (t->size >= size) {
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
        else
                size = (chunk_size * mul);

        if (__safe_uadd_sz(size, sizeof(object), &t, SIZE_MAX) == -1) {
                /* FIXME: this probably should set something other than ENOMEM */
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


static object *lookup(size_t i)
{
	flist *o = NULL;
	object *t = NULL;

	for (o = hashtab[hash(i)]; o != NULL; o = o->next) {
		t = o->node;
		if (t->size >= i) {
			delmiddle(o);
			return t;
		}
	}
	return NULL;
}

