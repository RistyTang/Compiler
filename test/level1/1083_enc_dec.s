                                                                                                                 	.arch armv8-a
	.arch_extension crc
	.arm
	.text
	.global enc
	.type enc , %function
enc:
	push {r4, r5, fp, lr}
	mov fp, sp
	sub sp, sp, #4
.L36:
	str r0, [fp, #-4]
	ldr r4, [fp, #-4]
	cmp r4, #25
	movgt r4, #1
	movle r4, #0
	bgt .L38
	b .L43
.L38:
	ldr r4, [fp, #-4]
	add r5, r4, #60
	str r5, [fp, #-4]
	b .L40
.L39:
	ldr r4, [fp, #-4]
	sub r5, r4, #15
	str r5, [fp, #-4]
	b .L40
.L40:
	ldr r4, [fp, #-4]
	mov r0, r4
	add sp, sp, #4
	pop {r4, r5, fp, lr}
	bx lr
.L41:
.L42:
.L43:
	b .L39

	.global dec
	.type dec , %function
dec:
	push {r4, r5, fp, lr}
	mov fp, sp
	sub sp, sp, #4
.L44:
	str r0, [fp, #-4]
	ldr r4, [fp, #-4]
	cmp r4, #85
	movgt r4, #1
	movle r4, #0
	bgt .L46
	b .L51
.L46:
	ldr r4, [fp, #-4]
	sub r5, r4, #59
	str r5, [fp, #-4]
	b .L48
.L47:
	ldr r4, [fp, #-4]
	add r5, r4, #14
	str r5, [fp, #-4]
	b .L48
.L48:
	ldr r4, [fp, #-4]
	mov r0, r4
	add sp, sp, #4
	pop {r4, r5, fp, lr}
	bx lr
.L49:
.L50:
.L51:
	b .L47

	.global main
	.type main , %function
main:
	push {r4, fp, lr}
	mov fp, sp
	sub sp, sp, #8
.L52:
	ldr r4, =400
	str r4, [fp, #-8]
	ldr r4, [fp, #-8]
	mov r0, r4
	bl enc
	mov r4, r0
	str r4, [fp, #-4]
	ldr r4, [fp, #-4]
	mov r0, r4
	bl dec
	mov r4, r0
	str r4, [fp, #-4]
	ldr r4, [fp, #-4]
	mov r0, r4
	bl putint
	mov r4, r0
	ldr r4, =10
	str r4, [fp, #-4]
	ldr r4, [fp, #-4]
	mov r0, r4
	bl putch
	mov r4, r0
	mov r0, #0
	add sp, sp, #8
	pop {r4, fp, lr}
	bx lr

