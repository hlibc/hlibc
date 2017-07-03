#include <ctype.h>

int isprint(int x)
{
        if (iscntrl(x))
                return 0;
        if ( x == ' ' )
                return 1;
        if (isspace(x) == 0)
                return 1;
        return 0;
}

