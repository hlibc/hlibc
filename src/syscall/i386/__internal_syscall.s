.globl  __internal_syscall
.type   __internal_syscall, @function
__internal_syscall: 
        pushl   %edi 
        pushl   %esi 
        pushl   %ebx 
        movl    28(%esp), %edx
        movl    24(%esp), %ecx
        movl    16(%esp), %eax
        movl    20(%esp), %ebx
        movl    32(%esp), %esi
        movl    36(%esp), %edi 
        pushl 40(%esp) ; pushl %ebp ; mov 4(%esp),%ebp ; int $128 ; popl %ebp ; popl %ecx 
        popl    %ebx 
        popl    %esi 
        popl    %edi 
        ret










