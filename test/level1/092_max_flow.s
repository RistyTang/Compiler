                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              	.arch armv8-a
	.arch_extension crc
	.arm
	.data
	.section .rodata
	.global INF
	.align 4
	.size INF, 4
INF:
	.word 1879048192
	.comm size, 40, 4
	.comm to, 400, 4
	.comm cap, 400, 4
	.comm rev, 400, 4
	.comm used, 40, 4
	.text
	.global my_memset
	.type my_memset , %function
my_memset:
	push {r4, r5, r6, r7, r8, fp, lr}
	mov fp, sp
	sub sp, sp, #16
.L196:
	str r0, [fp, #-16]
	str r1, [fp, #-12]
	str r2, [fp, #-8]
	ldr r4, =0
	str r4, [fp, #-4]
	b .L201
.L201:
	ldr r4, [fp, #-4]
	ldr r5, [fp, #-8]
	cmp r4, r5
	movlt r4, #1
	movge r4, #0
	blt .L202
	b .L206
.L202:
	ldr r4, [fp, #-12]
	ldr r5, [fp, #-16]
	ldr r6, [fp, #-4]
	mov r7, #4
	mul r8, r6, r7
	add r6, r5, r8
	str r4, [r6]
	ldr r4, [fp, #-4]
	add r5, r4, #1
	str r5, [fp, #-4]
	b .L201
.L203:
	add sp, sp, #16
	pop {r4, r5, r6, r7, r8, fp, lr}
	bx lr
.L204:
	add sp, sp, #16
	pop {r4, r5, r6, r7, r8, fp, lr}
	bx lr
.L205:
	add sp, sp, #16
	pop {r4, r5, r6, r7, r8, fp, lr}
	bx lr
.L206:
	b .L203

	.global add_node
	.type add_node , %function
add_node:
	push {r4, r5, r6, r7, r8, r9, fp, lr}
	mov fp, sp
	sub sp, sp, #12
.L208:
	str r0, [fp, #-12]
	str r1, [fp, #-8]
	str r2, [fp, #-4]
	ldr r4, [fp, #-8]
	ldr r5, [fp, #-12]
	ldr r6, addr_to0
	mov r7, #40
	mul r8, r5, r7
	add r5, r6, r8
	mov r6, r5
	ldr r5, [fp, #-12]
	ldr r7, addr_size0
	mov r8, #4
	mul r9, r5, r8
	add r5, r7, r9
	mov r7, r5
	ldr r5, [r7]
	mov r7, #4
	mul r8, r5, r7
	add r5, r6, r8
	str r4, [r5]
	ldr r4, [fp, #-4]
	ldr r5, [fp, #-12]
	ldr r6, addr_cap0
	mov r7, #40
	mul r8, r5, r7
	add r5, r6, r8
	mov r6, r5
	ldr r5, [fp, #-12]
	ldr r7, addr_size0
	mov r8, #4
	mul r9, r5, r8
	add r5, r7, r9
	mov r7, r5
	ldr r5, [r7]
	mov r7, #4
	mul r8, r5, r7
	add r5, r6, r8
	str r4, [r5]
	ldr r4, [fp, #-8]
	ldr r5, addr_size0
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	mov r5, r4
	ldr r4, [r5]
	ldr r5, [fp, #-12]
	ldr r6, addr_rev0
	mov r7, #40
	mul r8, r5, r7
	add r5, r6, r8
	mov r6, r5
	ldr r5, [fp, #-12]
	ldr r7, addr_size0
	mov r8, #4
	mul r9, r5, r8
	add r5, r7, r9
	mov r7, r5
	ldr r5, [r7]
	mov r8, #4
	mul r7, r5, r8
	add r5, r6, r7
	str r4, [r5]
	ldr r4, [fp, #-12]
	ldr r5, [fp, #-8]
	ldr r6, addr_to0
	mov r7, #40
	mul r8, r5, r7
	add r5, r6, r8
	mov r6, r5
	ldr r5, [fp, #-8]
	ldr r7, addr_size0
	mov r8, #4
	mul r9, r5, r8
	add r5, r7, r9
	mov r7, r5
	ldr r5, [r7]
	mov r8, #4
	mul r7, r5, r8
	add r5, r6, r7
	str r4, [r5]
	ldr r4, [fp, #-8]
	ldr r5, addr_cap0
	mov r6, #40
	mul r7, r4, r6
	add r4, r5, r7
	mov r5, r4
	ldr r4, [fp, #-8]
	ldr r6, addr_size0
	mov r7, #4
	mul r8, r4, r7
	add r4, r6, r8
	mov r6, r4
	ldr r4, [r6]
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	ldr r5, =0
	str r5, [r4]
	ldr r4, [fp, #-12]
	ldr r5, addr_size0
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	mov r5, r4
	ldr r4, [r5]
	ldr r5, [fp, #-8]
	ldr r6, addr_rev0
	mov r7, #40
	mul r8, r5, r7
	add r5, r6, r8
	mov r6, r5
	ldr r5, [fp, #-8]
	ldr r7, addr_size0
	mov r9, #4
	mul r8, r5, r9
	add r5, r7, r8
	mov r7, r5
	ldr r5, [r7]
	mov r7, #4
	mul r8, r5, r7
	add r5, r6, r8
	str r4, [r5]
	ldr r4, [fp, #-12]
	ldr r5, addr_size0
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	mov r5, r4
	ldr r4, [r5]
	add r5, r4, #1
	ldr r4, [fp, #-12]
	ldr r6, addr_size0
	mov r7, #4
	mul r8, r4, r7
	add r4, r6, r8
	mov r6, r4
	str r5, [r6]
	ldr r4, [fp, #-8]
	ldr r5, addr_size0
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	mov r5, r4
	ldr r4, [r5]
	add r5, r4, #1
	ldr r4, [fp, #-8]
	ldr r6, addr_size0
	mov r7, #4
	mul r8, r4, r7
	add r4, r6, r8
	mov r6, r4
	str r5, [r6]
	add sp, sp, #12
	pop {r4, r5, r6, r7, r8, r9, fp, lr}
	bx lr

	.global dfs
	.type dfs , %function
dfs:
	push {r4, r5, r6, r7, r8, r9, fp, lr}
	mov fp, sp
	sub sp, sp, #24
.L228:
	str r0, [fp, #-24]
	str r1, [fp, #-20]
	str r2, [fp, #-16]
	ldr r4, [fp, #-24]
	ldr r5, [fp, #-20]
	cmp r4, r5
	beq .L232
	b .L236
.L232:
	ldr r4, [fp, #-16]
	mov r0, r4
	add sp, sp, #24
	pop {r4, r5, r6, r7, r8, r9, fp, lr}
	bx lr
	b .L233
.L233:
	ldr r4, [fp, #-24]
	ldr r5, addr_used0
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	mov r5, r4
	ldr r4, =1
	str r4, [r5]
	ldr r4, =0
	str r4, [fp, #-12]
	b .L238
.L236:
	b .L233
.L238:
	ldr r4, [fp, #-12]
	ldr r5, [fp, #-24]
	ldr r6, addr_size0
	mov r7, #4
	mul r8, r5, r7
	add r5, r6, r8
	mov r6, r5
	ldr r5, [r6]
	cmp r4, r5
	movlt r4, #1
	movge r4, #0
	blt .L239
	b .L244
.L239:
	ldr r4, [fp, #-24]
	ldr r5, addr_to0
	mov r6, #40
	mul r7, r4, r6
	add r4, r5, r7
	mov r5, r4
	ldr r4, [fp, #-12]
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	ldr r5, [r4]
	ldr r4, addr_used0
	mov r6, #4
	mul r7, r5, r6
	add r5, r4, r7
	mov r4, r5
	ldr r5, [r4]
	cmp r5, #0
	bne .L245
	b .L251
.L240:
	mov r0, #0
	add sp, sp, #24
	pop {r4, r5, r6, r7, r8, r9, fp, lr}
	bx lr
.L244:
	b .L240
.L245:
	ldr r4, [fp, #-12]
	add r5, r4, #1
	str r5, [fp, #-12]
	b .L238
.L246:
	ldr r4, [fp, #-24]
	ldr r5, addr_cap0
	mov r6, #40
	mul r7, r4, r6
	add r4, r5, r7
	mov r5, r4
	ldr r4, [fp, #-12]
	mov r7, #4
	mul r6, r4, r7
	add r4, r5, r6
	ldr r5, [r4]
	cmp r5, #0
	movle r4, #1
	movgt r4, #0
	ble .L254
	b .L260
.L251:
	b .L246
.L253:
	b .L246
.L254:
	ldr r4, [fp, #-12]
	add r5, r4, #1
	str r5, [fp, #-12]
	b .L238
.L255:
	ldr r4, [fp, #-16]
	ldr r5, [fp, #-24]
	ldr r6, addr_cap0
	mov r7, #40
	mul r8, r5, r7
	add r5, r6, r8
	mov r6, r5
	ldr r5, [fp, #-12]
	mov r7, #4
	mul r8, r5, r7
	add r5, r6, r8
	ldr r6, [r5]
	cmp r4, r6
	movlt r4, #1
	movge r4, #0
	blt .L263
	b .L270
.L260:
	b .L255
.L261:
	b .L255
.L263:
	ldr r4, [fp, #-16]
	str r4, [fp, #-8]
	b .L265
.L264:
	ldr r4, [fp, #-24]
	ldr r5, addr_cap0
	mov r7, #40
	mul r6, r4, r7
	add r4, r5, r6
	mov r5, r4
	ldr r4, [fp, #-12]
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	ldr r5, [r4]
	str r5, [fp, #-8]
	b .L265
.L265:
	ldr r4, [fp, #-24]
	ldr r5, addr_to0
	mov r6, #40
	mul r7, r4, r6
	add r4, r5, r7
	mov r5, r4
	ldr r4, [fp, #-12]
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	ldr r5, [r4]
	ldr r4, [fp, #-20]
	ldr r6, [fp, #-8]
	mov r0, r5
	mov r1, r4
	mov r2, r6
	bl dfs
	mov r4, r0
	str r4, [fp, #-4]
	ldr r4, [fp, #-4]
	cmp r4, #0
	movgt r4, #1
	movle r4, #0
	bgt .L276
	b .L280
.L270:
	b .L264
.L276:
	ldr r4, [fp, #-24]
	ldr r5, addr_cap0
	mov r6, #40
	mul r7, r4, r6
	add r4, r5, r7
	mov r5, r4
	ldr r4, [fp, #-12]
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	ldr r5, [r4]
	ldr r4, [fp, #-4]
	sub r6, r5, r4
	ldr r4, [fp, #-24]
	ldr r5, addr_cap0
	mov r7, #40
	mul r8, r4, r7
	add r4, r5, r8
	mov r5, r4
	ldr r4, [fp, #-12]
	mov r7, #4
	mul r8, r4, r7
	add r4, r5, r8
	str r6, [r4]
	ldr r4, [fp, #-24]
	ldr r5, addr_to0
	mov r6, #40
	mul r7, r4, r6
	add r4, r5, r7
	mov r5, r4
	ldr r4, [fp, #-12]
	mov r7, #4
	mul r6, r4, r7
	add r4, r5, r6
	ldr r5, [r4]
	ldr r4, addr_cap0
	mov r6, #40
	mul r7, r5, r6
	add r5, r4, r7
	mov r4, r5
	ldr r5, [fp, #-24]
	ldr r6, addr_rev0
	mov r8, #40
	mul r7, r5, r8
	add r5, r6, r7
	mov r6, r5
	ldr r5, [fp, #-12]
	mov r7, #4
	mul r8, r5, r7
	add r5, r6, r8
	ldr r6, [r5]
	mov r5, #4
	mul r7, r6, r5
	add r5, r4, r7
	ldr r4, [r5]
	ldr r5, [fp, #-4]
	add r6, r4, r5
	ldr r4, [fp, #-24]
	ldr r5, addr_to0
	mov r7, #40
	mul r8, r4, r7
	add r4, r5, r8
	mov r5, r4
	ldr r4, [fp, #-12]
	mov r8, #4
	mul r7, r4, r8
	add r4, r5, r7
	ldr r5, [r4]
	ldr r4, addr_cap0
	mov r7, #40
	mul r8, r5, r7
	add r5, r4, r8
	mov r4, r5
	ldr r5, [fp, #-24]
	ldr r7, addr_rev0
	mov r9, #40
	mul r8, r5, r9
	add r5, r7, r8
	mov r7, r5
	ldr r5, [fp, #-12]
	mov r8, #4
	mul r9, r5, r8
	add r5, r7, r9
	ldr r7, [r5]
	mov r5, #4
	mul r8, r7, r5
	add r5, r4, r8
	str r6, [r5]
	ldr r4, [fp, #-4]
	mov r0, r4
	add sp, sp, #24
	pop {r4, r5, r6, r7, r8, r9, fp, lr}
	bx lr
	b .L277
	b .F0
.LTORG
addr_INF0:
	.word INF
addr_size0:
	.word size
addr_to0:
	.word to
addr_cap0:
	.word cap
addr_rev0:
	.word rev
addr_used0:
	.word used
.F0:
.L277:
	ldr r4, [fp, #-12]
	add r5, r4, #1
	str r5, [fp, #-12]
	b .L238
.L280:
	b .L277

	.global max_flow
	.type max_flow , %function
max_flow:
	push {r4, r5, r6, r7, fp, lr}
	mov fp, sp
	sub sp, sp, #16
.L295:
	str r0, [fp, #-16]
	str r1, [fp, #-12]
	ldr r4, =0
	str r4, [fp, #-8]
	b .L299
.L299:
	ldr r4, =1
	cmp r4, #0
	bne .L300
	b .L303
.L300:
	mov r4, #0
	ldr r5, addr_used1
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	mov r5, r4
	mov r0, r5
	mov r1, #0
	mov r2, #10
	bl my_memset
	ldr r4, [fp, #-16]
	ldr r5, [fp, #-12]
	ldr r6, addr_INF1
	ldr r7, [r6]
	mov r0, r4
	mov r1, r5
	mov r2, r7
	bl dfs
	mov r4, r0
	str r4, [fp, #-4]
	ldr r4, [fp, #-4]
	cmp r4, #0
	beq .L306
	b .L310
.L301:
	mov r0, #0
	add sp, sp, #16
	pop {r4, r5, r6, r7, fp, lr}
	bx lr
.L303:
	b .L301
.L306:
	ldr r4, [fp, #-8]
	mov r0, r4
	add sp, sp, #16
	pop {r4, r5, r6, r7, fp, lr}
	bx lr
	b .L307
.L307:
	ldr r4, [fp, #-8]
	ldr r5, [fp, #-4]
	add r6, r4, r5
	str r6, [fp, #-8]
	b .L299
.L310:
	b .L307

	.global main
	.type main , %function
main:
	push {r4, r5, r6, r7, fp, lr}
	mov fp, sp
	sub sp, sp, #20
.L311:
	bl getint
	mov r4, r0
	str r4, [fp, #-20]
	bl getint
	mov r4, r0
	str r4, [fp, #-16]
	mov r4, #0
	ldr r5, addr_size1
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	mov r5, r4
	mov r0, r5
	mov r1, #0
	mov r2, #10
	bl my_memset
	b .L314
.L314:
	ldr r4, [fp, #-16]
	cmp r4, #0
	movgt r4, #1
	movle r4, #0
	bgt .L315
	b .L319
.L315:
	bl getint
	mov r4, r0
	str r4, [fp, #-12]
	bl getint
	mov r4, r0
	str r4, [fp, #-8]
	bl getint
	mov r4, r0
	str r4, [fp, #-4]
	ldr r4, [fp, #-12]
	ldr r5, [fp, #-8]
	ldr r6, [fp, #-4]
	mov r0, r4
	mov r1, r5
	mov r2, r6
	bl add_node
	ldr r4, [fp, #-16]
	sub r5, r4, #1
	str r5, [fp, #-16]
	b .L314
.L316:
	ldr r4, [fp, #-20]
	mov r0, #1
	mov r1, r4
	bl max_flow
	mov r4, r0
	mov r0, r4
	bl putint
	mov r4, r0
	mov r0, #10
	bl putch
	mov r4, r0
	mov r0, #0
	add sp, sp, #20
	pop {r4, r5, r6, r7, fp, lr}
	bx lr
.L319:
	b .L316

addr_INF1:
	.word INF
addr_size1:
	.word size
addr_to1:
	.word to
addr_cap1:
	.word cap
addr_rev1:
	.word rev
addr_used1:
	.word used
