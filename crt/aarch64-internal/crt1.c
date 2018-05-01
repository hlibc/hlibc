
__asm__(
".text \n"
".global " "_start" "\n"
".type " "_start" ",%function\n"
"_start" ":\n"
"       mov x29, #0\n"
"       mov x30, #0\n"
"       mov x0, sp\n"
".weak _DYNAMIC\n"
".hidden _DYNAMIC\n"
"       adrp x1, _DYNAMIC\n"
"       add x1, x1, #:lo12:_DYNAMIC\n"
"       and sp, x0, #-16\n"
"       b " "_start" "_c\n"
);


int main();
void _init() __attribute__((weak));
void _fini() __attribute__((weak));
_Noreturn int __libc_start_main(int (*)(), int, char **,
        void (*)(), void(*)(), void(*)());

void _start_c(long *p)
{
        int argc = p[0];
        char **argv = (void *)(p+1);
        __libc_start_main(main, argc, argv, _init, _fini, 0);
}

