                                                                                                                                                                                                                                                                                                                                                   	.arch armv8-a
	.arch_extension crc
	.arm
	.data
	.section .rodata
	.global ascii_0
	.align 4
	.size ascii_0, 4
ascii_0:
	.word 48
	.text
	.global my_getint
	.type my_getint , %function
my_getint:
	push {r4, r5, r6, fp, lr}
	mov fp, sp
	sub sp, sp, #8
.L68:
	ldr r4, =0
	str r4, [fp, #-8]
	b .L71
.L71:
	ldr r4, =1
	cmp r4, #0
	bne .L72
	b .L75
.L72:
	bl getch
	mov r4, r0
	ldr r5, addr_ascii_00
	ldr r6, [r5]
	sub r5, r4, r6
	str r5, [fp, #-4]
	ldr r4, [fp, #-4]
	cmp r4, #0
	movlt r4, #1
	movge r4, #0
	blt .L77
	b .L83
.L73:
	ldr r4, [fp, #-4]
	str r4, [fp, #-8]
	b .L89
.L74:
.L75:
	b .L73
.L76:
.L77:
	b .L71
.L78:
	b .L73
.L79:
	b .L71
.L80:
	ldr r4, [fp, #-4]
	cmp r4, #9
	movgt r4, #1
	movle r4, #0
	bgt .L77
	b .L86
.L81:
.L82:
.L83:
	b .L80
.L84:
.L85:
.L86:
	b .L78
.L87:
	b .L79
.L88:
	b .L79
.L89:
	ldr r4, =1
	cmp r4, #0
	bne .L90
	b .L93
.L90:
	bl getch
	mov r4, r0
	ldr r5, addr_ascii_00
	ldr r6, [r5]
	sub r5, r4, r6
	str r5, [fp, #-4]
	ldr r4, [fp, #-4]
	cmp r4, #0
	movge r4, #1
	movlt r4, #0
	bge .L98
	b .L101
.L91:
	ldr r4, [fp, #-8]
	mov r0, r4
	add sp, sp, #8
	pop {r4, r5, r6, fp, lr}
	bx lr
.L92:
.L93:
	b .L91
.L94:
.L95:
	ldr r4, [fp, #-8]
	ldr r5, =10
	mul r6, r4, r5
	ldr r4, [fp, #-4]
	add r5, r6, r4
	str r5, [fp, #-8]
	b .L97
.L96:
	b .L91
.L97:
	b .L89
.L98:
	ldr r4, [fp, #-4]
	cmp r4, #9
	movle r4, #1
	movgt r4, #0
	ble .L95
	b .L104
.L99:
.L100:
.L101:
	b .L96
.L102:
.L103:
.L104:
	b .L96
.L105:
	b .L97

	.global my_putint
	.type my_putint , %function
my_putint:
	push {r4, r5, r6, r7, r8, fp, lr}
	mov fp, sp
	sub sp, sp, #72
.L106:
	str r0, [fp, #-72]
	ldr r4, =0
	str r4, [fp, #-4]
	b .L110
.L110:
	ldr r4, [fp, #-72]
	cmp r4, #0
	movgt r4, #1
	movle r4, #0
	bgt .L111
	b .L115
.L111:
	ldr r4, [fp, #-72]
	ldr r5, =10
	sdiv r6, r4, r5
	mul r5, r6, r5
	sub r6, r4, r5
	ldr r4, addr_ascii_00
	ldr r5, [r4]
	add r4, r6, r5
	ldr r5, [fp, #-4]
	mov r6, #-68
	mov r7, #4
	mul r8, r5, r7
	add r5, r6, r8
	add r6, fp, r5
	str r4, [r6]
	ldr r4, [fp, #-72]
	ldr r5, =10
	sdiv r6, r4, r5
	str r6, [fp, #-72]
	ldr r4, [fp, #-4]
	add r5, r4, #1
	str r5, [fp, #-4]
	b .L110
.L112:
	b .L116
.L113:
	add sp, sp, #72
	pop {r4, r5, r6, r7, r8, fp, lr}
	bx lr
.L114:
	add sp, sp, #72
	pop {r4, r5, r6, r7, r8, fp, lr}
	bx lr
.L115:
	b .L112
.L116:
	ldr r4, [fp, #-4]
	cmp r4, #0
	movgt r4, #1
	movle r4, #0
	bgt .L117
	b .L121
.L117:
	ldr r4, [fp, #-4]
	sub r5, r4, #1
	str r5, [fp, #-4]
	ldr r4, [fp, #-4]
	mov r5, #-68
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	add r5, fp, r4
	ldr r4, [r5]
	mov r0, r4
	bl putch
	mov r4, r0
	b .L116
.L118:
	add sp, sp, #72
	pop {r4, r5, r6, r7, r8, fp, lr}
	bx lr
.L119:
	add sp, sp, #72
	pop {r4, r5, r6, r7, r8, fp, lr}
	bx lr
.L120:
	add sp, sp, #72
	pop {r4, r5, r6, r7, r8, fp, lr}
	bx lr
.L121:
	b .L118

	.global main
	.type main , %function
main:
	push {r4, r5, fp, lr}
	mov fp, sp
	sub sp, sp, #8
.L123:
	bl my_getint
	mov r4, r0
	str r4, [fp, #-8]
	b .L125
.L125:
	ldr r4, [fp, #-8]
	cmp r4, #0
	movgt r4, #1
	movle r4, #0
	bgt .L126
	b .L130
.L126:
	bl my_getint
	mov r4, r0
	str r4, [fp, #-4]
	ldr r4, [fp, #-4]
	mov r0, r4
	bl my_putint
	mov r0, #10
	bl putch
	mov r4, r0
	ldr r4, [fp, #-8]
	sub r5, r4, #1
	str r5, [fp, #-8]
	b .L125
.L127:
	mov r0, #0
	add sp, sp, #8
	pop {r4, r5, fp, lr}
	bx lr
.L128:
.L129:
.L130:
	b .L127

addr_ascii_00:
	.word ascii_0
