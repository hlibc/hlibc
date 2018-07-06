/* Written 2011 Nicholas J. Kain, released as Public Domain */ 
.text
.global _start
_start:
	xor %rbp,%rbp   /* rbp:undefined -> mark as zero 0 (ABI) */
	mov %rdx,%r9    /* 6th arg: ptr to register with atexit() */
	pop %rsi        /* 2nd arg: argc */
	mov %rsp,%rdx   /* 3rd arg: argv */
	andq $-16,%rsp  /* align stack pointer */
	mov $main,%rdi  /* 1st arg: application entry ip */
	call __libc_start_main /* hlibc init will run the program */
1:	jmp 1b
