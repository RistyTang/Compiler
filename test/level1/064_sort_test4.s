                                                                                                                                                                                                                                                                                                                                                                    	.arch armv8-a
	.arch_extension crc
	.arm
	.data
	.global n
	.align 4
	.size n, 4
n:
	.word 0
	.text
	.global select_sort
	.type select_sort , %function
select_sort:
	push {r4, r5, r6, r7, r8, fp, lr}
	mov fp, sp
	sub sp, sp, #24
.L81:
	str r0, [fp, #-24]
	str r1, [fp, #-20]
	ldr r4, =0
	str r4, [fp, #-16]
	b .L87
.L87:
	ldr r4, [fp, #-16]
	ldr r5, [fp, #-20]
	sub r6, r5, #1
	cmp r4, r6
	movlt r4, #1
	movge r4, #0
	blt .L88
	b .L92
.L88:
	ldr r4, [fp, #-16]
	str r4, [fp, #-8]
	ldr r4, [fp, #-16]
	add r5, r4, #1
	str r5, [fp, #-12]
	b .L93
.L89:
	mov r0, #0
	add sp, sp, #24
	pop {r4, r5, r6, r7, r8, fp, lr}
	bx lr
.L92:
	b .L89
.L93:
	ldr r4, [fp, #-12]
	ldr r5, [fp, #-20]
	cmp r4, r5
	movlt r4, #1
	movge r4, #0
	blt .L94
	b .L98
.L94:
	ldr r4, [fp, #-24]
	ldr r5, [fp, #-8]
	mov r7, #4
	mul r6, r5, r7
	add r5, r4, r6
	ldr r4, [r5]
	ldr r5, [fp, #-24]
	ldr r6, [fp, #-12]
	mov r7, #4
	mul r8, r6, r7
	add r6, r5, r8
	ldr r5, [r6]
	cmp r4, r5
	movgt r4, #1
	movle r4, #0
	bgt .L99
	b .L107
.L95:
	ldr r4, [fp, #-8]
	ldr r5, [fp, #-16]
	cmp r4, r5
	bne .L108
	b .L112
.L98:
	b .L95
.L99:
	ldr r4, [fp, #-12]
	str r4, [fp, #-8]
	b .L100
.L100:
	ldr r4, [fp, #-12]
	add r5, r4, #1
	str r5, [fp, #-12]
	b .L93
.L107:
	b .L100
.L108:
	ldr r4, [fp, #-24]
	ldr r5, [fp, #-8]
	mov r6, #4
	mul r7, r5, r6
	add r5, r4, r7
	ldr r4, [r5]
	str r4, [fp, #-4]
	ldr r4, [fp, #-24]
	ldr r5, [fp, #-16]
	mov r6, #4
	mul r7, r5, r6
	add r5, r4, r7
	ldr r4, [r5]
	ldr r5, [fp, #-24]
	ldr r6, [fp, #-8]
	mov r7, #4
	mul r8, r6, r7
	add r6, r5, r8
	str r4, [r6]
	ldr r4, [fp, #-4]
	ldr r5, [fp, #-24]
	ldr r6, [fp, #-16]
	mov r7, #4
	mul r8, r6, r7
	add r6, r5, r8
	str r4, [r6]
	b .L109
.L109:
	ldr r4, [fp, #-16]
	add r5, r4, #1
	str r5, [fp, #-16]
	b .L87
.L112:
	b .L109

	.global main
	.type main , %function
main:
	push {r4, r5, r6, r7, fp, lr}
	mov fp, sp
	sub sp, sp, #48
.L120:
	ldr r4, =10
	ldr r5, addr_n0
	str r4, [r5]
	mov r4, #0
	mov r5, #-48
	mov r7, #4
	mul r6, r4, r7
	add r4, r5, r6
	add r5, fp, r4
	ldr r4, =4
	str r4, [r5]
	mov r4, #1
	mov r5, #-48
	mov r7, #4
	mul r6, r4, r7
	add r4, r5, r6
	add r5, fp, r4
	ldr r4, =3
	str r4, [r5]
	mov r4, #2
	mov r5, #-48
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	add r5, fp, r4
	ldr r4, =9
	str r4, [r5]
	mov r4, #3
	mov r5, #-48
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	add r5, fp, r4
	ldr r4, =2
	str r4, [r5]
	mov r4, #4
	mov r5, #-48
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	add r5, fp, r4
	ldr r4, =0
	str r4, [r5]
	mov r4, #5
	mov r5, #-48
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	add r5, fp, r4
	ldr r4, =1
	str r4, [r5]
	mov r4, #6
	mov r5, #-48
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	add r5, fp, r4
	ldr r4, =6
	str r4, [r5]
	mov r4, #7
	mov r5, #-48
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	add r5, fp, r4
	ldr r4, =5
	str r4, [r5]
	mov r4, #8
	mov r5, #-48
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	add r5, fp, r4
	ldr r4, =7
	str r4, [r5]
	mov r4, #9
	mov r5, #-48
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	add r5, fp, r4
	ldr r4, =8
	str r4, [r5]
	ldr r4, =0
	str r4, [fp, #-8]
	mov r4, #0
	mov r5, #-48
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	add r5, fp, r4
	ldr r4, addr_n0
	ldr r6, [r4]
	mov r0, r5
	mov r1, r6
	bl select_sort
	mov r4, r0
	str r4, [fp, #-8]
	b .L123
.L123:
	ldr r4, [fp, #-8]
	ldr r5, addr_n0
	ldr r6, [r5]
	cmp r4, r6
	movlt r4, #1
	movge r4, #0
	blt .L124
	b .L128
.L124:
	ldr r4, [fp, #-8]
	mov r5, #-48
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	add r5, fp, r4
	ldr r4, [r5]
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
	ldr r4, [fp, #-8]
	add r5, r4, #1
	str r5, [fp, #-8]
	b .L123
.L125:
	mov r0, #0
	add sp, sp, #48
	pop {r4, r5, r6, r7, fp, lr}
	bx lr
.L128:
	b .L125

addr_n0:
	.word n
