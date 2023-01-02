          	.arch armv8-a
	.arch_extension crc
	.arm
	.data
	.section .rodata
	.global a
	.align 4
	.size a, 4
a:
	.word 10
	.text
	.global main
	.type main , %function
main:
	push {r4, r5, fp, lr}
	mov fp, sp
	sub sp, sp, #0
.L2:
	ldr r4, addr_a0
	ldr r5, [r4]
	mov r0, r5
	add sp, sp, #0
	pop {r4, r5, fp, lr}
	bx lr

addr_a0:
	.word a
