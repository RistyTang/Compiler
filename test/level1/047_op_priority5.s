                	 	                                						 	.arch armv8-a
	.arch_extension crc
	.arm
	.data
	.global a
	.align 4
	.size a, 4
a:
	.word 1
	.global b
	.align 4
	.size b, 4
b:
	.word 0
	.global c
	.align 4
	.size c, 4
c:
	.word 1
	.global d
	.align 4
	.size d, 4
d:
	.word 2
	.global e
	.align 4
	.size e, 4
e:
	.word 4
	.text
	.global main
	.type main , %function
main:
	push {r4, r5, r6, r7, r8, fp, lr}
	mov fp, sp
	sub sp, sp, #4
.L43:
	ldr r4, =0
	str r4, [fp, #-4]
	ldr r4, addr_a0
	ldr r5, [r4]
	ldr r4, addr_b0
	ldr r6, [r4]
	mul r4, r5, r6
	ldr r5, addr_c0
	ldr r6, [r5]
	sdiv r5, r4, r6
	ldr r4, addr_e0
	ldr r6, [r4]
	ldr r4, addr_d0
	ldr r7, [r4]
	add r4, r6, r7
	cmp r5, r4
	beq .L48
	b .L51
.L45:
	ldr r4, =1
	str r4, [fp, #-4]
	b .L46
.L46:
	ldr r4, [fp, #-4]
	mov r0, r4
	bl putint
	mov r4, r0
	ldr r4, [fp, #-4]
	mov r0, r4
	add sp, sp, #4
	pop {r4, r5, r6, r7, r8, fp, lr}
	bx lr
.L47:
	ldr r4, addr_a0
	ldr r5, [r4]
	ldr r4, addr_b0
	ldr r6, [r4]
	ldr r4, addr_c0
	ldr r7, [r4]
	mul r4, r6, r7
	sub r6, r5, r4
	ldr r4, addr_d0
	ldr r5, [r4]
	ldr r4, addr_a0
	ldr r7, [r4]
	ldr r4, addr_c0
	ldr r8, [r4]
	sdiv r4, r7, r8
	sub r7, r5, r4
	cmp r6, r7
	beq .L45
	b .L57
.L48:
	ldr r4, addr_a0
	ldr r5, [r4]
	ldr r4, addr_a0
	ldr r6, [r4]
	ldr r4, addr_b0
	ldr r7, [r4]
	add r4, r6, r7
	mul r6, r5, r4
	ldr r4, addr_c0
	ldr r5, [r4]
	add r4, r6, r5
	ldr r5, addr_d0
	ldr r6, [r5]
	ldr r5, addr_e0
	ldr r7, [r5]
	add r5, r6, r7
	cmp r4, r5
	movle r4, #1
	movgt r4, #0
	ble .L45
	b .L54
.L49:
.L50:
.L51:
	b .L47
.L52:
.L53:
.L54:
	b .L47
.L55:
.L56:
.L57:
	b .L46

addr_a0:
	.word a
addr_b0:
	.word b
addr_c0:
	.word c
addr_d0:
	.word d
addr_e0:
	.word e
