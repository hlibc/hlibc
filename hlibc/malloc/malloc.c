#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include "../../musllibc/internal/syscall.h"
#include <sys/mman.h>

typedef long Align;

union header {
	struct {
		union header *ptr;
		size_t size;
	} s;
	Align x;
}header;

typedef union header Header;
static Header *morecore(unsigned nu);
void free(void *ap);
static Header base;
static Header *freep = NULL;

void *malloc(unsigned nbytes)
{
	Header *p, *prevp;
	Header *moreroce(unsigned);
	unsigned nunits;
	nunits = (nbytes+sizeof(Header)-1)/sizeof(header) + 1;
	if ((prevp = freep) == NULL) {
		base.s.ptr = freep = prevp = &base;
		base.s.size = 0;
	}
	for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
		if (p->s.size >= nunits) {
			if (p->s.size == nunits)
				prevp->s.ptr = p->s.ptr;
			else {
				p->s.size -= nunits;
				p += p->s.size;
				p->s.size = nunits;
			}
			freep = prevp;
			return (void *)(p+1);
		}
		if (p == freep)
			if ((p = morecore(nunits)) == NULL)
				return NULL;
	}
}

#define NALLOC 1024
static Header *morecore(unsigned nu)
{
	char *cp;
	Header *up;
	if (nu < NALLOC)
		nu = NALLOC;
	cp = sbrk(nu * sizeof(Header));
	if (cp == (char *) -1)
		return NULL;
	up = (Header *) cp;
	up->s.size = nu;
	free((up+1));
	//free((void *)(up+1));

	return freep;
}

void free(void *ap)
{
	Header *bp, *p;
	bp = (Header *)ap - 1;
	for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
		if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
			break;
	if (bp + bp->s.size == p->s.ptr) {
		bp->s.size += p->s.ptr->s.size;
		bp->s.ptr = p->s.ptr->s.ptr;
	} else
		bp->s.ptr = p->s.ptr;
	if (p + p->s.size == bp) {
		p->s.size += bp->s.size;
		p->s.ptr = bp->s.ptr;
	} else
		p->s.ptr = bp;
	freep = p;
}

void *realloc(void *ptr, size_t size)
{
	if (ptr == NULL)
		return ptr = malloc(size);
	free(ptr);
	ptr = malloc(size);
	return ptr;
}

void *calloc(size_t nmemb, size_t size)
{
	void *ret;
	ret = malloc(nmemb * size);
	memset(ret, 0, size);
	return ret;
}

