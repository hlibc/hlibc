#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include "../internal/internal.h"
#include <stdint.h>
#include <sys/mman.h>
#include <errno.h>
#include <limits.h>

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

typedef struct chain
{ 
	flist **magazine;
	flist **_fhead;
}chain;

static chain **tchain; 

/* shoot for a 64 unit granularity ~[512, 32768) as (32768/512 = 64) */
#define TWOTO32 4294967296			/* 2^32 */
#define HASHSIZE TWOTO32 / (256*512*64)		/* ~2^32 / 2^23 = ~512 */
#define CHAINLEN TWOTO32 / (256*512*128)	/* ~2^32 / 2^24 = ~256 */
#define WRAP TWOTO32 / (HASHSIZE*CHAINLEN)	/* ~2^32 / (~256*~512) = ~32768 */
#define HASH TWOTO32 / CHAINLEN			/* ~2^32 / ~256 = ~16777216 */

static const size_t chunk_size = 4096;

static size_t magno(size_t i)
{
	return i / HASH;
}

static size_t hash(size_t i)
{
	return i / WRAP;
}

static void initmag(size_t i)
{
	size_t z = magno(i);

	if (!tchain)
		tchain = __mmap_inter(sizeof(chain *) * CHAINLEN);

	chain *c = tchain[z]; 
	if (c == NULL) {
		c = __mmap_inter(sizeof (chain));
	}

	if (!c->magazine)
	{
		c->magazine = __mmap_inter(sizeof (flist) * HASHSIZE);
		c->_fhead = __mmap_inter(sizeof (flist) * HASHSIZE);
	
	}
	tchain[z] = c;
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
	size_t z = magno(node->size);
	chain *c = tchain[z];
	flist *last = c->_fhead[hashv]; 

	if (!(o = __mmap_inter(sizeof(flist)))) {
		return 1;
	}

	if (last) {
		last->next = o;
	}
	o->next = NULL;
	o->prev = last;
	o->node = node; 
	c->_fhead[hashv] = o;
	if (!(c->magazine[hashv])) { 
		 c->magazine[hashv] = o;
	}
	tchain[z] = c;
	return 0;
}

static object *findfree(size_t size)
{
	object *t = NULL;
	object *ret = NULL; 
	size_t i = hash(size);
	size_t z = magno(size);
	flist *o = NULL;
	chain *c;
	
	for (; z < CHAINLEN && ret == NULL; ++z) {
		c = tchain[z];
		 for (; c && i < HASHSIZE && ret == NULL; ++i) {
			for (o = c->magazine[i]; o ; o = o->next) {
				t = o->node;
				if (t == NULL || o == c->_fhead[i] || o == c->magazine[i])
					continue;
				if (t->size >= size && ret == NULL) {
					o = delmiddle(o);
					ret = t;
					break;
				}else {
					o = delmiddle(o);
					munmap(t, t->size + sizeof(object));
					t = NULL;
				}
			}
		}
		i = 0;
		tchain[z] = c;
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
		goto NULL;
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
	if (size >= TWOTO32)
	{
		goto core;
	}
	initmag(size);
	object *o;
	if (!(o = findfree(size))) {
		core:
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
	if (o->size >= TWOTO32) {
		munmap(o, o->size);
		return;
	}
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

