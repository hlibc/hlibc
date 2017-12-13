#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include "../internal/internal.h"
#include "../../musllibc/internal/syscall.h"
#include <sys/mman.h>
#include <errno.h>
#include "../internal/internal.h"


typedef struct object
{
	size_t size;
	struct object *next;
	int free;
}object;

void *base = NULL;

object *find_free_block(object **last, size_t size)
{
	object *o;
	for ( o = base; o && !(o->free && o->size >= size); o = o->next)
		*last = o;
	return o;
}

object *request_space(object *last, size_t size)
{
	object *o;
	/* if ((o = sbrk(size + sizeof(object))) == (void *)-1) */
	if ((o = mmap(o, size * sizeof(object), PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0)) == (void *)-1)
		return NULL;
	if (last)
		last->next = o;
	o->size = size;
	o->next = NULL;
	o->free = 0;
	return o;
}
void *malloc(size_t size)
{
	object *o;
	object *last;
	if (size <= 0)
		return NULL;

	if (!base) {
		if(!(o = request_space(NULL, size)))
			return NULL;
		base = o;
	}
	else {
		last = base;
		if (!(o = find_free_block(&last, size))){
			if (!(o = request_space(last, size))) 
				return NULL;
		}
		else 
			o->free = 0;
	}

	return (o + 1);
}

void free(void *ptr)
{
	object *o;
	if (!ptr)
		return;
	
	o = (object *)ptr - 1;
	o->free = 1;
	//munmap(o, o->size);
	
}

void *realloc(void *ptr, size_t size)
{
	void *ret;
	object *o;
	if (!ptr)
		return malloc(size);

	o = (object *)ptr - 1;
	if (o->size >= size)
		return ptr;
	
	if(!(ret = malloc(size))) 
		return NULL;

	memcpy(ret, ptr, o->size);
	free(ptr);
	return ret;
}

void *calloc(size_t nelem, size_t elsize)
{
	size_t size = 0;
	void *ptr;
	size = _safe_multiply(nelem, elsize, (size_t)-1);
	if(!(ptr = malloc(size)))
                return NULL;
	else
		memset(ptr, 0, size);

	return ptr;
}
