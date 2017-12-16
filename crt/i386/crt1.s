/* comments taken from crt/x86_64/crt1.s -cmg */
.weak _init
.weak _fini
.text
.global _start
_start:
	xor %ebp,%ebp /* rbp:undefined -> mark as zero 0 (ABI) -cmg*/
	pop %ecx
	mov %esp,%eax
	and $-16,%esp /* align stack pointer -cmg*/
	push %esp
	push %esp
	push %edx
	push $_fini /* 5th arg: fini/dtors function -cmg */
	push $_init /* 4th arg: init/ctors function -cmg *
	push %eax
	push %ecx
	push $main /* 1st arg: application entry ip -cmg */
	call __libc_start_main /* musl init will run the program -cmg */
1:	jmp 1b
