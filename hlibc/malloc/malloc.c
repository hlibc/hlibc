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
	struct object *prev;
	int free;
}object;

object *base = NULL;

object *delmiddle(object *o)
{
        object *tmp = o->prev;
        o->prev->next = o->next;
        o->next->prev = o->prev;
        munmap(o, o->size);
        return tmp;
}

object *delhead(object *o)
{
        object *tmp = o->next;
        o->next->prev = NULL;
        //munmap(o, o->size);
        return tmp;
}
object *deltail(object *o)
{
        object *tmp = o->prev;
        o->prev->next = NULL;
        munmap(o, o->size);
        return tmp;
}


object *find_free_block(object **last, size_t size)
{
	object *o;
	object *p;
	for ( p = base; p ; p = p->next)
	{ 
		//fprintf(stderr, "address %zu\n", &p[0]);
		//fprintf(stderr, "address %zu\n", &p->next[0]);
		//fprintf(stderr, "address %zu\n", &p->prev[0]);
		//fprintf(stderr, "set complete\n");
		if (p->free == 1)
		{
			if (p->next == NULL)
				p = deltail(p);
			else if (p->prev == NULL)
				p = delhead(p);
			else p = delmiddle(p);
		}
        }
	//fprintf(stderr, "done\n");
	for ( o = base; o && !(o->free && o->size >= size); o = o->next)
	{ 
		*last = o;
	} 
	return o;
}

object *request_space(object *last, size_t size)
{
	object *o;
	/* if ((o = sbrk(size + sizeof(object))) == (void *)-1) */
	if ((o = mmap(o, size * sizeof(object), PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0)) == (void *)-1)
		return NULL;
	if (last)
	{
		last->next = o;
		o->prev = last;
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

	//o = o->next;
	o->free = 1;
	object *hold = NULL;
	object *h; 
	//munmap(hold + 1, sizeof(object));
	
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
