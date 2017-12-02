#include "libc.h"

#undef environ
char **environ = 0;
//weak_alias(environ, _environ);
//weak_alias(environ, environ);
//weak_alias(environ, environ);
