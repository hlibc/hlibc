#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <limits.h>
#include "malloc.h"

#define _ALIGNTYPE long
#define NALLOC 10000

union header {
	struct {
		union header *ptr;
		size_t size;
	} s;
	_ALIGNTYPE x;
};

typedef union header Header;
static Header base;
static Header *gfreep = NULL;
Header *morecore(unsigned);

void *
_prevgfree(Header *bp)
{
        Header *p;

        for (p = gfreep; !(bp > p && bp < p->s.ptr); p = p->s.ptr) {
                if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
                        break;
        }
        return p;
}

void *
malloc(size_t nbytes)
{
	Header *p, *prevp; 
	size_t nunits;
	nunits = (nbytes+sizeof(Header)-1)/sizeof(Header) + 1;

	if ((prevp = gfreep) == NULL)
	{
		base.s.ptr = gfreep = prevp = &base;
		base.s.size = 0;
	}
	for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr)
	{
		if (p->s.size >= nunits)
		{
			if (p->s.size == nunits)
				prevp->s.ptr = p->s.ptr;
			else {
				p->s.size -= nunits;
				p += p->s.size;	
				p->s.size = nunits;
			}
			gfreep = prevp;
			return (void*) (p+1);
		}
		if ( p == gfreep)
			if ((p = morecore(nunits)) == NULL)
				return NULL;
	}
}

Header *
morecore(unsigned nu)
{
	char *cp;
	Header *up;
	if (nu < NALLOC)
		nu = NALLOC;
	cp = sbrk(nu * sizeof(Header));
	if (cp == (char *) -1)
		return NULL;
	up = (Header*) cp;
	up->s.size = nu;
	free((up+1));
	return gfreep;
}

void
free(void *ap)
{
	Header *bp, *p;
    
	bp = (Header*) ap - 1;

	p = _prevgfree(bp);
	if (bp + bp->s.size == p->s.ptr) 
	{
		bp->s.size += p->s.ptr->s.size;
		bp->s.ptr = p->s.ptr->s.ptr;
	}
	else
		bp->s.ptr = p->s.ptr;
	if ( p + p->s.size == bp ) 
	{
		p->s.size += bp->s.size;
		p->s.ptr = bp->s.ptr;
	}
	else
		p->s.ptr = bp;
	gfreep = p;
}

void *
realloc(void *old_ptr, size_t nbytes)
{
	Header *bp;
	void *new_ptr;
	size_t old_nbytes = 0;

	if (old_ptr == NULL)
		return malloc(nbytes);

	bp = (Header *) old_ptr - 1;

	old_nbytes = sizeof(Header) * (bp->s.size -1);

	if (old_nbytes == nbytes)
		return old_ptr;

	if ((new_ptr = malloc(nbytes)) == NULL)
		return NULL;

	memcpy(new_ptr, old_ptr, (old_nbytes > nbytes) ? nbytes : old_nbytes);

	free(old_ptr);
	return new_ptr;
}

void *
calloc(size_t nmemb, size_t size)
{ 
	size_t request;
	void *ret;
	
	request = _safe_mul(nmemb, size, (size_t)-1);

	if ((ret = malloc(request)) != NULL)
		memset(ret, 0, request); 
	
	return ret;
}
