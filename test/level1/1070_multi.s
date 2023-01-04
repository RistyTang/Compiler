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
.L15:
	ldr r4, =0
	str r4, [fp, #-4]
	ldr r4, =0
	str r4, [fp, #-8]
	b .L18
.L18:
	ldr r4, [fp, #-8]
	cmp r4, #21
	movlt r4, #1
	movge r4, #0
	blt .L19
	b .L23
.L19:
	ldr r4, [fp, #-4]
	ldr r5, [fp, #-8]
	mul r6, r4, r5
	str r6, [fp, #-4]
	ldr r4, [fp, #-8]
	add r5, r4, #1
	str r5, [fp, #-8]
	b .L18
.L20:
	ldr r4, [fp, #-4]
	mov r0, r4
	bl putint
	mov r4, r0
	mov r0, #0
	add sp, sp, #8
	pop {r4, r5, r6, fp, lr}
	bx lr
.L21:
.L22:
.L23:
	b .L20

