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
void initmag(void)
{
	size_t i = 0;
	usedl = 0;
        for (i=0; i <MAGLIM; ++i)
        { 
                reftable[i] = 0;
                used[i] = 0;
	}
}

void addmag(object *o)
{
	size_t i = 0;
	for (i=0; i <MAGLIM; ++i)
	{ 
		if(used[i] == 0)
		{ 
			reftable[i] = (uintptr_t)&*o;
			used[i] = 1;
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
		if (used[i] == 0)
			continue; 
		t = (object *)reftable[i];
		if (t && t->size >= size && ret == NULL) {
			ret = t;
                        used[i] = 0;
                        reftable[i] = 0; 
		}
		else if (t && t->size) { 
			munmap (t, t->size + sizeof(object));
			used[i] = 0;
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
		initmag(); 
		usedl = 1;

	}
	if (!(o = usemag(size))) {
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
	addmag(o);
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

void __destroy_malloc()
{
	return; 
}

