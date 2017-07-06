#include <stddef.h>
#include <stdint.h>
#include <strings.h>
#include <features.h>

/* Derived from OS-Zero strings.c. Copyright (C) 2017, Tuomo Venäläinen */

void
bzero(void *ptr, size_t nb)
{
    int8_t *bptr = ptr;
    int8_t  zb = 0;
    long    zw = 0;
    long    nleft = nb;
    long    n = 0;
    long   *lptr;
    long    cnt;
    size_t  val;

    /* Added as a hack, until integrated with the build system -CM Graff */
    int LONGSIZE = sizeof(long);
    int LONGSIZELOG2 = 3;

    cnt = sizeof(long);
    val = (uintptr_t)bptr & (cnt - 1);
    if (val) {
        n = cnt - val;
    }
    nleft -= n;
    while (n--) {
        /* set unaligned leading bytes */
        *bptr++ = zb;
    }
    lptr = (long *)bptr;
    n = nleft >> (3 + LONGSIZELOG2 - 1);
    nleft &= ~(8 * sizeof(long) - 1);
    while (n--) {
        /* set long-words */
        lptr[0] = zw;
        lptr[1] = zw;
        lptr[2] = zw;
        lptr[3] = zw;
        lptr[4] = zw;
        lptr[5] = zw;
        lptr[6] = zw;
        lptr[7] = zw;
        lptr += 8;
    }
    n = nleft >> LONGSIZELOG2;
    nleft &= (LONGSIZE - 1);
    while (n--) {
        /* set long-words */
        *lptr++ = zw;
    }
    bptr = (int8_t *)lptr;
    while (nleft--) {
        /* set trailing bytes */
        *bptr++ = zb;
    }

    return;
}
