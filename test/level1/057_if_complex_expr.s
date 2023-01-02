                                                                                                                                                     	.arch armv8-a
	.arch_extension crc
	.arm
	.text
	.global main
	.type main , %function
main:
	push {r4, r5, r6, fp, lr}
	mov fp, sp
	sub sp, sp, #20
.L44:
	ldr r4, =5
	str r4, [fp, #-20]
	ldr r4, =5
	str r4, [fp, #-16]
	ldr r4, =1
	str r4, [fp, #-12]
	ldr r4, =0
	sub r5, r4, #2
	str r5, [fp, #-8]
	ldr r4, =2
	str r4, [fp, #-4]
	ldr r4, [fp, #-8]
	ldr r5, =1
	mul r6, r4, r5
	ldr r4, =2
	sdiv r5, r6, r4
	cmp r5, #0
	movlt r4, #1
	movge r4, #0
	blt .L50
	b .L55
.L50:
	ldr r4, [fp, #-4]
	mov r0, r4
	bl putint
	mov r4, r0
	b .L51
.L51:
	ldr r4, [fp, #-8]
	ldr r5, =2
	sdiv r6, r4, r5
	mul r5, r6, r5
	sub r6, r4, r5
	add r4, r6, #67
	cmp r4, #0
	movlt r4, #1
	movge r4, #0
	blt .L63
	b .L68
.L52:
	ldr r4, [fp, #-20]
	ldr r5, [fp, #-16]
	sub r6, r4, r5
	cmp r6, #0
	bne .L56
	b .L59
.L55:
	b .L52
.L56:
	ldr r4, [fp, #-12]
	add r5, r4, #3
	ldr r4, =2
	sdiv r6, r5, r4
	mul r4, r6, r4
	sub r6, r5, r4
	cmp r6, #0
	bne .L50
	b .L62
.L59:
	b .L51
.L62:
	b .L51
.L63:
	ldr r4, =4
	str r4, [fp, #-4]
	ldr r4, [fp, #-4]
	mov r0, r4
	bl putint
	mov r4, r0
	b .L64
.L64:
	mov r0, #0
	add sp, sp, #20
	pop {r4, r5, r6, fp, lr}
	bx lr
.L65:
	ldr r4, [fp, #-20]
	ldr r5, [fp, #-16]
	sub r6, r4, r5
	cmp r6, #0
	bne .L69
	b .L72
.L68:
	b .L65
.L69:
	ldr r4, [fp, #-12]
	add r5, r4, #2
	ldr r4, =2
	sdiv r6, r5, r4
	mul r4, r6, r4
	sub r6, r5, r4
	cmp r6, #0
	bne .L63
	b .L75
.L72:
	b .L64
.L75:
	b .L64

