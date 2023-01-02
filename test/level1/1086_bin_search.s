                                                                                                                                                                                                                                                                                                         	.arch armv8-a
	.arch_extension crc
	.arm
	.text
	.global main
	.type main , %function
main:
	push {r4, r5, r6, r7, r8, fp, lr}
	mov fp, sp
	sub sp, sp, #68
.L66:
	ldr r4, =0
	str r4, [fp, #-64]
	ldr r4, =0
	str r4, [fp, #-68]
	b .L70
.L70:
	ldr r4, [fp, #-68]
	cmp r4, #10
	movlt r4, #1
	movge r4, #0
	blt .L71
	b .L75
.L71:
	ldr r4, [fp, #-68]
	add r5, r4, #1
	ldr r4, [fp, #-68]
	mov r6, #-60
	mov r7, #4
	mul r8, r4, r7
	add r4, r6, r8
	add r6, fp, r4
	str r5, [r6]
	ldr r4, [fp, #-68]
	add r5, r4, #1
	str r5, [fp, #-68]
	b .L70
.L72:
	ldr r4, =10
	str r4, [fp, #-4]
	bl getint
	mov r4, r0
	str r4, [fp, #-20]
	ldr r4, [fp, #-4]
	sub r5, r4, #1
	str r5, [fp, #-16]
	ldr r4, =0
	str r4, [fp, #-12]
	ldr r4, [fp, #-16]
	ldr r5, [fp, #-12]
	add r6, r4, r5
	ldr r4, =2
	sdiv r5, r6, r4
	str r5, [fp, #-8]
	b .L81
.L75:
	b .L72
.L81:
	ldr r4, [fp, #-8]
	mov r5, #-60
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	add r5, fp, r4
	ldr r4, [r5]
	ldr r5, [fp, #-20]
	cmp r4, r5
	bne .L84
	b .L88
.L82:
	ldr r4, [fp, #-16]
	ldr r5, [fp, #-12]
	add r6, r4, r5
	ldr r4, =2
	sdiv r5, r6, r4
	str r5, [fp, #-8]
	ldr r4, [fp, #-20]
	ldr r5, [fp, #-8]
	mov r6, #-60
	mov r7, #4
	mul r8, r5, r7
	add r5, r6, r8
	add r6, fp, r5
	ldr r5, [r6]
	cmp r4, r5
	movlt r4, #1
	movge r4, #0
	blt .L92
	b .L98
.L83:
	ldr r4, [fp, #-20]
	ldr r5, [fp, #-8]
	mov r6, #-60
	mov r7, #4
	mul r8, r5, r7
	add r5, r6, r8
	add r6, fp, r5
	ldr r5, [r6]
	cmp r4, r5
	beq .L99
	b .L105
.L84:
	ldr r4, [fp, #-12]
	ldr r5, [fp, #-16]
	cmp r4, r5
	movlt r4, #1
	movge r4, #0
	blt .L82
	b .L91
.L88:
	b .L83
.L91:
	b .L83
.L92:
	ldr r4, [fp, #-8]
	sub r5, r4, #1
	str r5, [fp, #-16]
	b .L94
.L93:
	ldr r4, [fp, #-8]
	add r5, r4, #1
	str r5, [fp, #-12]
	b .L94
.L94:
	b .L81
.L98:
	b .L93
.L99:
	ldr r4, [fp, #-20]
	mov r0, r4
	bl putint
	mov r4, r0
	b .L101
.L100:
	ldr r4, =0
	str r4, [fp, #-20]
	ldr r4, [fp, #-20]
	mov r0, r4
	bl putint
	mov r4, r0
	b .L101
.L101:
	ldr r4, =10
	str r4, [fp, #-20]
	ldr r4, [fp, #-20]
	mov r0, r4
	bl putch
	mov r4, r0
	mov r0, #0
	add sp, sp, #68
	pop {r4, r5, r6, r7, r8, fp, lr}
	bx lr
.L105:
	b .L100

