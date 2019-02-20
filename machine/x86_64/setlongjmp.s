/*
	setlongjmp.s (x64)
	Copyright (c) 2019, zhiayang
*/

.global setjmp
.type setjmp, @function

.global longjmp
.type longjmp, @function


/*
	setjmp takes one argument -- jmp_buf, which we will implement as an array
	of uint64_ts (register size, that is). since it's an array, then %rdi will
	be a pointer to the first element. there's no specific order for this, as
	long as we keep it consistent.

	[0 (0)]  = %rsp
	[1 (8)]  = %rbx
	[2 (16)] = %rbp
	[3 (24)] = %r12
	[4 (32)] = %r13
	[5 (40)] = %r14
	[6 (48)] = %r15
	[7 (56)] = return address

	note that we will need to save the sigmask whenever we start dealing with
	signals, but that's for another time. also, POSIX helpfully says that
	some local vars are undefined after a longjmp() -- we'll just follow
	SysV abi and save the callee-preserved registers.
*/

// int setjmp(jmp_buf env);
setjmp:
	movq %rsp,  0(%rdi)
	movq %rbx,  8(%rdi)
	movq %rbp, 16(%rdi)
	movq %r12, 24(%rdi)
	movq %r13, 32(%rdi)
	movq %r14, 40(%rdi)
	movq %r15, 48(%rdi)

	// return address lives at 0(%rsp) -- save that.
	// can't have two memory operands in one instruction, that would take
	// way too many bytes to encode lol
	movq 0(%rsp), %rax
	movq %rax, 56(%rdi)

	// return 0.
	xor %rax, %rax
	ret



// void longjmp(jmp_buf env, int val);
longjmp:
	testq %rsi, %rsi
	jnz 1f

	// "If the programmer mistakenly passes the value 0 in val,
	// the "fake" return will instead return 1"
	// -- posix spec

	movq $1, %rsi

1:
	movq 48(%rdi), %r15
	movq 40(%rdi), %r14
	movq 32(%rdi), %r13
	movq 24(%rdi), %r12
	movq 16(%rdi), %rbp
	movq  8(%rdi), %rbx
	movq  0(%rdi), %rsp

	// again, when longjmp is called, the 'return address' lives at 0(%rsp)
	// so, to return to the setjmp-ed location, we change that value to the
	// one that we stored earlier.

	movq 56(%rdi), %rax
	movq %rax, 0(%rsp)

	// setjmp will 'return' the user-provided value (in %rsi) when initiated
	// from longjmp -- we just set %rax, that's it.
	movq %rsi, %rax
	ret













