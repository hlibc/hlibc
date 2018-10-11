#include "../internal/internal.h"

int clearenv(void)
{
        __environ[0] = NULL;
        return 0;
}
