                                                                                                                                        	.arch armv8-a
	.arch_extension crc
	.arm
	.text
	.global move
	.type move , %function
move:
	push {r4, fp, lr}
	mov fp, sp
	sub sp, sp, #8
.L44:
	str r0, [fp, #-8]
	str r1, [fp, #-4]
	ldr r4, [fp, #-8]
	mov r0, r4
	bl putint
	mov r4, r0
	mov r0, #32
	bl putch
	mov r4, r0
	ldr r4, [fp, #-4]
	mov r0, r4
	bl putint
	mov r4, r0
	mov r0, #44
	bl putch
	mov r4, r0
	mov r0, #32
	bl putch
	mov r4, r0
	add sp, sp, #8
	pop {r4, fp, lr}
	bx lr

	.global hanoi
	.type hanoi , %function
hanoi:
	push {r4, r5, r6, r7, fp, lr}
	mov fp, sp
	sub sp, sp, #16
.L47:
	str r0, [fp, #-16]
	str r1, [fp, #-12]
	str r2, [fp, #-8]
	str r3, [fp, #-4]
	ldr r4, [fp, #-16]
	cmp r4, #1
	beq .L52
	b .L57
.L52:
	ldr r4, [fp, #-12]
	ldr r5, [fp, #-4]
	mov r0, r4
	mov r1, r5
	bl move
	b .L54
.L53:
	ldr r4, [fp, #-16]
	sub r5, r4, #1
	ldr r4, [fp, #-12]
	ldr r6, [fp, #-4]
	ldr r7, [fp, #-8]
	mov r0, r5
	mov r1, r4
	mov r2, r6
	mov r3, r7
	bl hanoi
	ldr r4, [fp, #-12]
	ldr r5, [fp, #-4]
	mov r0, r4
	mov r1, r5
	bl move
	ldr r4, [fp, #-16]
	sub r5, r4, #1
	ldr r4, [fp, #-8]
	ldr r6, [fp, #-12]
	ldr r7, [fp, #-4]
	mov r0, r5
	mov r1, r4
	mov r2, r6
	mov r3, r7
	bl hanoi
	b .L54
.L54:
	add sp, sp, #16
	pop {r4, r5, r6, r7, fp, lr}
	bx lr
.L55:
	add sp, sp, #16
	pop {r4, r5, r6, r7, fp, lr}
	bx lr
.L56:
	add sp, sp, #16
	pop {r4, r5, r6, r7, fp, lr}
	bx lr
.L57:
	b .L53

	.global main
	.type main , %function
main:
	push {r4, r5, fp, lr}
	mov fp, sp
	sub sp, sp, #4
.L58:
	bl getint
	mov r4, r0
	str r4, [fp, #-4]
	b .L60
.L60:
	ldr r4, [fp, #-4]
	cmp r4, #0
	movgt r4, #1
	movle r4, #0
	bgt .L61
	b .L65
.L61:
	bl getint
	mov r4, r0
	mov r0, r4
	mov r1, #1
	mov r2, #2
	mov r3, #3
	bl hanoi
	mov r0, #10
	bl putch
	mov r4, r0
	ldr r4, [fp, #-4]
	sub r5, r4, #1
	str r5, [fp, #-4]
	b .L60
.L62:
	mov r0, #0
	add sp, sp, #4
	pop {r4, r5, fp, lr}
	bx lr
.L65:
	b .L62

