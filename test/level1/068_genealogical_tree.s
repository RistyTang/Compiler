     	 	 	  																																																															  													 				 			 	 	 																												 	.arch armv8-a
	.arch_extension crc
	.arm
	.data
	.comm map, 400, 4
	.comm indegree, 40, 4
	.comm queue, 40, 4
	.text
	.global topo
	.type topo , %function
topo:
	push {r4, r5, r6, r7, r8, fp, lr}
	mov fp, sp
	sub sp, sp, #20
.L90:
	str r0, [fp, #-20]
	ldr r4, =0
	str r4, [fp, #-16]
	ldr r4, =0
	str r4, [fp, #-12]
	ldr r4, =1
	str r4, [fp, #-8]
	ldr r4, =1
	str r4, [fp, #-4]
	b .L96
.L96:
	ldr r4, [fp, #-8]
	ldr r5, [fp, #-20]
	cmp r4, r5
	movle r4, #1
	movgt r4, #0
	ble .L97
	b .L101
.L97:
	ldr r4, =1
	str r4, [fp, #-4]
	b .L102
.L98:
	ldr r4, =0
	str r4, [fp, #-8]
	b .L129
.L99:
	add sp, sp, #20
	pop {r4, r5, r6, r7, r8, fp, lr}
	bx lr
.L100:
	add sp, sp, #20
	pop {r4, r5, r6, r7, r8, fp, lr}
	bx lr
.L101:
	b .L98
.L102:
	ldr r4, [fp, #-4]
	ldr r5, [fp, #-20]
	cmp r4, r5
	movle r4, #1
	movgt r4, #0
	ble .L103
	b .L107
.L103:
	ldr r4, [fp, #-4]
	ldr r5, addr_indegree0
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	mov r5, r4
	ldr r4, [r5]
	cmp r4, #0
	beq .L108
	b .L113
.L104:
	ldr r4, [fp, #-16]
	ldr r5, [fp, #-12]
	ldr r6, addr_queue0
	mov r8, #4
	mul r7, r5, r8
	add r5, r6, r7
	mov r6, r5
	str r4, [r6]
	ldr r4, [fp, #-12]
	add r5, r4, #1
	str r5, [fp, #-12]
	ldr r4, =0
	sub r5, r4, #1
	ldr r4, [fp, #-16]
	ldr r6, addr_indegree0
	mov r8, #4
	mul r7, r4, r8
	add r4, r6, r7
	mov r6, r4
	str r5, [r6]
	ldr r4, =1
	str r4, [fp, #-4]
	b .L115
.L105:
	add sp, sp, #20
	pop {r4, r5, r6, r7, r8, fp, lr}
	bx lr
.L106:
	add sp, sp, #20
	pop {r4, r5, r6, r7, r8, fp, lr}
	bx lr
.L107:
	b .L104
.L108:
	ldr r4, [fp, #-4]
	str r4, [fp, #-16]
	b .L104
.L109:
	ldr r4, [fp, #-4]
	add r5, r4, #1
	str r5, [fp, #-4]
	b .L102
.L111:
	add sp, sp, #20
	pop {r4, r5, r6, r7, r8, fp, lr}
	bx lr
.L112:
	add sp, sp, #20
	pop {r4, r5, r6, r7, r8, fp, lr}
	bx lr
.L113:
	b .L109
.L114:
	b .L109
.L115:
	ldr r4, [fp, #-4]
	ldr r5, [fp, #-20]
	cmp r4, r5
	movle r4, #1
	movgt r4, #0
	ble .L116
	b .L120
.L116:
	ldr r4, [fp, #-16]
	ldr r5, addr_map0
	mov r6, #40
	mul r7, r4, r6
	add r4, r5, r7
	mov r5, r4
	ldr r4, [fp, #-4]
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	ldr r5, [r4]
	cmp r5, #0
	bne .L121
	b .L126
.L117:
	ldr r4, [fp, #-8]
	add r5, r4, #1
	str r5, [fp, #-8]
	b .L96
.L118:
	add sp, sp, #20
	pop {r4, r5, r6, r7, r8, fp, lr}
	bx lr
.L119:
	add sp, sp, #20
	pop {r4, r5, r6, r7, r8, fp, lr}
	bx lr
.L120:
	b .L117
.L121:
	ldr r4, [fp, #-4]
	ldr r5, addr_indegree0
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	mov r5, r4
	ldr r4, [r5]
	sub r5, r4, #1
	ldr r4, [fp, #-4]
	ldr r6, addr_indegree0
	mov r7, #4
	mul r8, r4, r7
	add r4, r6, r8
	mov r6, r4
	str r5, [r6]
	b .L122
.L122:
	ldr r4, [fp, #-4]
	add r5, r4, #1
	str r5, [fp, #-4]
	b .L115
.L125:
	add sp, sp, #20
	pop {r4, r5, r6, r7, r8, fp, lr}
	bx lr
.L126:
	b .L122
.L127:
	add sp, sp, #20
	pop {r4, r5, r6, r7, r8, fp, lr}
	bx lr
.L129:
	ldr r4, [fp, #-8]
	ldr r5, [fp, #-20]
	cmp r4, r5
	movlt r4, #1
	movge r4, #0
	blt .L130
	b .L134
.L130:
	ldr r4, [fp, #-8]
	ldr r5, addr_queue0
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
	ldr r4, [fp, #-8]
	add r5, r4, #1
	str r5, [fp, #-8]
	b .L129
	b .F0
.LTORG
addr_map0:
	.word map
addr_indegree0:
	.word indegree
addr_queue0:
	.word queue
.F0:
.L131:
	add sp, sp, #20
	pop {r4, r5, r6, r7, r8, fp, lr}
	bx lr
.L132:
	add sp, sp, #20
	pop {r4, r5, r6, r7, r8, fp, lr}
	bx lr
.L133:
	add sp, sp, #20
	pop {r4, r5, r6, r7, r8, fp, lr}
	bx lr
.L134:
	b .L131

	.global main
	.type main , %function
main:
	push {r4, r5, r6, r7, r8, fp, lr}
	mov fp, sp
	sub sp, sp, #12
.L136:
	ldr r4, =1
	str r4, [fp, #-4]
	ldr r4, =5
	str r4, [fp, #-12]
	b .L140
.L140:
	ldr r4, [fp, #-4]
	ldr r5, [fp, #-12]
	cmp r4, r5
	movle r4, #1
	movgt r4, #0
	ble .L141
	b .L145
.L141:
	bl getint
	mov r4, r0
	str r4, [fp, #-8]
	b .L146
.L142:
	ldr r4, [fp, #-12]
	mov r0, r4
	bl topo
	mov r0, #0
	add sp, sp, #12
	pop {r4, r5, r6, r7, r8, fp, lr}
	bx lr
.L145:
	b .L142
.L146:
	ldr r4, [fp, #-8]
	cmp r4, #0
	bne .L147
	b .L151
.L147:
	ldr r4, [fp, #-4]
	ldr r5, addr_map1
	mov r6, #40
	mul r7, r4, r6
	add r4, r5, r7
	mov r5, r4
	ldr r4, [fp, #-8]
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	ldr r5, =1
	str r5, [r4]
	ldr r4, [fp, #-8]
	ldr r5, addr_indegree1
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	mov r5, r4
	ldr r4, [r5]
	add r5, r4, #1
	ldr r4, [fp, #-8]
	ldr r6, addr_indegree1
	mov r7, #4
	mul r8, r4, r7
	add r4, r6, r8
	mov r6, r4
	str r5, [r6]
	bl getint
	mov r4, r0
	str r4, [fp, #-8]
	b .L146
.L148:
	ldr r4, [fp, #-4]
	add r5, r4, #1
	str r5, [fp, #-4]
	b .L140
.L151:
	b .L148

addr_map1:
	.word map
addr_indegree1:
	.word indegree
addr_queue1:
	.word queue
