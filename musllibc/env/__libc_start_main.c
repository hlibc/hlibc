#include "libc.h"

int __libc_start_main(
	int (*main)(int, char **, char **), int argc, char **argv,
	int (*init)(int, char **, char **), void (*fini)(void),
	void (*ldso_fini)(void))
{
	char **envp = argv+argc+1, **auxv = envp;

	/* assign the environment from envp */
	__environ = envp;
	do auxv++; while (*auxv);
	libc.auxv = (void *)++auxv;
	libc.ldso_fini = ldso_fini;
	libc.fini = fini;

	/* ssp would go here if it was supported */

	/* Execute constructors (static) linked into the application */
	if (init) init(argc, argv, envp);

	/* Pass control to to application */
	exit(main(argc, argv, envp));
	return 0;
}

