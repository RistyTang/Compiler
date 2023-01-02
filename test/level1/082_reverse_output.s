   	 	    						 							  	 		 	.arch armv8-a
	.arch_extension crc
	.arm
	.text
	.global reverse
	.type reverse , %function
reverse:
	push {r4, r5, fp, lr}
	mov fp, sp
	sub sp, sp, #8
.L17:
	str r0, [fp, #-8]
	ldr r4, [fp, #-8]
	cmp r4, #1
	movle r4, #1
	movgt r4, #0
	ble .L20
	b .L25
.L20:
	bl getint
	mov r4, r0
	str r4, [fp, #-4]
	ldr r4, [fp, #-4]
	mov r0, r4
	bl putint
	mov r4, r0
	b .L22
.L21:
	bl getint
	mov r4, r0
	str r4, [fp, #-4]
	ldr r4, [fp, #-8]
	sub r5, r4, #1
	mov r0, r5
	bl reverse
	ldr r4, [fp, #-4]
	mov r0, r4
	bl putint
	mov r4, r0
	b .L22
.L22:
	add sp, sp, #8
	pop {r4, r5, fp, lr}
	bx lr
.L23:
	add sp, sp, #8
	pop {r4, r5, fp, lr}
	bx lr
.L24:
	add sp, sp, #8
	pop {r4, r5, fp, lr}
	bx lr
.L25:
	b .L21

	.global main
	.type main , %function
main:
	push {r4, fp, lr}
	mov fp, sp
	sub sp, sp, #4
.L26:
	ldr r4, =200
	str r4, [fp, #-4]
	ldr r4, [fp, #-4]
	mov r0, r4
	bl reverse
	mov r0, #0
	add sp, sp, #4
	pop {r4, fp, lr}
	bx lr

