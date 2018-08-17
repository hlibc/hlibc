#include <unistd.h> 
#include <stdlib.h>
#include "../internal/internal.h"

extern char **__environ;

int __libc_start_main(int (*main)(int, char **, char **), int argc, char **argv)
{
	char **envp = argv+argc+1;
	__environ = envp;
	void initmag(void);
	exit(main(argc, argv, envp));
	return 0;
}
