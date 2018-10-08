#include <sys/syscall.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>

char *getcwd(char *buffer, size_t len)
{ 
        if (buffer == NULL) {
		len = PATH_MAX;
                if(!(buffer = malloc(len)))
			return NULL;
	}
        if (__syscall(SYS_getcwd, buffer, len) < 0)
                return NULL;

        return buffer;
}

