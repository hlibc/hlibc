.text
.global _start
_start:
	xor %ebp,%ebp
	pop %ecx
	mov %esp,%eax
	and $-16,%esp
	push %esp
	push %esp
	push %edx
	push %eax
	push %ecx
	push $main
	call __load_main
1:	jmp 1b
