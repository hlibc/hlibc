#include "bswap.h"

#ifdef _HAS_HLIBC_ENDIAN
static const test_case_t test_cases[] =
{
    { { __bswap16 }, { LE16 }, { BE16 }, U16 },
    { { __bswap32 }, { LE32 }, { BE32 }, U32 },
    { { __bswap64 }, { LE64 }, { BE64 }, U64 }
};
static const size_t test_cases_size = sizeof(test_cases) / sizeof(test_cases[0]);
#else
static const test_case_t *test_cases = NULL;
static const size_t test_cases_size = 0;
#endif

int main(void)
{
    return test_all_cases(test_cases, test_cases_size);
}
