.text
.global _start
_start:
	xor %ebp,%ebp /* rbp:undefined -> mark as zero 0 (ABI) */
	pop %ecx
	mov %esp,%eax
	and $-16,%esp /* align stack pointer */
	push %esp
	push %esp
	push %edx
	push %eax
	push %ecx
	push $main /* 1st arg: application entry ip */
	call __load_main /* hlibc init will run the program */
1:	jmp 1b
