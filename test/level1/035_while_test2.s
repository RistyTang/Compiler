                                                                                                                                                                          	.arch armv8-a
	.arch_extension crc
	.arm
	.text
	.global FourWhile
	.type FourWhile , %function
FourWhile:
	push {r4, r5, r6, r7, fp, lr}
	mov fp, sp
	sub sp, sp, #16
.L45:
	ldr r4, =5
	str r4, [fp, #-16]
	ldr r4, =6
	str r4, [fp, #-12]
	ldr r4, =7
	str r4, [fp, #-8]
	ldr r4, =10
	str r4, [fp, #-4]
	b .L50
.L50:
	ldr r4, [fp, #-16]
	cmp r4, #20
	movlt r4, #1
	movge r4, #0
	blt .L51
	b .L55
.L51:
	ldr r4, [fp, #-16]
	add r5, r4, #3
	str r5, [fp, #-16]
	b .L56
.L52:
	ldr r4, [fp, #-16]
	ldr r5, [fp, #-12]
	ldr r6, [fp, #-4]
	add r7, r5, r6
	add r5, r4, r7
	ldr r4, [fp, #-8]
	add r6, r5, r4
	mov r0, r6
	add sp, sp, #16
	pop {r4, r5, r6, r7, fp, lr}
	bx lr
.L55:
	b .L52
.L56:
	ldr r4, [fp, #-12]
	cmp r4, #10
	movlt r4, #1
	movge r4, #0
	blt .L57
	b .L61
.L57:
	ldr r4, [fp, #-12]
	add r5, r4, #1
	str r5, [fp, #-12]
	b .L62
.L58:
	ldr r4, [fp, #-12]
	sub r5, r4, #2
	str r5, [fp, #-12]
	b .L50
.L61:
	b .L58
.L62:
	ldr r4, [fp, #-8]
	cmp r4, #7
	beq .L63
	b .L67
.L63:
	ldr r4, [fp, #-8]
	sub r5, r4, #1
	str r5, [fp, #-8]
	b .L68
.L64:
	ldr r4, [fp, #-8]
	add r5, r4, #1
	str r5, [fp, #-8]
	b .L56
.L67:
	b .L64
.L68:
	ldr r4, [fp, #-4]
	cmp r4, #20
	movlt r4, #1
	movge r4, #0
	blt .L69
	b .L73
.L69:
	ldr r4, [fp, #-4]
	add r5, r4, #3
	str r5, [fp, #-4]
	b .L68
.L70:
	ldr r4, [fp, #-4]
	sub r5, r4, #1
	str r5, [fp, #-4]
	b .L62
.L73:
	b .L70

	.global main
	.type main , %function
main:
	push {r4, fp, lr}
	mov fp, sp
	sub sp, sp, #0
.L74:
	bl FourWhile
	mov r4, r0
	mov r0, r4
	add sp, sp, #0
	pop {r4, fp, lr}
	bx lr

