#include <arpa/inet.h>
#include <stddef.h>

enum
{
    LE16 = 0x1122ULL,
    BE16 = 0x2211ULL,
    LE32 = 0x11223344ULL,
    BE32 = 0x44332211ULL,
    LE64 = 0x1122334455667788ULL,
    BE64 = 0x8877665544332211ULL
};

typedef struct
{
    union
    {
        uint16_t (*u16) (uint16_t);
        uint32_t (*u32) (uint32_t);
        uint64_t (*u64) (uint64_t);
    } func;
    union
    {
        uint16_t u16;
        uint32_t u32;
        uint64_t u64;
    } in;
    union
    {
        uint16_t u16;
        uint32_t u32;
        uint64_t u64;
    } out;
    enum
    {
        U16,
        U32,
        U64
    } type;
} test_case_t;

static int test_one_case(const test_case_t *p, size_t n)
{
    const test_case_t *tc = &p[n];

    switch(tc->type)
    {
        case U16:
            return (tc->func.u16(tc->in.u16) != tc->out.u16);
        case U32:
            return (tc->func.u32(tc->in.u32) != tc->out.u32);
        case U64:
            return (tc->func.u64(tc->in.u16) != tc->out.u64);
        default:
            return -1;
    }
}

static int test_all_cases(const test_case_t *p, size_t n)
{
    size_t i;

    for( i = 0 ; i < n ; ++i )
    {
        if(test_one_case(p, i))
        {
            return 1;
        }
    }

    return 0;
}
