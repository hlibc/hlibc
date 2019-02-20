/*
	setlongjmp.s (i386)
	Copyright (c) 2019, zhiayang
*/

.global setjmp
.type setjmp, @function

.global longjmp
.type longjmp, @function


/*
	the main bulk of the documentation is in x86_64/setlongjmp.s
	the contents are mostly identical anyway, minus the struct layout.

	[0 (0)]  = %esp
	[1 (4)]  = %ebx
	[2 (8)]  = %ebp
	[3 (12)] = %edi
	[4 (16)] = %esi
	[5 (20)] = return address
*/

// int setjmp(jmp_buf env);
setjmp:
	// args are passed on the stack; 0(%esp) is the return address (which we
	// need to save) and 4(%esp) is the jmp_buf

	// clobber eax, nobody cares.
	movl 4(%esp), %eax

	movl %esp,  0(%eax)
	movl %ebx,  4(%eax)
	movl %ebp,  8(%eax)
	movl %edi, 12(%eax)
	movl %esi, 16(%eax)

	// clobber edx too. eax and edx are called-saved
	movl 0(%esp), %edx
	movl %edx, 20(%eax)

	// return 0.
	xor %eax, %eax
	ret



// void longjmp(jmp_buf env, int val);
longjmp:
	movl 4(%esp), %eax      // this is jmp_buf
	movl 8(%esp), %ecx      // this is val
	testl %ecx, %ecx
	jnz 1f

	// if 'val' was 0, make it 1
	movl $1, %ecx

1:
	movl 16(%eax), %esi
	movl 12(%eax), %edi
	movl  8(%eax), %ebp
	movl  4(%eax), %ebx
	movl  0(%eax), %esp

	movl 20(%eax), %edx
	movl %edx, 0(%esp)

	movl %ecx, %eax
	ret













