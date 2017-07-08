#include <ctype.h>

int isgraph(int x)
{
        if (x == ' ')
                return 0;
        if (isprint(x))
                return 1;
        return 0;
}

