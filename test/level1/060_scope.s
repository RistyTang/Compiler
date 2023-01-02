     	   	   	    		    		 				   	   	   	    		   			    		    		   						 	.arch armv8-a
	.arch_extension crc
	.arm
	.data
	.global a
	.align 4
	.size a, 4
a:
	.word 7
	.text
	.global func
	.type func , %function
func:
	push {r4, r5, fp, lr}
	mov fp, sp
	sub sp, sp, #8
.L26:
	ldr r4, addr_a0
	ldr r5, [r4]
	str r5, [fp, #-8]
	ldr r4, =1
	str r4, [fp, #-4]
	ldr r4, [fp, #-4]
	ldr r5, [fp, #-8]
	cmp r4, r5
	beq .L29
	b .L34
.L29:
	ldr r4, [fp, #-4]
	add r5, r4, #1
	str r5, [fp, #-4]
	mov r0, #1
	add sp, sp, #8
	pop {r4, r5, fp, lr}
	bx lr
	b .L31
.L30:
	mov r0, #0
	add sp, sp, #8
	pop {r4, r5, fp, lr}
	bx lr
	b .L31
.L31:
	mov r0, #0
	add sp, sp, #8
	pop {r4, r5, fp, lr}
	bx lr
.L34:
	b .L30

	.global main
	.type main , %function
main:
	push {r4, r5, fp, lr}
	mov fp, sp
	sub sp, sp, #8
.L35:
	ldr r4, =0
	str r4, [fp, #-8]
	ldr r4, =0
	str r4, [fp, #-4]
	b .L38
.L38:
	ldr r4, [fp, #-4]
	cmp r4, #100
	movlt r4, #1
	movge r4, #0
	blt .L39
	b .L43
.L39:
	bl func
	mov r4, r0
	cmp r4, #1
	beq .L44
	b .L48
.L40:
	ldr r4, [fp, #-8]
	cmp r4, #100
	movlt r4, #1
	movge r4, #0
	blt .L49
	b .L54
.L43:
	b .L40
.L44:
	ldr r4, [fp, #-8]
	add r5, r4, #1
	str r5, [fp, #-8]
	b .L45
.L45:
	ldr r4, [fp, #-4]
	add r5, r4, #1
	str r5, [fp, #-4]
	b .L38
.L48:
	b .L45
.L49:
	mov r0, #1
	bl putint
	mov r4, r0
	b .L51
.L50:
	mov r0, #0
	bl putint
	mov r4, r0
	b .L51
.L51:
	mov r0, #0
	add sp, sp, #8
	pop {r4, r5, fp, lr}
	bx lr
.L54:
	b .L50

addr_a0:
	.word a
