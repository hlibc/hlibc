#include <ctype.h>

int isspace(int x)
{
        int ret = 1;
        switch(x)
        {
                case ' ':
                        return ret;
                        break;
                case '\t':
                        return ret;
                        break;
                case '\n':
                        return ret;
                        break;
                case '\r':
                        return ret;
                        break;
                case '\f':
                        return ret;
                        break;
                case '\v':
                        return ret;
                        break;
                default:
                        ret = 0;
                        break;
        }
        return ret;
}
