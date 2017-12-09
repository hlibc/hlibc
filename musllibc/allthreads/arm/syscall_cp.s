.global __syscall_cp_asm
.type __syscall_cp_asm,%function
__syscall_cp_asm:
	mov ip,sp
	stmfd sp!,{r4,r5,r6,r7,lr}
	stmfd sp!,{r0}
	bl 1f
1:	ldr r0,[r0]
	cmp r0,#0
	mov r7,r1
	mov r0,r2
	mov r1,r3
	ldmfd ip,{r2,r3,r4,r5,r6}
1:	svc 0
	ldmfd sp!,{r1}
	mov r2,#0
	str r2,[r1]
	ldmfd sp!,{r4,r5,r6,r7,lr}
	tst lr,#1
	moveq pc,lr
	bx lr
