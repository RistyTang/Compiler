                                                                                                                                                                                                                      	.arch armv8-a
	.arch_extension crc
	.arm
	.text
	.global main
	.type main , %function
main:
	push {r4, r5, r6, r7, fp, lr}
	mov fp, sp
	sub sp, sp, #16
.L42:
	ldr r4, =0
	str r4, [fp, #-16]
	ldr r4, =0
	str r4, [fp, #-12]
	ldr r4, =0
	str r4, [fp, #-8]
	b .L47
.L47:
	ldr r4, [fp, #-16]
	cmp r4, #21
	movlt r4, #1
	movge r4, #0
	blt .L48
	b .L52
.L48:
	b .L53
.L49:
	mov r0, #0
	add sp, sp, #16
	pop {r4, r5, r6, r7, fp, lr}
	bx lr
.L50:
.L51:
.L52:
	b .L49
.L53:
	ldr r4, [fp, #-12]
	ldr r5, [fp, #-16]
	ldr r6, =101
	sub r7, r6, r5
	cmp r4, r7
	movlt r4, #1
	movge r4, #0
	blt .L54
	b .L58
.L54:
	ldr r4, [fp, #-16]
	ldr r5, =100
	sub r6, r5, r4
	ldr r4, [fp, #-12]
	sub r5, r6, r4
	str r5, [fp, #-8]
	ldr r4, [fp, #-16]
	ldr r5, =5
	mul r6, r5, r4
	ldr r4, [fp, #-12]
	ldr r5, =1
	mul r7, r5, r4
	add r4, r6, r7
	ldr r5, [fp, #-8]
	ldr r6, =2
	sdiv r7, r5, r6
	add r5, r4, r7
	cmp r5, #100
	beq .L59
	b .L63
.L55:
	ldr r4, [fp, #-16]
	add r5, r4, #1
	str r5, [fp, #-16]
	b .L47
.L56:
.L57:
.L58:
	b .L55
.L59:
	ldr r4, [fp, #-16]
	mov r0, r4
	bl putint
	mov r4, r0
	ldr r4, [fp, #-12]
	mov r0, r4
	bl putint
	mov r4, r0
	ldr r4, [fp, #-8]
	mov r0, r4
	bl putint
	mov r4, r0
	ldr r4, =10
	str r4, [fp, #-4]
	ldr r4, [fp, #-4]
	mov r0, r4
	bl putch
	mov r4, r0
	b .L60
.L60:
	ldr r4, [fp, #-12]
	add r5, r4, #1
	str r5, [fp, #-12]
	b .L53
.L61:
.L62:
.L63:
	b .L60

