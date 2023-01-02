                                                                                                                                                                                                                                                                                                                 	.arch armv8-a
	.arch_extension crc
	.arm
	.text
	.global main
	.type main , %function
main:
	push {r4, r5, r6, r7, r8, fp, lr}
	mov fp, sp
	sub sp, sp, #76
.L61:
	ldr r4, =0
	str r4, [fp, #-72]
	ldr r4, =0
	str r4, [fp, #-76]
	b .L65
.L65:
	ldr r4, [fp, #-76]
	cmp r4, #10
	movlt r4, #1
	movge r4, #0
	blt .L66
	b .L70
.L66:
	ldr r4, [fp, #-76]
	add r5, r4, #1
	ldr r4, [fp, #-76]
	mov r6, #-68
	mov r7, #4
	mul r8, r4, r7
	add r4, r6, r8
	add r6, fp, r4
	str r5, [r6]
	ldr r4, [fp, #-76]
	add r5, r4, #1
	str r5, [fp, #-76]
	b .L65
.L67:
	ldr r4, =10
	str r4, [fp, #-12]
	bl getint
	mov r4, r0
	str r4, [fp, #-28]
	ldr r4, [fp, #-12]
	sub r5, r4, #1
	str r5, [fp, #-24]
	ldr r4, =0
	str r4, [fp, #-20]
	ldr r4, [fp, #-24]
	ldr r5, [fp, #-20]
	add r6, r4, r5
	ldr r4, =2
	sdiv r5, r6, r4
	str r5, [fp, #-16]
	ldr r4, =0
	str r4, [fp, #-8]
	ldr r4, =0
	str r4, [fp, #-76]
	ldr r4, =0
	str r4, [fp, #-4]
	b .L78
.L70:
	b .L67
.L78:
	ldr r4, [fp, #-76]
	cmp r4, #10
	movlt r4, #1
	movge r4, #0
	blt .L81
	b .L84
.L79:
	ldr r4, [fp, #-76]
	mov r5, #-68
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	add r5, fp, r4
	ldr r4, [r5]
	ldr r5, [fp, #-28]
	cmp r4, r5
	beq .L88
	b .L93
.L80:
	ldr r4, [fp, #-8]
	cmp r4, #1
	beq .L94
	b .L99
.L81:
	ldr r4, [fp, #-8]
	cmp r4, #0
	beq .L79
	b .L87
.L84:
	b .L80
.L87:
	b .L80
.L88:
	ldr r4, =1
	str r4, [fp, #-8]
	ldr r4, [fp, #-76]
	str r4, [fp, #-4]
	b .L89
.L89:
	ldr r4, [fp, #-76]
	add r5, r4, #1
	str r5, [fp, #-76]
	b .L78
.L93:
	b .L89
.L94:
	ldr r4, [fp, #-4]
	mov r0, r4
	bl putint
	mov r4, r0
	b .L96
.L95:
	ldr r4, =0
	str r4, [fp, #-28]
	ldr r4, [fp, #-28]
	mov r0, r4
	bl putint
	mov r4, r0
	b .L96
.L96:
	ldr r4, =10
	str r4, [fp, #-28]
	ldr r4, [fp, #-28]
	mov r0, r4
	bl putch
	mov r4, r0
	mov r0, #0
	add sp, sp, #76
	pop {r4, r5, r6, r7, r8, fp, lr}
	bx lr
.L99:
	b .L95

