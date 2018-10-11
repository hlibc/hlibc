.global _start
_start:
	mov fp,#0
	mov lr,#0
	ldr a2,[sp],#4
	mov a3,sp
	str fp,[sp,#-4]!
	str a1,[sp,#-4]!
	str a4,[sp,#-4]!
	ldr a1,=main  /* 1st arg: application entry ip */
	bl __load_main /* hlibc init will run the program */
1:      b 1b

