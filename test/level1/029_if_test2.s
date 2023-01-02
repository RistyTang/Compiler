                                                                                                   	.arch armv8-a
	.arch_extension crc
	.arm
	.text
	.global ifElseIf
	.type ifElseIf , %function
ifElseIf:
	push {r4, r5, r6, fp, lr}
	mov fp, sp
	sub sp, sp, #8
.L31:
	ldr r4, =5
	str r4, [fp, #-8]
	ldr r4, =10
	str r4, [fp, #-4]
	ldr r4, [fp, #-8]
	cmp r4, #6
	beq .L34
	b .L40
.L34:
	ldr r4, [fp, #-8]
	mov r0, r4
	add sp, sp, #8
	pop {r4, r5, r6, fp, lr}
	bx lr
	b .L36
.L35:
	ldr r4, [fp, #-4]
	cmp r4, #10
	beq .L47
	b .L50
.L36:
	ldr r4, [fp, #-8]
	mov r0, r4
	add sp, sp, #8
	pop {r4, r5, r6, fp, lr}
	bx lr
.L37:
	ldr r4, [fp, #-4]
	cmp r4, #11
	beq .L34
	b .L43
.L40:
	b .L37
.L43:
	b .L35
.L44:
	ldr r4, =25
	str r4, [fp, #-8]
	b .L46
.L45:
	ldr r4, [fp, #-4]
	cmp r4, #10
	beq .L57
	b .L60
.L46:
	b .L36
.L47:
	ldr r4, [fp, #-8]
	cmp r4, #1
	beq .L44
	b .L53
.L50:
	b .L45
.L53:
	b .L45
.L54:
	ldr r4, [fp, #-8]
	add r5, r4, #15
	str r5, [fp, #-8]
	b .L56
.L55:
	ldr r4, [fp, #-8]
	ldr r5, =0
	sub r6, r5, r4
	str r6, [fp, #-8]
	b .L56
.L56:
	b .L46
.L57:
	ldr r4, [fp, #-8]
	ldr r5, =0
	sub r6, r5, #5
	cmp r4, r6
	beq .L54
	b .L63
.L60:
	b .L55
.L63:
	b .L55

	.global main
	.type main , %function
main:
	push {r4, fp, lr}
	mov fp, sp
	sub sp, sp, #0
.L64:
	bl ifElseIf
	mov r4, r0
	mov r0, r4
	bl putint
	mov r4, r0
	mov r0, #0
	add sp, sp, #0
	pop {r4, fp, lr}
	bx lr

