                                 	    	    	    		                                                         	               	                   	            	            		  																	  				            				    							                          	                                                                 		                                	                                                             	.arch armv8-a
	.arch_extension crc
	.arm
	.data
	.comm V, 160000, 4
	.text
	.global KnapSack
	.type KnapSack , %function
KnapSack:
	push {r4, r5, r6, r7, r8, r9, fp, lr}
	mov fp, sp
	sub sp, sp, #36
.L110:
	str r0, [fp, #-36]
	str r1, [fp, #-32]
	str r2, [fp, #-28]
	str r3, [fp, #-24]
	ldr r3, [fp, #32]
	str r3, [fp, #-20]
	ldr r4, =1
	str r4, [fp, #-16]
	b .L118
.L118:
	ldr r4, [fp, #-16]
	ldr r5, [fp, #-36]
	cmp r4, r5
	movle r4, #1
	movgt r4, #0
	ble .L119
	b .L123
.L119:
	ldr r4, =0
	str r4, [fp, #-12]
	b .L124
.L120:
	ldr r4, [fp, #-20]
	str r4, [fp, #-12]
	ldr r4, [fp, #-36]
	str r4, [fp, #-16]
	b .L159
.L123:
	b .L120
.L124:
	ldr r4, [fp, #-12]
	ldr r5, [fp, #-20]
	add r6, r5, #1
	cmp r4, r6
	movlt r4, #1
	movge r4, #0
	blt .L125
	b .L129
.L125:
	ldr r4, [fp, #-12]
	ldr r5, [fp, #-32]
	ldr r6, [fp, #-16]
	mov r7, #4
	mul r8, r6, r7
	add r6, r5, r8
	ldr r5, [r6]
	cmp r4, r5
	movlt r4, #1
	movge r4, #0
	blt .L130
	b .L137
.L126:
	ldr r4, [fp, #-16]
	add r5, r4, #1
	str r5, [fp, #-16]
	b .L118
.L129:
	b .L126
.L130:
	ldr r4, [fp, #-16]
	sub r5, r4, #1
	ldr r4, addr_V0
	ldr r6, =800
	mul r7, r5, r6
	add r5, r4, r7
	mov r4, r5
	ldr r5, [fp, #-12]
	mov r6, #4
	mul r7, r5, r6
	add r5, r4, r7
	ldr r4, [r5]
	ldr r5, [fp, #-16]
	ldr r6, addr_V0
	ldr r7, =800
	mul r8, r5, r7
	add r5, r6, r8
	mov r6, r5
	ldr r5, [fp, #-12]
	mov r7, #4
	mul r8, r5, r7
	add r5, r6, r8
	str r4, [r5]
	b .L132
.L131:
	ldr r4, [fp, #-16]
	sub r5, r4, #1
	ldr r4, addr_V0
	ldr r6, =800
	mul r7, r5, r6
	add r5, r4, r7
	mov r4, r5
	ldr r5, [fp, #-12]
	mov r6, #4
	mul r7, r5, r6
	add r5, r4, r7
	ldr r4, [r5]
	str r4, [fp, #-8]
	ldr r4, [fp, #-16]
	sub r5, r4, #1
	ldr r4, addr_V0
	ldr r6, =800
	mul r7, r5, r6
	add r5, r4, r7
	mov r4, r5
	ldr r5, [fp, #-12]
	ldr r6, [fp, #-32]
	ldr r7, [fp, #-16]
	mov r8, #4
	mul r9, r7, r8
	add r7, r6, r9
	ldr r6, [r7]
	sub r7, r5, r6
	mov r5, #4
	mul r6, r7, r5
	add r5, r4, r6
	ldr r4, [r5]
	ldr r5, [fp, #-28]
	ldr r6, [fp, #-16]
	mov r7, #4
	mul r8, r6, r7
	add r6, r5, r8
	ldr r5, [r6]
	add r6, r4, r5
	str r6, [fp, #-4]
	ldr r4, [fp, #-8]
	ldr r5, [fp, #-4]
	cmp r4, r5
	movgt r4, #1
	movle r4, #0
	bgt .L151
	b .L156
.L132:
	ldr r4, [fp, #-12]
	add r5, r4, #1
	str r5, [fp, #-12]
	b .L124
.L137:
	b .L131
.L151:
	ldr r4, [fp, #-8]
	ldr r5, [fp, #-16]
	ldr r6, addr_V0
	ldr r7, =800
	mul r8, r5, r7
	add r5, r6, r8
	mov r6, r5
	ldr r5, [fp, #-12]
	mov r7, #4
	mul r8, r5, r7
	add r5, r6, r8
	str r4, [r5]
	b .L153
.L152:
	ldr r4, [fp, #-4]
	ldr r5, [fp, #-16]
	ldr r6, addr_V0
	ldr r7, =800
	mul r8, r5, r7
	add r5, r6, r8
	mov r6, r5
	ldr r5, [fp, #-12]
	mov r8, #4
	mul r7, r5, r8
	add r5, r6, r7
	str r4, [r5]
	b .L153
.L153:
	b .L132
.L156:
	b .L152
.L159:
	ldr r4, [fp, #-16]
	cmp r4, #1
	movge r4, #1
	movlt r4, #0
	bge .L160
	b .L164
.L160:
	ldr r4, [fp, #-16]
	ldr r5, addr_V0
	ldr r6, =800
	mul r7, r4, r6
	add r4, r5, r7
	mov r5, r4
	ldr r4, [fp, #-12]
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	ldr r5, [r4]
	ldr r4, [fp, #-16]
	sub r6, r4, #1
	ldr r4, addr_V0
	ldr r8, =800
	mul r7, r6, r8
	add r6, r4, r7
	mov r4, r6
	ldr r6, [fp, #-12]
	mov r7, #4
	mul r8, r6, r7
	add r6, r4, r8
	ldr r4, [r6]
	cmp r5, r4
	movgt r4, #1
	movle r4, #0
	bgt .L165
	b .L174
	b .F0
.LTORG
addr_V0:
	.word V
.F0:
.L161:
	ldr r4, [fp, #-36]
	ldr r5, addr_V1
	ldr r6, =800
	mul r7, r4, r6
	add r4, r5, r7
	mov r5, r4
	ldr r4, [fp, #-20]
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	ldr r5, [r4]
	mov r0, r5
	add sp, sp, #36
	pop {r4, r5, r6, r7, r8, r9, fp, lr}
	bx lr
.L164:
	b .L161
.L165:
	ldr r4, [fp, #-24]
	ldr r5, [fp, #-16]
	mov r6, #4
	mul r7, r5, r6
	add r5, r4, r7
	ldr r4, =1
	str r4, [r5]
	ldr r4, [fp, #-12]
	ldr r5, [fp, #-32]
	ldr r6, [fp, #-16]
	mov r7, #4
	mul r8, r6, r7
	add r6, r5, r8
	ldr r5, [r6]
	sub r6, r4, r5
	str r6, [fp, #-12]
	b .L167
.L166:
	ldr r4, [fp, #-24]
	ldr r5, [fp, #-16]
	mov r6, #4
	mul r7, r5, r6
	add r5, r4, r7
	ldr r4, =0
	str r4, [r5]
	b .L167
.L167:
	ldr r4, [fp, #-16]
	sub r5, r4, #1
	str r5, [fp, #-16]
	b .L159
.L174:
	b .L166

	.global main
	.type main , %function
main:
	push {r4, r5, r6, r7, r8, r9, r10, fp, lr}
	mov fp, sp
	sub sp, sp, #84
.L181:
	mov r4, #0
	mov r5, #-80
	mov r7, #4
	mul r6, r4, r7
	add r4, r5, r6
	add r5, fp, r4
	ldr r4, =0
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =2
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =2
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =6
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =5
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =4
	str r5, [r4]
	mov r4, #0
	mov r5, #-56
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	add r5, fp, r4
	ldr r4, =0
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =6
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =3
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =5
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =4
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =6
	str r5, [r4]
	ldr r4, =5
	str r4, [fp, #-8]
	ldr r4, =10
	str r4, [fp, #-4]
	ldr r4, [fp, #-8]
	mov r5, #0
	mov r6, #-80
	mov r7, #4
	mul r8, r5, r7
	add r5, r6, r8
	add r6, fp, r5
	mov r5, #0
	mov r7, #-56
	mov r8, #4
	mul r9, r5, r8
	add r5, r7, r9
	add r7, fp, r5
	mov r5, #0
	mov r8, #-32
	mov r9, #4
	mul r10, r5, r9
	add r5, r8, r10
	add r8, fp, r5
	ldr r5, [fp, #-4]
	mov r0, r4
	mov r1, r6
	mov r2, r7
	mov r3, r8
	push {r5}
	bl KnapSack
	add sp, sp, #4
	mov r4, r0
	str r4, [fp, #-84]
	ldr r4, [fp, #-84]
	mov r0, r4
	bl putint
	mov r4, r0
	mov r0, #0
	add sp, sp, #84
	pop {r4, r5, r6, r7, r8, r9, r10, fp, lr}
	bx lr

addr_V1:
	.word V
