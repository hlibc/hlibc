#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/mman.h>
#include <errno.h>

typedef struct object
{
	size_t size;
	struct object *next;
	struct object *prev;
} object;

typedef struct tfreelist
{ 
	struct tfreelist *next;
	struct tfreelist *prev;
	struct object *tfreenode;
	intptr_t nodaddr;
	uintptr_t val;
	uintptr_t nval;
	uintptr_t pval;
}tfreelist;

static object *base = NULL;
static object *head = NULL;


static tfreelist *fbase = NULL;
static tfreelist *fhead = NULL;
uintptr_t fbaseval = 0;

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

static tfreelist *deltfreenode(tfreelist *o)
{
	tfreelist *tmp = o->prev;
	o->prev->next = o->next;
	o->prev->nval = o->next->nval;
	o->next->prev = o->prev;
	o->next->pval = o->prev->pval;
	munmap(o, sizeof(tfreelist) + 4096);
	return tmp;
}

static tfreelist *__deltfreenode(tfreelist *o)
{ 
	if (o->next && o->prev && o != fhead && o != fbase)
		o = deltfreenode(o);
	return o;
}

static object *find_tfreenode(size_t size)
{
	tfreelist *o;
	object *ret = NULL;
	write(2, "find_free\n", 10);
	printf ("fbase is %p\n", fbase);
	fflush(NULL);

	//for (o = fbase; o ; o = (tfreelist*)o->nval) {
	for (o = fbase; o ; o = o->next) {
	//	if (o->nval == 0)
	//		break;
	write(2, "loop\n", 5);
		//object *t = (object*)o->val;
		object *t = o->tfreenode;
		if (t->size >= size && ret == NULL) {
			ret = t;
			o = __deltfreenode(o);
			break;
			
		}else  { 
			__delmiddle(t);
			o = __deltfreenode(o);
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

	t = size + sizeof(object);
	//if (__safe_uadd_sz(size, sizeof(object), &t, SIZE_MAX) == -1) {
	//	goto error;
	//}

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

static tfreelist *addtfreenode(tfreelist *unused, object *node)
{ 
	tfreelist *o = NULL;
	int pt = PROT_READ | PROT_WRITE;
	int fs = MAP_PRIVATE | MAP_ANONYMOUS;
	size_t t = sizeof(tfreelist) + 4096;
	tfreelist *last = fhead;
	
	if ((o = mmap(o, t, pt, fs, -1, 0)) == (void *)-1) {
		return NULL;
	}
	
	if (last) {
		last->next = o;
		last->nval = (uintptr_t)&o;
	}
	o->next = NULL;
	o->prev = last;
	o->tfreenode = node;
	o->val = (uintptr_t)&node;
	o->nval = 0;
	o->pval = (uintptr_t)&last;
	fhead = o;
	if (!(fbase) || fbaseval == 0)
	{
		fbase = o;
		fbaseval = (uintptr_t)&o;
	}
	return o;
}


void *tmalloc(size_t size)
{
	object *o;
	if (!(o = find_tfreenode(size))) {
		if (!(o = morecore(size))) {
			return NULL;
		}
	}
	if (!base)
		base = o;
	if (!head)
		head = o;

	return (o + 1);
}

void tfree(void *ptr)
{
	object *o;
	if (!ptr) {
		return;
	}
	/*
		This object should be added to the tfree list 
	*/
	o = (object *)ptr - 1;
	addtfreenode(NULL, o);
	printf ("pointer is %p\n", o);
	printf ("fbase is %p\n", fbase);
	fflush(NULL);
}

void *trealloc(void *ptr, size_t size)
{
	void *ret;
	object *o;
	if (!ptr) {
		return tmalloc(size);
	}

	o = (object *)ptr - 1;
	if (o->size >= size) {
		return ptr;
	}

	if (!(ret = tmalloc(size))) {
		return NULL;
	}

	memcpy(ret, ptr, o->size);
	tfree(ptr);
	return ret;
}

void *tcalloc(size_t nmemb, size_t size)
{
	void *o;
	size_t t = 0;
	t = nmemb * size;
	//if(__safe_umul_sz(nmemb, size, &t, (size_t)-1) == -1) { 
	//	return NULL;
	//}
	if (!(o = tmalloc(t))) {
		return NULL;
	}
	memset(o, 0, t);
	return o;
}

void __destroy_tmalloc()
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
void some(void)
{
	
	char *p = tmalloc(10);
	tfree(p);
	char *j = tmalloc(1000);
	char *k = tmalloc(100000);
	tfree(j);
	tfree(k);
	char *l = tmalloc(10000);
	
}
void some2(void)
{

        char *p = tmalloc(10);
        tfree(p);
        char *j = tmalloc(1000);
        char *k = tmalloc(100000);
        tfree(j);
        tfree(k);
        char *l = tmalloc(10000);
}


int main(void)
{
	some();
	some2();
	return 0;
}
