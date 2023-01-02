                                                                                                                                                                                                                                                                                                                                                                                                    	.arch armv8-a
	.arch_extension crc
	.arm
	.data
	.global sum
	.align 4
	.size sum, 4
sum:
	.word 0
	.global n
	.align 4
	.size n, 4
n:
	.word 0
	.comm ans, 200, 4
	.comm row, 200, 4
	.comm line1, 200, 4
	.comm line2, 400, 4
	.text
	.global printans
	.type printans , %function
printans:
	push {r4, r5, r6, r7, fp, lr}
	mov fp, sp
	sub sp, sp, #4
.L93:
	ldr r4, addr_sum0
	ldr r5, [r4]
	add r4, r5, #1
	ldr r5, addr_sum0
	str r4, [r5]
	ldr r4, =1
	str r4, [fp, #-4]
	b .L95
.L95:
	ldr r4, [fp, #-4]
	ldr r5, addr_n0
	ldr r6, [r5]
	cmp r4, r6
	movle r4, #1
	movgt r4, #0
	ble .L96
	b .L100
.L96:
	ldr r4, [fp, #-4]
	ldr r5, addr_ans0
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	mov r5, r4
	ldr r4, [r5]
	mov r0, r4
	bl putint
	mov r4, r0
	ldr r4, [fp, #-4]
	ldr r5, addr_n0
	ldr r6, [r5]
	cmp r4, r6
	beq .L102
	b .L107
.L97:
	add sp, sp, #4
	pop {r4, r5, r6, r7, fp, lr}
	bx lr
.L98:
	add sp, sp, #4
	pop {r4, r5, r6, r7, fp, lr}
	bx lr
.L99:
	add sp, sp, #4
	pop {r4, r5, r6, r7, fp, lr}
	bx lr
.L100:
	b .L97
.L102:
	mov r0, #10
	bl putch
	mov r4, r0
	add sp, sp, #4
	pop {r4, r5, r6, r7, fp, lr}
	bx lr
	b .L104
.L103:
	mov r0, #32
	bl putch
	mov r4, r0
	b .L104
.L104:
	ldr r4, [fp, #-4]
	add r5, r4, #1
	str r5, [fp, #-4]
	b .L95
.L105:
	add sp, sp, #4
	pop {r4, r5, r6, r7, fp, lr}
	bx lr
.L106:
	add sp, sp, #4
	pop {r4, r5, r6, r7, fp, lr}
	bx lr
.L107:
	b .L103

	.global f
	.type f , %function
f:
	push {r4, r5, r6, r7, r8, fp, lr}
	mov fp, sp
	sub sp, sp, #8
.L108:
	str r0, [fp, #-8]
	ldr r4, =1
	str r4, [fp, #-4]
	b .L111
.L111:
	ldr r4, [fp, #-4]
	ldr r5, addr_n0
	ldr r6, [r5]
	cmp r4, r6
	movle r4, #1
	movgt r4, #0
	ble .L112
	b .L116
.L112:
	ldr r4, [fp, #-4]
	ldr r5, addr_row0
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	mov r5, r4
	ldr r4, [r5]
	cmp r4, #1
	bne .L120
	b .L124
.L113:
	add sp, sp, #8
	pop {r4, r5, r6, r7, r8, fp, lr}
	bx lr
.L114:
	add sp, sp, #8
	pop {r4, r5, r6, r7, r8, fp, lr}
	bx lr
.L115:
	add sp, sp, #8
	pop {r4, r5, r6, r7, r8, fp, lr}
	bx lr
.L116:
	b .L113
.L117:
	ldr r4, [fp, #-4]
	ldr r5, [fp, #-8]
	ldr r6, addr_ans0
	mov r7, #4
	mul r8, r5, r7
	add r5, r6, r8
	mov r6, r5
	str r4, [r6]
	ldr r4, [fp, #-8]
	ldr r5, addr_n0
	ldr r6, [r5]
	cmp r4, r6
	beq .L134
	b .L138
.L118:
	ldr r4, [fp, #-4]
	add r5, r4, #1
	str r5, [fp, #-4]
	b .L111
.L119:
	ldr r4, addr_n0
	ldr r5, [r4]
	ldr r4, [fp, #-8]
	add r6, r5, r4
	ldr r4, [fp, #-4]
	sub r5, r6, r4
	ldr r4, addr_line20
	mov r6, #4
	mul r7, r5, r6
	add r5, r4, r7
	mov r4, r5
	ldr r5, [r4]
	cmp r5, #0
	moveq r4, #1
	movne r4, #0
	cmp r4, #0
	bne .L117
	b .L132
.L120:
	ldr r4, [fp, #-8]
	ldr r5, [fp, #-4]
	add r6, r4, r5
	ldr r4, addr_line10
	mov r5, #4
	mul r7, r6, r5
	add r5, r4, r7
	mov r4, r5
	ldr r5, [r4]
	cmp r5, #0
	beq .L119
	b .L128
.L122:
	add sp, sp, #8
	pop {r4, r5, r6, r7, r8, fp, lr}
	bx lr
.L123:
	add sp, sp, #8
	pop {r4, r5, r6, r7, r8, fp, lr}
	bx lr
.L124:
	b .L118
.L126:
	add sp, sp, #8
	pop {r4, r5, r6, r7, r8, fp, lr}
	bx lr
.L127:
	add sp, sp, #8
	pop {r4, r5, r6, r7, r8, fp, lr}
	bx lr
.L128:
	b .L118
.L131:
	add sp, sp, #8
	pop {r4, r5, r6, r7, r8, fp, lr}
	bx lr
.L132:
	b .L118
.L133:
	add sp, sp, #8
	pop {r4, r5, r6, r7, r8, fp, lr}
	bx lr
.L134:
	bl printans
	b .L135
.L135:
	ldr r4, [fp, #-4]
	ldr r5, addr_row0
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	mov r5, r4
	ldr r4, =1
	str r4, [r5]
	ldr r4, [fp, #-8]
	ldr r5, [fp, #-4]
	add r6, r4, r5
	ldr r4, addr_line10
	mov r5, #4
	mul r7, r6, r5
	add r5, r4, r7
	mov r4, r5
	ldr r5, =1
	str r5, [r4]
	ldr r4, addr_n0
	ldr r5, [r4]
	ldr r4, [fp, #-8]
	add r6, r5, r4
	ldr r4, [fp, #-4]
	sub r5, r6, r4
	ldr r4, addr_line20
	mov r6, #4
	mul r7, r5, r6
	add r5, r4, r7
	mov r4, r5
	ldr r5, =1
	str r5, [r4]
	ldr r4, [fp, #-8]
	add r5, r4, #1
	mov r0, r5
	bl f
	ldr r4, [fp, #-4]
	ldr r5, addr_row0
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	mov r5, r4
	ldr r4, =0
	str r4, [r5]
	ldr r4, [fp, #-8]
	ldr r5, [fp, #-4]
	add r6, r4, r5
	ldr r4, addr_line10
	mov r5, #4
	mul r7, r6, r5
	add r5, r4, r7
	mov r4, r5
	ldr r5, =0
	str r5, [r4]
	ldr r4, addr_n0
	ldr r5, [r4]
	ldr r4, [fp, #-8]
	add r6, r5, r4
	ldr r4, [fp, #-4]
	sub r5, r6, r4
	ldr r4, addr_line20
	mov r6, #4
	mul r7, r5, r6
	add r5, r4, r7
	mov r4, r5
	ldr r5, =0
	str r5, [r4]
	b .L118
	b .F0
.LTORG
addr_ans0:
	.word ans
addr_sum0:
	.word sum
addr_n0:
	.word n
addr_row0:
	.word row
addr_line10:
	.word line1
addr_line20:
	.word line2
.F0:
.L136:
	add sp, sp, #8
	pop {r4, r5, r6, r7, r8, fp, lr}
	bx lr
.L137:
	add sp, sp, #8
	pop {r4, r5, r6, r7, r8, fp, lr}
	bx lr
.L138:
	b .L135

	.global main
	.type main , %function
main:
	push {r4, r5, fp, lr}
	mov fp, sp
	sub sp, sp, #4
.L139:
	bl getint
	mov r4, r0
	str r4, [fp, #-4]
	b .L141
.L141:
	ldr r4, [fp, #-4]
	cmp r4, #0
	movgt r4, #1
	movle r4, #0
	bgt .L142
	b .L146
.L142:
	bl getint
	mov r4, r0
	ldr r5, addr_n1
	str r4, [r5]
	mov r0, #1
	bl f
	ldr r4, [fp, #-4]
	sub r5, r4, #1
	str r5, [fp, #-4]
	b .L141
.L143:
	ldr r4, addr_sum1
	ldr r5, [r4]
	mov r0, r5
	add sp, sp, #4
	pop {r4, r5, fp, lr}
	bx lr
.L146:
	b .L143

addr_ans1:
	.word ans
addr_sum1:
	.word sum
addr_n1:
	.word n
addr_row1:
	.word row
addr_line11:
	.word line1
addr_line21:
	.word line2
