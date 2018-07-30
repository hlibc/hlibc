/* Copyright 2018, Adrian Parvin D. Ouano */
/* Copyright 2018, CM Graff */

.global _start
_start: 
	subq $8, %rsp
	xor %rbp, %rbp
	pop %rax
	pop %rsi
	mov %rsp, %rdx
	andq $-16, %rsp
	mov $main, %rdi
	call __libc_start_main

