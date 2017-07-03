#include <ctype.h>

int ispunct(int x)
{
        if (x >= '!' && x <= '/')
                return 1;
        if (x >= ':' && x <= '@')
                return 1;
        if (x >= '[' && x <= '`')
                return 1;
        if (x >= '{' && x <= '~')
                return 1;
        return 0;
}

