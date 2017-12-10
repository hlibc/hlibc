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
static Header *morecore(size_t nu);
void free(void *ap);
static Header base;
static Header *freep = NULL;

void *malloc(size_t nbytes)
{
	Header *p, *prevp;
	size_t nunits;
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


static Header *morecore(size_t nu)
{
	char *cp;
	Header *up;
	if (nu < 1024)
		nu = 1024;
	/* cp = sbrk(nu * sizeof(Header)); */
	cp = mmap(cp, nu * sizeof(Header), PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);

	if (cp == (char *) -1)
		return NULL;
	up = (Header *) cp;
	up->s.size = nu;
	free((up+1));
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
	size_t len = 0;
	len = _safe_multiply(nmemb, size, (size_t)-1);
	if (len)
		ret = malloc(len);
	memset(ret, 0, size);
	return ret;
}

