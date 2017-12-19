#include "libc.h"
/*

09:28 <interviewer> regarding __libc_start_main is that part of gcc or is that
			 defined in the assembly crt files?

09:25 < developer> interviewer, __lib_start_main is the thing responsible fort setting 
                        up libc and calling your main function, it's called by 
                        _start, which is defined in assembly files

09:28 < developer> _start is the entry point the kernel program loader 
                        jumps to, it sets up some registers containing 
                        important information like environment and command line 
                        arguments, dso and some other stuff, then _start 
                        figures out all that stuff, aligns the stack and sets 
                        up registers according to abi then calls 
                        __libc_start_main, this is part of libc, which 
                        initializes parts of libc (like the allocator, 
                        return-to-libc attack prevention (canary
09:28 < developer> stuff), threading state, locale, what ever may be done 
                        here), then __libc_start_main, calls your main 
                        function, and captures it's return value, that return 
                        value is then used to call the exit system call or 
                        exitgroup (in the case of musl)
09:29 <@author> _start is not special really, it's just that ld defaults to -e 
                _start
09:29 < developer> thanks for the clarification
09:29 <@author> which sets e_entry (of main elf header) to point to _start
09:29 < deuteron> author: Yeah, that's probably what happened, as developer said.
09:30 <@author> return value of main has to be passed to exit function not syscall
09:31 <@author> because returning from main is required to behave as if by exit 
                (stdio flushing, atexit handlers, etc.)
09:31 <@author> and SYS_exit is not usable here because it just terminates the 
                calling thread not the process
09:32 < developer> I keep forgetting about all those minor things, yeah it has 
                        to do all the stuff exit would do
09:33 < skarnet> that's why "#include <unistd.h> \n int main (void) { _exit(0); }" 
                 yields a smaller binary than "int main (void) { return 0; }", which 
                 is obviously very, very intuitive
09:33 < developer> though __libc_start_main could just do all that before 
                        issuing the syscall to exit the process
09:33 < developer> but then exit also has to do it
09:33 < developer> so may as well just have __libc_start_main do exit(main(argc, 
                        argv, envp))
09:34 <@author> skarnet, i don't think either yields a different size
09:34 <@author> unless you have LTO
09:35 <@author> because without LTO there's no way for the linker to see that exit is 
                not reachable
09:35 < developer> SYS_exit_group is the syscall that terminates the process 
                        right?
09:35 < developer> whereas SYS_exit is just the calling thread
09:35 < skarnet> there was somehow a size difference when I tested it, i.e. something 
                 like 2 years ago
09:36 <@author> developer, right
09:36 < developer> well, _Exit is marked _Noreturn, so if you do int main() { 
                        _Exit(0); }, then LTO can see that main also cannot return, 
                        so if you had exit(main(...)) then it would remove the call 
                        to exit
09:36 < developer> so I can see how that would be a size difference
09:36 <@author> developer, *nod* but you really need LTO for this
09:36 < developer> yeah
*/

void __init_security(size_t *);

int __libc_start_main(
	int (*main)(int, char **, char **), int argc, char **argv,
	int (*init)(int, char **, char **), void (*fini)(void),
	void (*ldso_fini)(void))
{
	char **envp = argv+argc+1, **auxv = envp;

	__environ = envp;
	do auxv++; while (*auxv);
	libc.auxv = (void *)++auxv;
	libc.ldso_fini = ldso_fini;
	libc.fini = fini;

	__init_security((void *)auxv);

	/* Execute constructors (static) linked into the application */
	if (init) init(argc, argv, envp);

	/* Pass control to to application */
	exit(main(argc, argv, envp));
	return 0;
}
