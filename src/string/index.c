#include <string.h>
/*
	Copyright 2016 Evgeniy Popov
	Modified by CM Graff in 2018 to just use strchr
*/

char *index(const char *s, int c)
{
        return strchr(s, c);
}

