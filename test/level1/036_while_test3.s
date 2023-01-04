                                                                                                                                                                                                                                                                                                                                                                                                                                                             	.arch armv8-a
	.arch_extension crc
	.arm
	.data
	.global g
	.align 4
	.size g, 4
g:
	.word 0
	.global h
	.align 4
	.size h, 4
h:
	.word 0
	.global f
	.align 4
	.size f, 4
f:
	.word 0
	.global e
	.align 4
	.size e, 4
e:
	.word 0
	.text
	.global EightWhile
	.type EightWhile , %function
EightWhile:
	push {r4, r5, r6, r7, fp, lr}
	mov fp, sp
	sub sp, sp, #16
.L93:
	ldr r4, =5
	str r4, [fp, #-16]
	ldr r4, =6
	str r4, [fp, #-12]
	ldr r4, =7
	str r4, [fp, #-8]
	ldr r4, =10
	str r4, [fp, #-4]
	b .L98
.L98:
	ldr r4, [fp, #-16]
	cmp r4, #20
	movlt r4, #1
	movge r4, #0
	blt .L99
	b .L103
.L99:
	ldr r4, [fp, #-16]
	add r5, r4, #3
	str r5, [fp, #-16]
	b .L104
.L100:
	ldr r4, [fp, #-16]
	ldr r5, [fp, #-12]
	ldr r6, [fp, #-4]
	add r7, r5, r6
	add r5, r4, r7
	ldr r4, [fp, #-8]
	add r6, r5, r4
	ldr r4, addr_e0
	ldr r5, [r4]
	ldr r4, [fp, #-4]
	add r7, r5, r4
	ldr r4, addr_g0
	ldr r5, [r4]
	sub r4, r7, r5
	ldr r5, addr_h0
	ldr r7, [r5]
	add r5, r4, r7
	sub r4, r6, r5
	mov r0, r4
	add sp, sp, #16
	pop {r4, r5, r6, r7, fp, lr}
	bx lr
.L101:
.L102:
.L103:
	b .L100
.L104:
	ldr r4, [fp, #-12]
	cmp r4, #10
	movlt r4, #1
	movge r4, #0
	blt .L105
	b .L109
.L105:
	ldr r4, [fp, #-12]
	add r5, r4, #1
	str r5, [fp, #-12]
	b .L110
.L106:
	ldr r4, [fp, #-12]
	sub r5, r4, #2
	str r5, [fp, #-12]
	b .L98
.L107:
.L108:
.L109:
	b .L106
.L110:
	ldr r4, [fp, #-8]
	cmp r4, #7
	beq .L111
	b .L115
.L111:
	ldr r4, [fp, #-8]
	sub r5, r4, #1
	str r5, [fp, #-8]
	b .L116
.L112:
	ldr r4, [fp, #-8]
	add r5, r4, #1
	str r5, [fp, #-8]
	b .L104
.L113:
.L114:
.L115:
	b .L112
.L116:
	ldr r4, [fp, #-4]
	cmp r4, #20
	movlt r4, #1
	movge r4, #0
	blt .L117
	b .L121
.L117:
	ldr r4, [fp, #-4]
	add r5, r4, #3
	str r5, [fp, #-4]
	b .L122
.L118:
	ldr r4, [fp, #-4]
	sub r5, r4, #1
	str r5, [fp, #-4]
	b .L110
.L119:
.L120:
.L121:
	b .L118
.L122:
	ldr r4, addr_e0
	ldr r5, [r4]
	cmp r5, #1
	movgt r4, #1
	movle r4, #0
	bgt .L123
	b .L127
.L123:
	ldr r4, addr_e0
	ldr r5, [r4]
	sub r4, r5, #1
	ldr r5, addr_e0
	str r4, [r5]
	b .L128
.L124:
	ldr r4, addr_e0
	ldr r5, [r4]
	add r4, r5, #1
	ldr r5, addr_e0
	str r4, [r5]
	b .L116
.L125:
.L126:
.L127:
	b .L124
.L128:
	ldr r4, addr_f0
	ldr r5, [r4]
	cmp r5, #2
	movgt r4, #1
	movle r4, #0
	bgt .L129
	b .L133
.L129:
	ldr r4, addr_f0
	ldr r5, [r4]
	sub r4, r5, #2
	ldr r5, addr_f0
	str r4, [r5]
	b .L134
.L130:
	ldr r4, addr_f0
	ldr r5, [r4]
	add r4, r5, #1
	ldr r5, addr_f0
	str r4, [r5]
	b .L122
.L131:
.L132:
.L133:
	b .L130
.L134:
	ldr r4, addr_g0
	ldr r5, [r4]
	cmp r5, #3
	movlt r4, #1
	movge r4, #0
	blt .L135
	b .L139
.L135:
	ldr r4, addr_g0
	ldr r5, [r4]
	add r4, r5, #10
	ldr r5, addr_g0
	str r4, [r5]
	b .L140
.L136:
	ldr r4, addr_g0
	ldr r5, [r4]
	sub r4, r5, #8
	ldr r5, addr_g0
	str r4, [r5]
	b .L128
.L137:
.L138:
.L139:
	b .L136
.L140:
	ldr r4, addr_h0
	ldr r5, [r4]
	cmp r5, #10
	movlt r4, #1
	movge r4, #0
	blt .L141
	b .L145
.L141:
	ldr r4, addr_h0
	ldr r5, [r4]
	add r4, r5, #8
	ldr r5, addr_h0
	str r4, [r5]
	b .L140
.L142:
	ldr r4, addr_h0
	ldr r5, [r4]
	sub r4, r5, #1
	ldr r5, addr_h0
	str r4, [r5]
	b .L134
	b .F0
.LTORG
addr_g0:
	.word g
addr_h0:
	.word h
addr_f0:
	.word f
addr_e0:
	.word e
.F0:
.L143:
.L144:
.L145:
	b .L142

	.global main
	.type main , %function
main:
	push {r4, r5, fp, lr}
	mov fp, sp
	sub sp, sp, #0
.L146:
	ldr r4, =1
	ldr r5, addr_g1
	str r4, [r5]
	ldr r4, =2
	ldr r5, addr_h1
	str r4, [r5]
	ldr r4, =4
	ldr r5, addr_e1
	str r4, [r5]
	ldr r4, =6
	ldr r5, addr_f1
	str r4, [r5]
	bl EightWhile
	mov r4, r0
	mov r0, r4
	add sp, sp, #0
	pop {r4, r5, fp, lr}
	bx lr

addr_g1:
	.word g
addr_h1:
	.word h
addr_f1:
	.word f
addr_e1:
	.word e
