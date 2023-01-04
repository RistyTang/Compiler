                                                                                                                                                                                                                                                                                                                                                                                                                   	.arch armv8-a
	.arch_extension crc
	.arm
	.data
	.global b
	.align 4
	.size b, 4
b:
	.word 5
	.global c
	.align 4
	.size c, 16
c:
	.word 6
	.word 7
	.word 8
	.word 9
	.text
	.global main
	.type main , %function
main:
	push {r4, r5, r6, r7, fp, lr}
	mov fp, sp
	sub sp, sp, #220
.L53:
	ldr r4, =1
	str r4, [fp, #-220]
	ldr r4, =2
	str r4, [fp, #-216]
	ldr r4, =3
	str r4, [fp, #-216]
	ldr r4, [fp, #-216]
	mov r0, r4
	bl putint
	mov r4, r0
	ldr r4, [fp, #-216]
	mov r0, r4
	bl putint
	mov r4, r0
	ldr r4, [fp, #-220]
	mov r0, r4
	bl putint
	mov r4, r0
	mov r0, #10
	bl putch
	mov r4, r0
	b .L56
.L56:
	ldr r4, [fp, #-220]
	cmp r4, #5
	movlt r4, #1
	movge r4, #0
	blt .L57
	b .L61
.L57:
	ldr r4, =0
	str r4, [fp, #-212]
	ldr r4, [fp, #-212]
	add r5, r4, #1
	str r5, [fp, #-212]
	ldr r4, [fp, #-212]
	cmp r4, #0
	bne .L63
	b .L66
.L58:
	ldr r4, [fp, #-220]
	mov r0, r4
	bl putint
	mov r4, r0
	mov r0, #10
	bl putch
	mov r4, r0
	mov r4, #2
	ldr r5, addr_c0
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	mov r5, r4
	ldr r4, =1
	str r4, [r5]
	mov r4, #0
	mov r5, #-208
	mov r6, #32
	mul r7, r4, r6
	add r4, r5, r7
	add r5, fp, r4
	mov r4, #0
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	ldr r5, =0
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =9
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =0
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =0
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =0
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =0
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =0
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =0
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =8
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =3
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =0
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =0
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =0
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =0
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =0
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =0
	str r4, [r5]
	ldr r4, =2
	str r4, [fp, #-144]
	mov r4, #2
	ldr r5, addr_c0
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	mov r5, r4
	ldr r4, [r5]
	cmp r4, #0
	bne .L103
	b .L107
.L59:
.L60:
.L61:
	b .L58
.L63:
	b .L58
.L64:
	b .L56
.L65:
.L66:
	b .L64
.L67:
.L68:
	b .L64
.L103:
	mov r4, #0
	mov r5, #-140
	mov r7, #20
	mul r6, r4, r7
	add r4, r5, r6
	add r5, fp, r4
	mov r4, #0
	mov r6, #20
	mul r7, r4, r6
	add r4, r5, r7
	mov r5, #0
	mov r6, #4
	mul r7, r5, r6
	add r5, r4, r7
	ldr r4, =0
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =0
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =0
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =0
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =0
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =0
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =0
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =0
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =0
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =0
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =2
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =1
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =8
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =0
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =0
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =0
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =0
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =0
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =0
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =0
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =0
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =0
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =0
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =0
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =0
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =0
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =0
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =0
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =0
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =0
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =0
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =0
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =0
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =0
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =0
	str r4, [r5]
	ldr r4, [fp, #-144]
	mov r5, #-140
	mov r6, #20
	mul r7, r4, r6
	add r4, r5, r7
	add r5, fp, r4
	mov r4, #0
	mov r7, #20
	mul r6, r4, r7
	add r4, r5, r6
	mov r5, #0
	mov r6, #4
	mul r7, r5, r6
	add r5, r4, r7
	ldr r4, [r5]
	mov r0, r4
	bl putint
	mov r4, r0
	ldr r4, [fp, #-144]
	mov r5, #-140
	mov r6, #20
	mul r7, r4, r6
	add r4, r5, r7
	add r5, fp, r4
	mov r4, #0
	mov r7, #20
	mul r6, r4, r7
	add r4, r5, r6
	mov r5, #1
	mov r6, #4
	mul r7, r5, r6
	add r5, r4, r7
	ldr r4, [r5]
	mov r0, r4
	bl putint
	mov r4, r0
	ldr r4, [fp, #-144]
	mov r5, #-140
	mov r6, #20
	mul r7, r4, r6
	add r4, r5, r7
	add r5, fp, r4
	mov r4, #0
	mov r6, #20
	mul r7, r4, r6
	add r4, r5, r7
	mov r5, #2
	mov r6, #4
	mul r7, r5, r6
	add r5, r4, r7
	ldr r4, [r5]
	mov r0, r4
	bl putint
	mov r4, r0
	b .L104
	b .F0
.LTORG
addr_b0:
	.word b
addr_c0:
	.word c
.F0:
.L104:
	mov r0, #10
	bl putch
	mov r4, r0
	ldr r4, addr_b1
	ldr r5, [r4]
	mov r0, r5
	bl putint
	mov r4, r0
	mov r0, #10
	bl putch
	mov r4, r0
	mov r4, #0
	ldr r5, addr_c1
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	mov r5, r4
	ldr r4, [r5]
	mov r0, r4
	bl putint
	mov r4, r0
	mov r4, #1
	ldr r5, addr_c1
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	mov r5, r4
	ldr r4, [r5]
	mov r0, r4
	bl putint
	mov r4, r0
	mov r4, #2
	ldr r5, addr_c1
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	mov r5, r4
	ldr r4, [r5]
	mov r0, r4
	bl putint
	mov r4, r0
	mov r4, #3
	ldr r5, addr_c1
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	mov r5, r4
	ldr r4, [r5]
	mov r0, r4
	bl putint
	mov r4, r0
	mov r0, #10
	bl putch
	mov r4, r0
	mov r0, #0
	add sp, sp, #220
	pop {r4, r5, r6, r7, fp, lr}
	bx lr
.L106:
.L107:
	b .L104
.L108:

addr_b1:
	.word b
addr_c1:
	.word c
