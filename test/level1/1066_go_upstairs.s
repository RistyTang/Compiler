                                                                                                                   	.arch armv8-a
	.arch_extension crc
	.arm
	.text
	.global climbStairs
	.type climbStairs , %function
climbStairs:
	push {r4, r5, r6, r7, r8, fp, lr}
	mov fp, sp
	sub sp, sp, #48
.L36:
	str r0, [fp, #-48]
	ldr r4, [fp, #-48]
	cmp r4, #4
	movlt r4, #1
	movge r4, #0
	blt .L38
	b .L42
.L38:
	ldr r4, [fp, #-48]
	mov r0, r4
	add sp, sp, #48
	pop {r4, r5, r6, r7, r8, fp, lr}
	bx lr
	b .L39
.L39:
	mov r4, #0
	mov r5, #-44
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	add r5, fp, r4
	ldr r4, =0
	str r4, [r5]
	mov r4, #1
	mov r5, #-44
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	add r5, fp, r4
	ldr r4, =1
	str r4, [r5]
	mov r4, #2
	mov r5, #-44
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	add r5, fp, r4
	ldr r4, =2
	str r4, [r5]
	ldr r4, =3
	str r4, [fp, #-4]
	b .L45
.L40:
.L41:
.L42:
	b .L39
.L45:
	ldr r4, [fp, #-4]
	ldr r5, [fp, #-48]
	add r6, r5, #1
	cmp r4, r6
	movlt r4, #1
	movge r4, #0
	blt .L46
	b .L50
.L46:
	ldr r4, [fp, #-4]
	sub r5, r4, #1
	mov r4, #-44
	mov r6, #4
	mul r7, r5, r6
	add r5, r4, r7
	add r4, fp, r5
	ldr r5, [r4]
	ldr r4, [fp, #-4]
	sub r6, r4, #2
	mov r4, #-44
	mov r7, #4
	mul r8, r6, r7
	add r6, r4, r8
	add r4, fp, r6
	ldr r6, [r4]
	add r4, r5, r6
	ldr r5, [fp, #-4]
	mov r6, #-44
	mov r7, #4
	mul r8, r5, r7
	add r5, r6, r8
	add r6, fp, r5
	str r4, [r6]
	ldr r4, [fp, #-4]
	add r5, r4, #1
	str r5, [fp, #-4]
	b .L45
.L47:
	ldr r4, [fp, #-48]
	mov r5, #-44
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	add r5, fp, r4
	ldr r4, [r5]
	mov r0, r4
	add sp, sp, #48
	pop {r4, r5, r6, r7, r8, fp, lr}
	bx lr
.L48:
.L49:
.L50:
	b .L47

	.global main
	.type main , %function
main:
	push {r4, fp, lr}
	mov fp, sp
	sub sp, sp, #8
.L54:
	ldr r4, =5
	str r4, [fp, #-4]
	ldr r4, [fp, #-4]
	mov r0, r4
	bl climbStairs
	mov r4, r0
	str r4, [fp, #-8]
	ldr r4, [fp, #-8]
	mov r0, r4
	add sp, sp, #8
	pop {r4, fp, lr}
	bx lr

