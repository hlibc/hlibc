.globl	__internal_syscall
__internal_syscall:
	movq	%rdi, %rax
	movq	%r8, %r10
	movq	%rsi, %rdi
	movq	%r9, %r8
	movq	%rdx, %rsi
	movq	8(%rsp), %r9
	movq	%rcx, %rdx
	syscall
	ret

