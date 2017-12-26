#include "libc.h"

#undef environ
char **__environ = 0;

