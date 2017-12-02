#include <stdlib.h>

extern char **environ;

int clearenv()
{
	environ[0] = 0;
	return 0;
}
