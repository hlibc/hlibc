        .file   "assembly.c"
        .section        ".toc","aw"
        .align 3
        .section        ".text"
        .machine power7
        .align 2
        .p2align 4,,15
        .globl __internal_syscall
        .section        ".opd","aw"
        .align 3
__internal_syscall:
        .quad   .L.__internal_syscall,.TOC.@tocbase
        .previous
        .type   __internal_syscall, @function
.L.__internal_syscall:
        mr 0,3
        mr 3,4
        mr 4,5
        mr 5,6
        mr 6,7
        mr 7,8
        mr 8,9
#APP
 # 10 "assembly.c" 1
        sc ; bns+ 1f ; neg 3, 3 ; 1:
 # 0 "" 2
#NO_APP
        blr
        .long 0
        .byte 0,0,0,0,0,0,0,0
        .size   __internal_syscall,.-.L.__internal_syscall
        .ident  "GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-16)"
        .section        .note.GNU-stack,"",@progbits

