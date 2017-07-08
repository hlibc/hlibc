#include <ctype.h>

int iscntrl(int x)
{
        if (x >= '\0' && x < ' ' )
                return 1;
        return 0;
}

