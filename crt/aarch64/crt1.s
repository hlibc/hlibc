.global _start
.type _start,%function
_start:
	mov x29, #0
	mov x30, #0
	mov x0, sp
.weak _DYNAMIC
.hidden _DYNAMIC
	adrp x1, _DYNAMIC
	add x1, x1, #:lo12:_DYNAMIC
	and sp, x0, #-16 
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	str	x0, [x29,24]
	ldr	x0, [x29,24]
	ldr	x0, [x0]
	str	w0, [x29,44]
	ldr	x0, [x29,24]
	add	x0, x0, 8
	str	x0, [x29,32]
	adrp	x0, main
	add	x0, x0, :lo12:main
	ldr	x3, .LC0
	ldr	x4, .LC1
	ldr	w1, [x29,44]
	ldr	x2, [x29,32]
	mov	x5, 0
	bl	__libc_start_main

.LC0:
	.xword	_init
	.align	3
.LC1:
	.xword	_fini
	.weak	_fini
	.weak	_init
	

