                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      	.arch armv8-a
	.arch_extension crc
	.arm
	.data
	.global n
	.align 4
	.size n, 4
n:
	.word 0
	.global m
	.align 4
	.size m, 4
m:
	.word 0
	.global v1
	.align 4
	.size v1, 4
v1:
	.word 0
	.global v2
	.align 4
	.size v2, 4
v2:
	.word 0
	.global w
	.align 4
	.size w, 4
w:
	.word 0
	.section .rodata
	.global INF
	.align 4
	.size INF, 4
INF:
	.word 65535
	.comm e, 1024, 4
	.comm book, 64, 4
	.comm dis, 64, 4
	.text
	.global Dijkstra
	.type Dijkstra , %function
Dijkstra:
	push {r4, r5, r6, r7, r8, r9, fp, lr}
	mov fp, sp
	sub sp, sp, #24
.L143:
	ldr r4, =1
	str r4, [fp, #-24]
	b .L146
.L146:
	ldr r4, [fp, #-24]
	ldr r5, addr_n0
	ldr r6, [r5]
	cmp r4, r6
	movle r4, #1
	movgt r4, #0
	ble .L147
	b .L151
.L147:
	mov r4, #1
	ldr r5, addr_e0
	mov r6, #64
	mul r7, r4, r6
	add r4, r5, r7
	mov r5, r4
	ldr r4, [fp, #-24]
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	ldr r5, [r4]
	ldr r4, [fp, #-24]
	ldr r6, addr_dis0
	mov r7, #4
	mul r8, r4, r7
	add r4, r6, r8
	mov r6, r4
	str r5, [r6]
	ldr r4, [fp, #-24]
	ldr r5, addr_book0
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	mov r5, r4
	ldr r4, =0
	str r4, [r5]
	ldr r4, [fp, #-24]
	add r5, r4, #1
	str r5, [fp, #-24]
	b .L146
.L148:
	mov r4, #1
	ldr r5, addr_book0
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	mov r5, r4
	ldr r4, =1
	str r4, [r5]
	ldr r4, =1
	str r4, [fp, #-24]
	b .L154
.L149:
	add sp, sp, #24
	pop {r4, r5, r6, r7, r8, r9, fp, lr}
	bx lr
.L150:
	add sp, sp, #24
	pop {r4, r5, r6, r7, r8, r9, fp, lr}
	bx lr
.L151:
	b .L148
.L154:
	ldr r4, [fp, #-24]
	ldr r5, addr_n0
	ldr r6, [r5]
	sub r5, r6, #1
	cmp r4, r5
	movle r4, #1
	movgt r4, #0
	ble .L155
	b .L159
.L155:
	ldr r4, addr_INF0
	ldr r5, [r4]
	str r5, [fp, #-16]
	ldr r4, =0
	str r4, [fp, #-12]
	ldr r4, =1
	str r4, [fp, #-8]
	b .L163
.L156:
	add sp, sp, #24
	pop {r4, r5, r6, r7, r8, r9, fp, lr}
	bx lr
.L157:
	add sp, sp, #24
	pop {r4, r5, r6, r7, r8, r9, fp, lr}
	bx lr
.L158:
	add sp, sp, #24
	pop {r4, r5, r6, r7, r8, r9, fp, lr}
	bx lr
.L159:
	b .L156
.L163:
	ldr r4, [fp, #-8]
	ldr r5, addr_n0
	ldr r6, [r5]
	cmp r4, r6
	movle r4, #1
	movgt r4, #0
	ble .L164
	b .L168
.L164:
	ldr r4, [fp, #-16]
	ldr r5, [fp, #-8]
	ldr r6, addr_dis0
	mov r7, #4
	mul r8, r5, r7
	add r5, r6, r8
	mov r6, r5
	ldr r5, [r6]
	cmp r4, r5
	movgt r4, #1
	movle r4, #0
	bgt .L171
	b .L175
.L165:
	ldr r4, [fp, #-12]
	ldr r5, addr_book0
	mov r7, #4
	mul r6, r4, r7
	add r4, r5, r6
	mov r5, r4
	ldr r4, =1
	str r4, [r5]
	ldr r4, =1
	str r4, [fp, #-4]
	b .L182
.L166:
	add sp, sp, #24
	pop {r4, r5, r6, r7, r8, r9, fp, lr}
	bx lr
.L167:
	add sp, sp, #24
	pop {r4, r5, r6, r7, r8, r9, fp, lr}
	bx lr
.L168:
	b .L165
.L169:
	ldr r4, [fp, #-8]
	ldr r5, addr_dis0
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	mov r5, r4
	ldr r4, [r5]
	str r4, [fp, #-16]
	ldr r4, [fp, #-8]
	str r4, [fp, #-12]
	b .L170
.L170:
	ldr r4, [fp, #-8]
	add r5, r4, #1
	str r5, [fp, #-8]
	b .L163
.L171:
	ldr r4, [fp, #-8]
	ldr r5, addr_book0
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	mov r5, r4
	ldr r4, [r5]
	cmp r4, #0
	beq .L169
	b .L179
.L173:
	add sp, sp, #24
	pop {r4, r5, r6, r7, r8, r9, fp, lr}
	bx lr
.L174:
	add sp, sp, #24
	pop {r4, r5, r6, r7, r8, r9, fp, lr}
	bx lr
.L175:
	b .L170
.L177:
	add sp, sp, #24
	pop {r4, r5, r6, r7, r8, r9, fp, lr}
	bx lr
.L178:
	add sp, sp, #24
	pop {r4, r5, r6, r7, r8, r9, fp, lr}
	bx lr
.L179:
	b .L170
.L182:
	ldr r4, [fp, #-4]
	ldr r5, addr_n0
	ldr r6, [r5]
	cmp r4, r6
	movle r4, #1
	movgt r4, #0
	ble .L183
	b .L187
	b .F0
.LTORG
addr_INF0:
	.word INF
addr_e0:
	.word e
addr_book0:
	.word book
addr_dis0:
	.word dis
addr_n0:
	.word n
addr_m0:
	.word m
addr_v10:
	.word v1
addr_v20:
	.word v2
addr_w0:
	.word w
.F0:
.L183:
	ldr r4, [fp, #-12]
	ldr r5, addr_e1
	mov r6, #64
	mul r7, r4, r6
	add r4, r5, r7
	mov r5, r4
	ldr r4, [fp, #-4]
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	ldr r5, [r4]
	ldr r4, addr_INF1
	ldr r6, [r4]
	cmp r5, r6
	movlt r4, #1
	movge r4, #0
	blt .L188
	b .L194
.L184:
	ldr r4, [fp, #-24]
	add r5, r4, #1
	str r5, [fp, #-24]
	b .L154
.L185:
	add sp, sp, #24
	pop {r4, r5, r6, r7, r8, r9, fp, lr}
	bx lr
.L186:
	add sp, sp, #24
	pop {r4, r5, r6, r7, r8, r9, fp, lr}
	bx lr
.L187:
	b .L184
.L188:
	ldr r4, [fp, #-4]
	ldr r5, addr_dis1
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	mov r5, r4
	ldr r4, [r5]
	ldr r5, [fp, #-12]
	ldr r6, addr_dis1
	mov r7, #4
	mul r8, r5, r7
	add r5, r6, r8
	mov r6, r5
	ldr r5, [r6]
	ldr r6, [fp, #-12]
	ldr r7, addr_e1
	mov r8, #64
	mul r9, r6, r8
	add r6, r7, r9
	mov r7, r6
	ldr r6, [fp, #-4]
	mov r8, #4
	mul r9, r6, r8
	add r6, r7, r9
	ldr r7, [r6]
	add r6, r5, r7
	cmp r4, r6
	movgt r4, #1
	movle r4, #0
	bgt .L195
	b .L203
.L189:
	ldr r4, [fp, #-4]
	add r5, r4, #1
	str r5, [fp, #-4]
	b .L182
.L192:
	add sp, sp, #24
	pop {r4, r5, r6, r7, r8, r9, fp, lr}
	bx lr
.L193:
	add sp, sp, #24
	pop {r4, r5, r6, r7, r8, r9, fp, lr}
	bx lr
.L194:
	b .L189
.L195:
	ldr r4, [fp, #-12]
	ldr r5, addr_dis1
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	mov r5, r4
	ldr r4, [r5]
	ldr r5, [fp, #-12]
	ldr r6, addr_e1
	mov r7, #64
	mul r8, r5, r7
	add r5, r6, r8
	mov r6, r5
	ldr r5, [fp, #-4]
	mov r8, #4
	mul r7, r5, r8
	add r5, r6, r7
	ldr r6, [r5]
	add r5, r4, r6
	ldr r4, [fp, #-4]
	ldr r6, addr_dis1
	mov r7, #4
	mul r8, r4, r7
	add r4, r6, r8
	mov r6, r4
	str r5, [r6]
	b .L196
.L196:
	b .L189
.L201:
	add sp, sp, #24
	pop {r4, r5, r6, r7, r8, r9, fp, lr}
	bx lr
.L202:
	add sp, sp, #24
	pop {r4, r5, r6, r7, r8, r9, fp, lr}
	bx lr
.L203:
	b .L196

	.global main
	.type main , %function
main:
	push {r4, r5, r6, r7, r8, fp, lr}
	mov fp, sp
	sub sp, sp, #16
.L207:
	bl getint
	mov r4, r0
	ldr r5, addr_n1
	str r4, [r5]
	bl getint
	mov r4, r0
	ldr r5, addr_m1
	str r4, [r5]
	ldr r4, =1
	str r4, [fp, #-16]
	b .L209
.L209:
	ldr r4, [fp, #-16]
	ldr r5, addr_n1
	ldr r6, [r5]
	cmp r4, r6
	movle r4, #1
	movgt r4, #0
	ble .L210
	b .L214
.L210:
	ldr r4, =1
	str r4, [fp, #-12]
	b .L216
.L211:
	ldr r4, =1
	str r4, [fp, #-16]
	b .L230
.L212:
.L213:
.L214:
	b .L211
.L216:
	ldr r4, [fp, #-12]
	ldr r5, addr_n1
	ldr r6, [r5]
	cmp r4, r6
	movle r4, #1
	movgt r4, #0
	ble .L217
	b .L221
.L217:
	ldr r4, [fp, #-16]
	ldr r5, [fp, #-12]
	cmp r4, r5
	beq .L222
	b .L227
.L218:
	ldr r4, [fp, #-16]
	add r5, r4, #1
	str r5, [fp, #-16]
	b .L209
.L219:
.L220:
.L221:
	b .L218
.L222:
	ldr r4, [fp, #-16]
	ldr r5, addr_e1
	mov r7, #64
	mul r6, r4, r7
	add r4, r5, r6
	mov r5, r4
	ldr r4, [fp, #-12]
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	ldr r5, =0
	str r5, [r4]
	b .L224
.L223:
	ldr r4, addr_INF1
	ldr r5, [r4]
	ldr r4, [fp, #-16]
	ldr r6, addr_e1
	mov r7, #64
	mul r8, r4, r7
	add r4, r6, r8
	mov r6, r4
	ldr r4, [fp, #-12]
	mov r8, #4
	mul r7, r4, r8
	add r4, r6, r7
	str r5, [r4]
	b .L224
.L224:
	ldr r4, [fp, #-12]
	add r5, r4, #1
	str r5, [fp, #-12]
	b .L216
.L225:
.L226:
.L227:
	b .L223
.L230:
	ldr r4, [fp, #-16]
	ldr r5, addr_m1
	ldr r6, [r5]
	cmp r4, r6
	movle r4, #1
	movgt r4, #0
	ble .L231
	b .L235
.L231:
	bl getint
	mov r4, r0
	str r4, [fp, #-8]
	bl getint
	mov r4, r0
	str r4, [fp, #-4]
	bl getint
	mov r4, r0
	ldr r5, [fp, #-8]
	ldr r6, addr_e1
	mov r7, #64
	mul r8, r5, r7
	add r5, r6, r8
	mov r6, r5
	ldr r5, [fp, #-4]
	mov r8, #4
	mul r7, r5, r8
	add r5, r6, r7
	str r4, [r5]
	ldr r4, [fp, #-16]
	add r5, r4, #1
	str r5, [fp, #-16]
	b .L230
.L232:
	bl Dijkstra
	ldr r4, =1
	str r4, [fp, #-16]
	b .L239
.L233:
.L234:
.L235:
	b .L232
.L239:
	ldr r4, [fp, #-16]
	ldr r5, addr_n1
	ldr r6, [r5]
	cmp r4, r6
	movle r4, #1
	movgt r4, #0
	ble .L240
	b .L244
.L240:
	ldr r4, [fp, #-16]
	ldr r5, addr_dis1
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	mov r5, r4
	ldr r4, [r5]
	mov r0, r4
	bl putint
	mov r4, r0
	mov r0, #32
	bl putch
	mov r4, r0
	ldr r4, [fp, #-16]
	add r5, r4, #1
	str r5, [fp, #-16]
	b .L239
.L241:
	mov r0, #10
	bl putch
	mov r4, r0
	mov r0, #0
	add sp, sp, #16
	pop {r4, r5, r6, r7, r8, fp, lr}
	bx lr
.L242:
.L243:
.L244:
	b .L241

addr_INF1:
	.word INF
addr_e1:
	.word e
addr_book1:
	.word book
addr_dis1:
	.word dis
addr_n1:
	.word n
addr_m1:
	.word m
addr_v11:
	.word v1
addr_v21:
	.word v2
addr_w1:
	.word w
