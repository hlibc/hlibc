.weak _init
.weak _fini
.text
.global _start
/* These comments were borrowed from crt/x86_64/crt1.s -cmg */
_start:
	xor %ebp,%ebp /* rbp:undefined -> mark as zero 0 (ABI) */
	pop %ecx
	mov %esp,%eax
	and $-16,%esp /* align stack pointer */
	push %esp
	push %esp
	push %edx
	push $_fini /* 5th arg: fini/dtors function */
	push $_init /* 4th arg: init/ctors function */
	push %eax
	push %ecx
	push $main /* 1st arg: application entry ip */
	call __libc_start_main /* hlibc init will run the program */
1:	jmp 1b
