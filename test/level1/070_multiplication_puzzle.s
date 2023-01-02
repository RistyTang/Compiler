   	 		 																									 																																		 	.arch armv8-a
	.arch_extension crc
	.arm
	.data
	.global a
	.align 4
	.size a, 24
a:
	.word 10
	.word 1
	.word 50
	.word 50
	.word 20
	.word 5
	.comm dp, 400, 4
	.text
	.global main
	.type main , %function
main:
	push {r4, r5, r6, r7, r8, r9, fp, lr}
	mov fp, sp
	sub sp, sp, #24
.L76:
	ldr r4, =6
	str r4, [fp, #-24]
	ldr r4, =3
	str r4, [fp, #-20]
	b .L83
.L83:
	ldr r4, [fp, #-20]
	ldr r5, [fp, #-24]
	cmp r4, r5
	movle r4, #1
	movgt r4, #0
	ble .L84
	b .L88
.L84:
	ldr r4, =0
	str r4, [fp, #-16]
	b .L89
.L85:
	mov r4, #0
	ldr r5, addr_dp0
	mov r6, #40
	mul r7, r4, r6
	add r4, r5, r7
	mov r5, r4
	ldr r4, [fp, #-24]
	sub r6, r4, #1
	mov r4, #4
	mul r7, r6, r4
	add r4, r5, r7
	ldr r5, [r4]
	mov r0, r5
	bl putint
	mov r4, r0
	mov r0, #0
	add sp, sp, #24
	pop {r4, r5, r6, r7, r8, r9, fp, lr}
	bx lr
.L88:
	b .L85
.L89:
	ldr r4, [fp, #-16]
	ldr r5, [fp, #-24]
	ldr r6, [fp, #-20]
	sub r7, r5, r6
	add r5, r7, #1
	cmp r4, r5
	movlt r4, #1
	movge r4, #0
	blt .L90
	b .L94
.L90:
	ldr r4, [fp, #-16]
	ldr r5, [fp, #-20]
	add r6, r4, r5
	sub r4, r6, #1
	str r4, [fp, #-8]
	ldr r4, [fp, #-16]
	add r5, r4, #1
	str r5, [fp, #-12]
	b .L95
.L91:
	ldr r4, [fp, #-20]
	add r5, r4, #1
	str r5, [fp, #-20]
	b .L83
.L94:
	b .L91
.L95:
	ldr r4, [fp, #-12]
	ldr r5, [fp, #-8]
	cmp r4, r5
	movlt r4, #1
	movge r4, #0
	blt .L96
	b .L100
.L96:
	ldr r4, [fp, #-16]
	ldr r5, addr_dp0
	mov r6, #40
	mul r7, r4, r6
	add r4, r5, r7
	mov r5, r4
	ldr r4, [fp, #-12]
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	ldr r5, [r4]
	ldr r4, [fp, #-12]
	ldr r6, addr_dp0
	mov r7, #40
	mul r8, r4, r7
	add r4, r6, r8
	mov r6, r4
	ldr r4, [fp, #-8]
	mov r7, #4
	mul r8, r4, r7
	add r4, r6, r8
	ldr r6, [r4]
	add r4, r5, r6
	ldr r5, [fp, #-16]
	ldr r6, addr_a0
	mov r7, #4
	mul r8, r5, r7
	add r5, r6, r8
	mov r6, r5
	ldr r5, [r6]
	ldr r6, [fp, #-12]
	ldr r7, addr_a0
	mov r8, #4
	mul r9, r6, r8
	add r6, r7, r9
	mov r7, r6
	ldr r6, [r7]
	mul r7, r5, r6
	ldr r5, [fp, #-8]
	ldr r6, addr_a0
	mov r9, #4
	mul r8, r5, r9
	add r5, r6, r8
	mov r6, r5
	ldr r5, [r6]
	mul r6, r7, r5
	add r5, r4, r6
	str r5, [fp, #-4]
	ldr r4, [fp, #-16]
	ldr r5, addr_dp0
	mov r6, #40
	mul r7, r4, r6
	add r4, r5, r7
	mov r5, r4
	ldr r4, [fp, #-8]
	mov r7, #4
	mul r6, r4, r7
	add r4, r5, r6
	ldr r5, [r4]
	cmp r5, #0
	moveq r4, #1
	movne r4, #0
	cmp r4, #0
	bne .L108
	b .L115
.L97:
	ldr r4, [fp, #-16]
	add r5, r4, #1
	str r5, [fp, #-16]
	b .L89
.L100:
	b .L97
.L108:
	ldr r4, [fp, #-4]
	ldr r5, [fp, #-16]
	ldr r6, addr_dp0
	mov r7, #40
	mul r8, r5, r7
	add r5, r6, r8
	mov r6, r5
	ldr r5, [fp, #-8]
	mov r8, #4
	mul r7, r5, r8
	add r5, r6, r7
	str r4, [r5]
	b .L109
.L109:
	ldr r4, [fp, #-12]
	add r5, r4, #1
	str r5, [fp, #-12]
	b .L95
.L110:
	ldr r4, [fp, #-4]
	ldr r5, [fp, #-16]
	ldr r6, addr_dp0
	mov r7, #40
	mul r8, r5, r7
	add r5, r6, r8
	mov r6, r5
	ldr r5, [fp, #-8]
	mov r7, #4
	mul r8, r5, r7
	add r5, r6, r8
	ldr r6, [r5]
	cmp r4, r6
	movlt r4, #1
	movge r4, #0
	blt .L108
	b .L121
	b .F0
.LTORG
addr_a0:
	.word a
addr_dp0:
	.word dp
.F0:
.L115:
	b .L110
.L121:
	b .L109

addr_a1:
	.word a
addr_dp1:
	.word dp
