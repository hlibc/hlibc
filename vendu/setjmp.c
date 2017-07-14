#define TEST 1
#define PROF 0

#if defined(__i386__)
#include <zero/prof.h>
#endif

#include <stddef.h>
#include <alloca.h>
#if defined(__GNUC__)
#define alloca(size) __builtin_alloca(size)
#else
#endif

#if defined(__amd64__)
#define setjmp_printstk(str)						\
    do {                                                                \
        int64_t _reg;                                                   \
                                                                        \
        fprintf(stderr, "%s\n", str);                                   \
        __asm__ __volatile("movq %%rsp, %0" : "=m" (_reg));             \
        fprintf(stderr, "\tsp\t%x\n", _reg);                            \
        __asm__ __volatile("movq %%rbp, %0" : "=m" (_reg));             \
        fprintf(stderr, "\tfp\t%x\n", _reg);                            \
    } while (0)
#define setjmp_printctx(jp)						\
    fprintf(stderr, "--------\n");                                      \
    fprintf(stderr, "rbx\t%lx\n", jp->rbx);                             \
    fprintf(stderr, "r12\t%lx\n", jp->r12);                             \
    fprintf(stderr, "r13\t%lx\n", jp->r13);                             \
    fprintf(stderr, "r14\t%lx\n", jp->r14);                             \
    fprintf(stderr, "r15\t%lx\n", jp->r15);                             \
    fprintf(stderr, "rbp\t%lx\n", jp->rbp);                             \
    fprintf(stderr, "rsp\t%lx\n", jp->rsp);                             \
    fprintf(stderr, "rip\t%lx\n", jp->rip)
#elif defined(__i386__)
#define setjmp_printstk(str)						\
    do {                                                                \
        int32_t _reg;                                                   \
                                                                        \
        fprintf(stderr, "%s\n", str);                                   \
        __asm__ __volatile("movl %%esp, %0" : "=m" (_reg));             \
        fprintf(stderr, "\tsp\t%x\n", _reg);                            \
        __asm__ __volatile("movl %%ebp, %0" : "=m" (_reg));             \
        fprintf(stderr, "\tfp\t%x\n", _reg);                            \
    } while (0)
#define setjmp_printctx(jp)						\
    fprintf(stderr, "--------\n");                                      \
    fprintf(stderr, "ebx\t%lx\n", jp->ebx);                             \
    fprintf(stderr, "esi\t%lx\n", jp->esi);                             \
    fprintf(stderr, "edi\t%lx\n", jp->edi);                             \
    fprintf(stderr, "ebp\t%lx\n", jp->ebp);                             \
    fprintf(stderr, "esp\t%lx\n", jp->esp);                             \
    fprintf(stderr, "eip\t%lx\n", jp->eip)
#elif defined(__arm__)
#define setjmp_printstk(str)						\
    do {                                                                \
        int32_t _reg;                                                   \
                                                                        \
        fprintf(stderr, "%s\n", str);                                   \
        __asm__ __volatile__ ("movs %0, sp\n" : "=r" (_reg));		\
        fprintf(stderr, "\tsp\t%x\n", _reg);                            \
        __asm__ __volatile__ ("movs %0, fp\n" : "=r" (_reg));		\
        fprintf(stderr, "\tfp\t%x\n", _reg);                            \
    } while (0)
#define setjmp_printctx(jp)						\
    fprintf(stderr, "--------\n");                                      \
    fprintf(stderr, "r4\t%lx\n", jp->r4);                               \
    fprintf(stderr, "r5\t%lx\n", jp->r5);                               \
    fprintf(stderr, "r6\t%lx\n", jp->r6);                               \
    fprintf(stderr, "r7\t%lx\n", jp->r7);                               \
    fprintf(stderr, "r8\t%lx\n", jp->r8);                               \
    fprintf(stderr, "r9\t%lx\n", jp->r9);                               \
    fprintf(stderr, "r10\t%lx\n", jp->r10);                             \
    fprintf(stderr, "fp\t%lx\n", jp->fp);                               \
    fprintf(stderr, "sp\t%lx\n", jp->sp);                               \
    fprintf(stderr, "lr\t%lx\n", jp->lr)
#endif

#include <setjmp.h>

#if (TEST || PROF)
#include <stdlib.h>
#include <stdio.h>

#if (PROF)
#include <zero/prof.h>
#endif

static jmp_buf      jb;

int
jmp(int val)
{
    setjmp_printstk("jmp");
    longjmp(jb, 1);
}

#define _NRUN 10000
int
main(int argc, char *argv[])
{
    volatile int retval;
    uint32_t *ptr = NULL;
#if defined(__i386__)
    PROFTICK(tick);
#endif

    retval = 0x01010101;
#if (TEST)
    while (1) {
        fprintf(stderr, "&retval: %p, &ptr: %p\n",
                &retval, &ptr);
        setjmp_printstk("main");
        setjmp_printctx(&jb);
        retval = setjmp(jb);
        fprintf(stderr, "SETJMP: %x\n", retval);
        if (retval) {
#if defined(__i386__)
            profstarttick(tick);
#endif
#if (TEST_ALLOCA2)
            alloca2(8, ptr);
#else
            ptr = __zalloca(8);
#endif
#if defined(__i386__)
            profstoptick(tick);
            fprintf(stderr, "%ll cycles\n", proftickdiff(tick));
#endif
            ptr[0] = 0x03030303;
            ptr[1] = 0x04040404;
            fprintf(stderr, "ALLOCA: %p (%x %x)\n", ptr,
                    (unsigned int)ptr[0], (unsigned int)ptr[1]);
            setjmp_printctx(&jb);

            exit(0);
        }
        jmp(1);
    }
#endif

    exit(0);
}
#endif

