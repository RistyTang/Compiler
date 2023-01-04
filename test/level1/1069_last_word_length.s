                                                                                                                                                                                         	.arch armv8-a
	.arch_extension crc
	.arm
	.text
	.global lengthOfLastWord
	.type lengthOfLastWord , %function
lengthOfLastWord:
	push {r4, r5, r6, r7, fp, lr}
	mov fp, sp
	sub sp, sp, #16
.L68:
	str r0, [fp, #-16]
	str r1, [fp, #-12]
	ldr r4, [fp, #-12]
	cmp r4, #0
	beq .L71
	b .L75
.L71:
	mov r0, #0
	add sp, sp, #16
	pop {r4, r5, r6, r7, fp, lr}
	bx lr
	b .L72
.L72:
	ldr r4, [fp, #-12]
	sub r5, r4, #1
	str r5, [fp, #-8]
	b .L77
.L73:
.L74:
.L75:
	b .L72
.L77:
	ldr r4, [fp, #-8]
	ldr r5, =0
	sub r6, r5, #1
	cmp r4, r6
	movgt r4, #1
	movle r4, #0
	bgt .L80
	b .L83
.L78:
	ldr r4, [fp, #-8]
	sub r5, r4, #1
	str r5, [fp, #-8]
	b .L77
.L79:
	ldr r4, [fp, #-8]
	ldr r5, =0
	sub r6, r5, #1
	cmp r4, r6
	beq .L89
	b .L93
.L80:
	ldr r4, [fp, #-16]
	ldr r5, [fp, #-8]
	mov r6, #4
	mul r7, r5, r6
	add r5, r4, r7
	ldr r4, [r5]
	cmp r4, #0
	beq .L78
	b .L88
.L81:
.L82:
.L83:
	b .L79
.L86:
.L87:
.L88:
	b .L79
.L89:
	mov r0, #0
	add sp, sp, #16
	pop {r4, r5, r6, r7, fp, lr}
	bx lr
	b .L90
.L90:
	ldr r4, [fp, #-8]
	str r4, [fp, #-4]
	b .L95
.L91:
.L92:
.L93:
	b .L90
.L95:
	ldr r4, [fp, #-4]
	ldr r5, =0
	sub r6, r5, #1
	cmp r4, r6
	movgt r4, #1
	movle r4, #0
	bgt .L96
	b .L100
.L96:
	ldr r4, [fp, #-16]
	ldr r5, [fp, #-4]
	mov r6, #4
	mul r7, r5, r6
	add r5, r4, r7
	ldr r4, [r5]
	cmp r4, #0
	beq .L101
	b .L107
.L97:
	ldr r4, [fp, #-8]
	ldr r5, [fp, #-4]
	sub r6, r4, r5
	mov r0, r6
	add sp, sp, #16
	pop {r4, r5, r6, r7, fp, lr}
	bx lr
.L98:
.L99:
.L100:
	b .L97
.L101:
	ldr r4, [fp, #-12]
	ldr r5, [fp, #-4]
	sub r6, r4, r5
	sub r4, r6, #1
	ldr r5, [fp, #-12]
	sub r6, r5, #1
	ldr r5, [fp, #-8]
	sub r7, r6, r5
	sub r5, r4, r7
	mov r0, r5
	add sp, sp, #16
	pop {r4, r5, r6, r7, fp, lr}
	bx lr
	b .L102
.L102:
	ldr r4, [fp, #-4]
	sub r5, r4, #1
	str r5, [fp, #-4]
	b .L95
.L105:
.L106:
.L107:
	b .L102

	.global main
	.type main , %function
main:
	push {r4, r5, r6, r7, r8, fp, lr}
	mov fp, sp
	sub sp, sp, #44
.L108:
	ldr r4, =0
	sub r5, r4, #4
	mov r4, #0
	mov r6, #-40
	mov r8, #4
	mul r7, r4, r8
	add r4, r6, r7
	add r6, fp, r4
	str r5, [r6]
	mov r4, #1
	mov r5, #-40
	mov r7, #4
	mul r6, r4, r7
	add r4, r5, r6
	add r5, fp, r4
	ldr r4, =3
	str r4, [r5]
	mov r4, #2
	mov r5, #-40
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	add r5, fp, r4
	ldr r4, =9
	str r4, [r5]
	ldr r4, =0
	sub r5, r4, #2
	mov r4, #3
	mov r6, #-40
	mov r7, #4
	mul r8, r4, r7
	add r4, r6, r8
	add r6, fp, r4
	str r5, [r6]
	mov r4, #4
	mov r5, #-40
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	add r5, fp, r4
	ldr r4, =0
	str r4, [r5]
	mov r4, #5
	mov r5, #-40
	mov r7, #4
	mul r6, r4, r7
	add r4, r5, r6
	add r5, fp, r4
	ldr r4, =1
	str r4, [r5]
	ldr r4, =0
	sub r5, r4, #6
	mov r4, #6
	mov r6, #-40
	mov r8, #4
	mul r7, r4, r8
	add r4, r6, r7
	add r6, fp, r4
	str r5, [r6]
	mov r4, #7
	mov r5, #-40
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	add r5, fp, r4
	ldr r4, =5
	str r4, [r5]
	mov r4, #8
	mov r5, #-40
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	add r5, fp, r4
	ldr r4, =7
	str r4, [r5]
	mov r4, #9
	mov r5, #-40
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	add r5, fp, r4
	ldr r4, =8
	str r4, [r5]
	ldr r4, =10
	str r4, [fp, #-44]
	mov r4, #0
	mov r5, #-40
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	add r5, fp, r4
	ldr r4, [fp, #-44]
	mov r0, r5
	mov r1, r4
	bl lengthOfLastWord
	mov r4, r0
	str r4, [fp, #-44]
	ldr r4, [fp, #-44]
	mov r0, r4
	add sp, sp, #44
	pop {r4, r5, r6, r7, r8, fp, lr}
	bx lr

