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

static const size_t chunk_size = 8192;
static int usedl = 0;
#define MAGLIM 512
uintptr_t reftable[MAGLIM];

object *magazine[MAGLIM];

typedef struct flist
{
        struct flist *next; 
        struct flist *prev; 
	object *node;
        uintptr_t val;
}flist;

static flist *fbase;
static flist *fhead;

static uintptr_t fheadval = 0;
static uintptr_t fbaseval = 0;

static flist *delmiddle(flist *o)
{
        flist *tmp = o->prev;
        o->prev->next = o->next;
        o->next->prev = o->prev;
        munmap(o, sizeof(flist));
        return tmp;
}

static flist *addfreenode(object *node)
{
        flist *o = NULL;
        int pt = PROT_READ | PROT_WRITE;
        int fs = MAP_PRIVATE | MAP_ANONYMOUS;
        size_t t = sizeof(flist *);
        flist *last = fhead;

        if ((o = mmap(o, t, pt, fs, -1, 0)) == (void *)-1) {
                return NULL;
        }

        if (last) {
                last->next = o;
        }
        o->next = NULL;
	
        o->prev = last;
	o->node = node;
	o->val = (uintptr_t)&*node;
        fhead = o;
        if (!(fbase)) {
                fbase = o; 
        }
        return o;
}

object *findfree(size_t size)
{
	object *ret = NULL;
	flist *o = NULL;
	object *t = NULL;
	for (o = fbase; o ; o = o->next) {
		//object *t = o->node;
		//t = (object*) o->val;
		t =o->node;
		if (t && t->size >= size && o != fbase && o != fhead)
		{
			o = delmiddle(o);
			ret = t;
			break;
		}else {
			if (o!=fbase&&o!=fhead)
			{
			munmap(t, t->size + sizeof(object));
			o = delmiddle(o);
			if (o == fhead|| o == fbase)
				break;
			}
		}
	}
	return ret;
}

void initmag(void)
{
	size_t i = 0;
	usedl = 0;
        for (i=0; i <MAGLIM; ++i) { 
                reftable[i] = 0;
		magazine[i] = NULL;
	}
}

void addmag(object *o)
{
	size_t i = 0;
	for (i=0; i <MAGLIM; ++i){ 
		if(reftable[i] == 0){ 
			reftable[i] = (uintptr_t)&*o;
			magazine[i] = o;
			break;
		}
	} 
}

object *usemag(size_t size)
{ 
	size_t i = 0;
	object *ret = NULL; 
	object *t = NULL; 
	for (i=0; i <MAGLIM; ++i)
	{ 
		if (reftable[i] == 0)
			continue;
		t = (object *)reftable[i];
		//t = magazine[i];
		if (t && t->size >= size && ret == NULL) {
			ret = t; 
                        reftable[i] = 0; 
			break;
		}
		else { 
			munmap (t, t->size + sizeof(object)); 
			reftable[i] = 0;
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
	usedl = 1; 

	if ((o = mmap(o, size + sizeof(object), pt, fs, -1, 0)) == (void *)-1) {
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
	if (usedl == 0) {
		//initmag(); 
		usedl = 1;
		 if (!(o = morecore(size))) {
                        return NULL;
                }
		fbase = fhead = NULL;
		return (o+1);
        }

	//if (!(o = usemag(size))) {
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
	//addmag(o);
	addfreenode(o);
	return;
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



