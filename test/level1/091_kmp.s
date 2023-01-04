                                                                                                                                                                                                                                                                                                                                                                                                                                                                    	.arch armv8-a
	.arch_extension crc
	.arm
	.text
	.global get_next
	.type get_next , %function
get_next:
	push {r4, r5, r6, r7, r8, fp, lr}
	mov fp, sp
	sub sp, sp, #16
.L101:
	str r0, [fp, #-16]
	str r1, [fp, #-12]
	ldr r4, =0
	sub r5, r4, #1
	ldr r4, [fp, #-12]
	mov r6, #0
	mov r7, #4
	mul r8, r6, r7
	add r6, r4, r8
	str r5, [r6]
	ldr r4, =0
	str r4, [fp, #-8]
	ldr r4, =0
	sub r5, r4, #1
	str r5, [fp, #-4]
	b .L107
.L107:
	ldr r4, [fp, #-16]
	ldr r5, [fp, #-8]
	mov r6, #4
	mul r7, r5, r6
	add r5, r4, r7
	ldr r4, [r5]
	cmp r4, #0
	bne .L108
	b .L113
.L108:
	ldr r4, [fp, #-4]
	ldr r5, =0
	sub r6, r5, #1
	cmp r4, r6
	beq .L115
	b .L121
.L109:
	add sp, sp, #16
	pop {r4, r5, r6, r7, r8, fp, lr}
	bx lr
.L112:
	add sp, sp, #16
	pop {r4, r5, r6, r7, r8, fp, lr}
	bx lr
.L113:
	b .L109
.L114:
	add sp, sp, #16
	pop {r4, r5, r6, r7, r8, fp, lr}
	bx lr
.L115:
	ldr r4, [fp, #-4]
	add r5, r4, #1
	str r5, [fp, #-4]
	ldr r4, [fp, #-8]
	add r5, r4, #1
	str r5, [fp, #-8]
	ldr r4, [fp, #-4]
	ldr r5, [fp, #-12]
	ldr r6, [fp, #-8]
	mov r7, #4
	mul r8, r6, r7
	add r6, r5, r8
	str r4, [r6]
	b .L117
.L116:
	ldr r4, [fp, #-12]
	ldr r5, [fp, #-4]
	mov r6, #4
	mul r7, r5, r6
	add r5, r4, r7
	ldr r4, [r5]
	str r4, [fp, #-4]
	b .L117
.L117:
	b .L107
.L118:
	ldr r4, [fp, #-16]
	ldr r5, [fp, #-8]
	mov r6, #4
	mul r7, r5, r6
	add r5, r4, r7
	ldr r4, [r5]
	ldr r5, [fp, #-16]
	ldr r6, [fp, #-4]
	mov r7, #4
	mul r8, r6, r7
	add r6, r5, r8
	ldr r5, [r6]
	cmp r4, r5
	beq .L115
	b .L128
.L119:
	add sp, sp, #16
	pop {r4, r5, r6, r7, r8, fp, lr}
	bx lr
.L120:
	add sp, sp, #16
	pop {r4, r5, r6, r7, r8, fp, lr}
	bx lr
.L121:
	b .L118
.L126:
	add sp, sp, #16
	pop {r4, r5, r6, r7, r8, fp, lr}
	bx lr
.L127:
	add sp, sp, #16
	pop {r4, r5, r6, r7, r8, fp, lr}
	bx lr
.L128:
	b .L116

	.global KMP
	.type KMP , %function
KMP:
	push {r4, r5, r6, r7, r8, fp, lr}
	mov fp, sp
	ldr r4, =16400
	sub sp, sp, r4
.L132:
	ldr r4, =-16400
	str r0, [fp, r4]
	ldr r4, =-16396
	str r1, [fp, r4]
	ldr r4, =-16400
	ldr r5, [fp, r4]
	mov r4, #0
	ldr r6, =-16392
	mov r7, #4
	mul r8, r4, r7
	add r4, r6, r8
	add r6, fp, r4
	mov r0, r5
	mov r1, r6
	bl get_next
	ldr r4, =0
	str r4, [fp, #-8]
	ldr r4, =0
	str r4, [fp, #-4]
	b .L139
.L139:
	ldr r5, =-16396
	ldr r4, [fp, r5]
	ldr r5, [fp, #-4]
	mov r6, #4
	mul r7, r5, r6
	add r5, r4, r7
	ldr r4, [r5]
	cmp r4, #0
	bne .L140
	b .L145
.L140:
	ldr r4, =-16400
	ldr r5, [fp, r4]
	ldr r4, [fp, #-8]
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	ldr r5, [r4]
	ldr r6, =-16396
	ldr r4, [fp, r6]
	ldr r6, [fp, #-4]
	mov r8, #4
	mul r7, r6, r8
	add r6, r4, r7
	ldr r4, [r6]
	cmp r5, r4
	beq .L147
	b .L156
.L141:
	ldr r4, =0
	sub r5, r4, #1
	mov r0, r5
	ldr r1, =16400
	add sp, sp, r1
	pop {r4, r5, r6, r7, r8, fp, lr}
	bx lr
.L144:
.L145:
	b .L141
.L146:
.L147:
	ldr r4, [fp, #-8]
	add r5, r4, #1
	str r5, [fp, #-8]
	ldr r4, [fp, #-4]
	add r5, r4, #1
	str r5, [fp, #-4]
	ldr r5, =-16400
	ldr r4, [fp, r5]
	ldr r5, [fp, #-8]
	mov r6, #4
	mul r7, r5, r6
	add r5, r4, r7
	ldr r4, [r5]
	cmp r4, #0
	moveq r4, #1
	movne r4, #0
	cmp r4, #0
	bne .L157
	b .L163
.L148:
	ldr r4, [fp, #-8]
	ldr r5, =-16392
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	add r5, fp, r4
	ldr r4, [r5]
	str r4, [fp, #-8]
	ldr r4, [fp, #-8]
	ldr r5, =0
	sub r6, r5, #1
	cmp r4, r6
	beq .L166
	b .L170
.L149:
	b .L139
.L154:
.L155:
.L156:
	b .L148
.L157:
	ldr r4, [fp, #-4]
	mov r0, r4
	ldr r1, =16400
	add sp, sp, r1
	pop {r4, r5, r6, r7, r8, fp, lr}
	bx lr
	b .L158
.L158:
	b .L149
.L162:
.L163:
	b .L158
.L164:
.L166:
	ldr r4, [fp, #-8]
	add r5, r4, #1
	str r5, [fp, #-8]
	ldr r4, [fp, #-4]
	add r5, r4, #1
	str r5, [fp, #-4]
	b .L167
.L167:
	b .L149
.L168:
.L169:
.L170:
	b .L167

	.global read_str
	.type read_str , %function
read_str:
	push {r4, r5, r6, r7, r8, fp, lr}
	mov fp, sp
	sub sp, sp, #8
.L171:
	str r0, [fp, #-8]
	ldr r4, =0
	str r4, [fp, #-4]
	b .L174
.L174:
	ldr r4, =1
	cmp r4, #0
	bne .L175
	b .L178
.L175:
	bl getch
	mov r4, r0
	ldr r5, [fp, #-8]
	ldr r6, [fp, #-4]
	mov r7, #4
	mul r8, r6, r7
	add r6, r5, r8
	str r4, [r6]
	ldr r4, [fp, #-8]
	ldr r5, [fp, #-4]
	mov r6, #4
	mul r7, r5, r6
	add r5, r4, r7
	ldr r4, [r5]
	cmp r4, #10
	beq .L181
	b .L187
.L176:
	ldr r4, [fp, #-8]
	ldr r5, [fp, #-4]
	mov r6, #4
	mul r7, r5, r6
	add r5, r4, r7
	ldr r4, =0
	str r4, [r5]
	ldr r4, [fp, #-4]
	mov r0, r4
	add sp, sp, #8
	pop {r4, r5, r6, r7, r8, fp, lr}
	bx lr
.L177:
.L178:
	b .L176
.L179:
.L181:
	b .L176
.L182:
	ldr r4, [fp, #-4]
	add r5, r4, #1
	str r5, [fp, #-4]
	b .L174
.L185:
.L186:
.L187:
	b .L182
.L188:
	b .L182

	.global main
	.type main , %function
main:
	push {r4, r5, r6, r7, r8, fp, lr}
	mov fp, sp
	ldr r4, =32768
	sub sp, sp, r4
.L190:
	mov r4, #0
	ldr r5, =-32768
	mov r7, #4
	mul r6, r4, r7
	add r4, r5, r6
	add r5, fp, r4
	mov r0, r5
	bl read_str
	mov r4, r0
	mov r4, #0
	ldr r5, =-16384
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	add r5, fp, r4
	mov r0, r5
	bl read_str
	mov r4, r0
	mov r4, #0
	ldr r5, =-32768
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	add r5, fp, r4
	mov r4, #0
	ldr r6, =-16384
	mov r7, #4
	mul r8, r4, r7
	add r4, r6, r8
	add r6, fp, r4
	mov r0, r5
	mov r1, r6
	bl KMP
	mov r4, r0
	mov r0, r4
	bl putint
	mov r4, r0
	mov r0, #10
	bl putch
	mov r4, r0
	mov r0, #0
	ldr r1, =32768
	add sp, sp, r1
	pop {r4, r5, r6, r7, r8, fp, lr}
	bx lr

