#include <sys/types.h> 
#include <stdint.h>
#include <sys/mman.h>
#include "../internal/internal.h"

void *__mmap_inter(size_t size)
{
        static const int pt = PROT_READ | PROT_WRITE;
        static const int fs = MAP_PRIVATE | MAP_ANONYMOUS;
        void *o = NULL;
        if ((o = mmap(o, size, pt, fs, -1, 0)) == (void *)-1) {
                return NULL;
        }
        return o;
}

