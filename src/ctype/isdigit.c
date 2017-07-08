#include <ctype.h>

int isdigit(int x)
{
        if ( x >= '0' && x <= '9')
                return 1;
        return 0;
}

