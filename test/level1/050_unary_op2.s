                                                                                     	.arch armv8-a
	.arch_extension crc
	.arm
	.text
	.global main
	.type main , %function
main:
	push {r4, r5, r6, fp, lr}
	mov fp, sp
	sub sp, sp, #8
.L25:
	ldr r4, =56
	str r4, [fp, #-8]
	ldr r4, =4
	str r4, [fp, #-4]
	ldr r4, [fp, #-8]
	ldr r5, =0
	sub r6, r5, #4
	sub r5, r4, r6
	ldr r4, [fp, #-4]
	add r6, r5, r4
	str r6, [fp, #-8]
	ldr r4, [fp, #-8]
	cmp r4, #0
	moveq r4, #1
	movne r4, #0
	moveq r4, #1
	movne r4, #0
	moveq r4, #1
	movne r4, #0
	mov r5, r4
	ldr r4, =0
	sub r6, r4, r5
	cmp r6, #0
	bne .L28
	b .L34
.L28:
	ldr r4, =0
	sub r5, r4, #1
	ldr r4, =0
	sub r6, r4, r5
	ldr r4, =0
	sub r5, r4, r6
	str r5, [fp, #-8]
	b .L30
.L29:
	ldr r4, [fp, #-4]
	ldr r5, =0
	add r6, r5, r4
	str r6, [fp, #-8]
	b .L30
.L30:
	ldr r4, [fp, #-8]
	mov r0, r4
	bl putint
	mov r4, r0
	mov r0, #0
	add sp, sp, #8
	pop {r4, r5, r6, fp, lr}
	bx lr
.L34:
	b .L29

