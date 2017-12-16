/* comments taken from crt/x86_64/crt1.s -cmg */
.weak _init
.weak _fini
.global _start
_start:
	mov fp,#0
	mov lr,#0
	ldr a2,[sp],#4
	mov a3,sp
	ldr a4,=_fini
	str fp,[sp,#-4]!
	str a1,[sp,#-4]!
	str a4,[sp,#-4]!
	ldr a4,=_init /* 4th arg: init/ctors function */
	ldr a1,=main /* 1st arg: application entry ip */
	bl __libc_start_main /* musl init will run the program */
1:	b 1b
