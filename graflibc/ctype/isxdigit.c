#include <ctype.h>

int isxdigit(int x)
{
        if (isdigit(x))
                return 1;
        if (x >= 'a' && x <= 'f')
                return 1;
        if (x >= 'A' && x <= 'F')
                return 1;
        return 0;
}


