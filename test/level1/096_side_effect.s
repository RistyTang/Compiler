                                                                                                                                                                                                 	.arch armv8-a
	.arch_extension crc
	.arm
	.data
	.global a
	.align 4
	.size a, 4
a:
	.word -1
	.global b
	.align 4
	.size b, 4
b:
	.word 1
	.text
	.global inc_a
	.type inc_a , %function
inc_a:
	push {r4, r5, fp, lr}
	mov fp, sp
	sub sp, sp, #4
.L56:
	ldr r4, addr_a0
	ldr r5, [r4]
	str r5, [fp, #-4]
	ldr r4, [fp, #-4]
	add r5, r4, #1
	str r5, [fp, #-4]
	ldr r4, [fp, #-4]
	ldr r5, addr_a0
	str r4, [r5]
	ldr r4, addr_a0
	ldr r5, [r4]
	mov r0, r5
	add sp, sp, #4
	pop {r4, r5, fp, lr}
	bx lr

	.global main
	.type main , %function
main:
	push {r4, r5, r6, fp, lr}
	mov fp, sp
	sub sp, sp, #4
.L58:
	ldr r4, =5
	str r4, [fp, #-4]
	b .L60
.L60:
	ldr r4, [fp, #-4]
	cmp r4, #0
	movge r4, #1
	movlt r4, #0
	bge .L61
	b .L65
.L61:
	bl inc_a
	mov r4, r0
	cmp r4, #0
	bne .L69
	b .L71
.L62:
	ldr r4, addr_a0
	ldr r5, [r4]
	mov r0, r5
	bl putint
	mov r4, r0
	mov r0, #32
	bl putch
	mov r4, r0
	ldr r4, addr_b0
	ldr r5, [r4]
	mov r0, r5
	bl putint
	mov r4, r0
	mov r0, #10
	bl putch
	mov r4, r0
	ldr r4, addr_a0
	ldr r5, [r4]
	mov r0, r5
	add sp, sp, #4
	pop {r4, r5, r6, fp, lr}
	bx lr
.L63:
.L64:
.L65:
	b .L62
.L66:
	ldr r4, addr_a0
	ldr r5, [r4]
	mov r0, r5
	bl putint
	mov r4, r0
	mov r0, #32
	bl putch
	mov r4, r0
	ldr r4, addr_b0
	ldr r5, [r4]
	mov r0, r5
	bl putint
	mov r4, r0
	mov r0, #10
	bl putch
	mov r4, r0
	b .L67
.L67:
	bl inc_a
	mov r4, r0
	cmp r4, #14
	movlt r4, #1
	movge r4, #0
	blt .L79
	b .L85
.L68:
	bl inc_a
	mov r4, r0
	cmp r4, #0
	bne .L66
	b .L77
.L69:
	bl inc_a
	mov r4, r0
	cmp r4, #0
	bne .L68
	b .L74
.L70:
.L71:
	b .L67
.L72:
.L73:
.L74:
	b .L67
.L75:
.L76:
.L77:
	b .L67
.L78:
.L79:
	ldr r4, addr_a0
	ldr r5, [r4]
	mov r0, r5
	bl putint
	mov r4, r0
	mov r0, #10
	bl putch
	mov r4, r0
	ldr r4, addr_b0
	ldr r5, [r4]
	ldr r4, =2
	mul r6, r5, r4
	ldr r4, addr_b0
	str r6, [r4]
	b .L81
.L80:
	bl inc_a
	mov r4, r0
	b .L81
.L81:
	ldr r4, [fp, #-4]
	sub r5, r4, #1
	str r5, [fp, #-4]
	b .L60
.L82:
	bl inc_a
	mov r4, r0
	cmp r4, #0
	bne .L86
	b .L88
.L83:
.L84:
.L85:
	b .L82
.L86:
	bl inc_a
	mov r4, r0
	bl inc_a
	mov r5, r0
	sub r6, r4, r5
	add r4, r6, #1
	cmp r4, #0
	bne .L79
	b .L91
.L87:
.L88:
	b .L80
.L89:
.L90:
.L91:
	b .L80
.L92:

addr_a0:
	.word a
addr_b0:
	.word b
