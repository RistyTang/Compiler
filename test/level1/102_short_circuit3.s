                                                                                                                                                                                                                                                                                                                       	.arch armv8-a
	.arch_extension crc
	.arm
	.data
	.global a
	.align 4
	.size a, 4
a:
	.word 0
	.global b
	.align 4
	.size b, 4
b:
	.word 0
	.global d
	.align 4
	.size d, 4
d:
	.word 0
	.text
	.global set_a
	.type set_a , %function
set_a:
	push {r4, r5, fp, lr}
	mov fp, sp
	sub sp, sp, #4
.L147:
	str r0, [fp, #-4]
	ldr r4, [fp, #-4]
	ldr r5, addr_a0
	str r4, [r5]
	ldr r4, addr_a0
	ldr r5, [r4]
	mov r0, r5
	add sp, sp, #4
	pop {r4, r5, fp, lr}
	bx lr

	.global set_b
	.type set_b , %function
set_b:
	push {r4, r5, fp, lr}
	mov fp, sp
	sub sp, sp, #4
.L149:
	str r0, [fp, #-4]
	ldr r4, [fp, #-4]
	ldr r5, addr_b0
	str r4, [r5]
	ldr r4, addr_b0
	ldr r5, [r4]
	mov r0, r5
	add sp, sp, #4
	pop {r4, r5, fp, lr}
	bx lr

	.global set_d
	.type set_d , %function
set_d:
	push {r4, r5, fp, lr}
	mov fp, sp
	sub sp, sp, #4
.L151:
	str r0, [fp, #-4]
	ldr r4, [fp, #-4]
	ldr r5, addr_d0
	str r4, [r5]
	ldr r4, addr_d0
	ldr r5, [r4]
	mov r0, r5
	add sp, sp, #4
	pop {r4, r5, fp, lr}
	bx lr

	.global main
	.type main , %function
main:
	push {r4, r5, r6, r7, fp, lr}
	mov fp, sp
	sub sp, sp, #24
.L153:
	ldr r4, =2
	ldr r5, addr_a0
	str r4, [r5]
	ldr r4, =3
	ldr r5, addr_b0
	str r4, [r5]
	mov r0, #0
	bl set_a
	mov r4, r0
	cmp r4, #0
	bne .L156
	b .L158
.L154:
	b .L155
.L155:
	ldr r4, addr_a0
	ldr r5, [r4]
	mov r0, r5
	bl putint
	mov r4, r0
	mov r0, #32
	bl putch
	mov r4, r0
	ldr r4, addr_b0
	ldr r5, [r4]
	mov r0, r5
	bl putint
	mov r4, r0
	mov r0, #32
	bl putch
	mov r4, r0
	ldr r4, =2
	ldr r5, addr_a0
	str r4, [r5]
	ldr r4, =3
	ldr r5, addr_b0
	str r4, [r5]
	mov r0, #0
	bl set_a
	mov r4, r0
	cmp r4, #0
	bne .L165
	b .L167
.L156:
	mov r0, #1
	bl set_b
	mov r4, r0
	cmp r4, #0
	bne .L154
	b .L161
.L157:
.L158:
	b .L155
.L159:
.L160:
.L161:
	b .L155
.L162:
.L163:
	b .L164
.L164:
	ldr r4, addr_a0
	ldr r5, [r4]
	mov r0, r5
	bl putint
	mov r4, r0
	mov r0, #32
	bl putch
	mov r4, r0
	ldr r4, addr_b0
	ldr r5, [r4]
	mov r0, r5
	bl putint
	mov r4, r0
	mov r0, #10
	bl putch
	mov r4, r0
	ldr r4, =1
	str r4, [fp, #-24]
	ldr r4, =2
	ldr r5, addr_d0
	str r4, [r5]
	ldr r4, [fp, #-24]
	cmp r4, #1
	movge r4, #1
	movlt r4, #0
	bge .L175
	b .L178
.L165:
	mov r0, #1
	bl set_b
	mov r4, r0
	cmp r4, #0
	bne .L163
	b .L170
.L166:
.L167:
	b .L164
.L168:
.L169:
.L170:
	b .L164
.L171:
.L173:
	b .L174
.L174:
	ldr r4, addr_d0
	ldr r5, [r4]
	mov r0, r5
	bl putint
	mov r4, r0
	mov r0, #32
	bl putch
	mov r4, r0
	ldr r4, [fp, #-24]
	cmp r4, #1
	movle r4, #1
	movgt r4, #0
	ble .L182
	b .L187
.L175:
	mov r0, #3
	bl set_d
	mov r4, r0
	cmp r4, #0
	bne .L173
	b .L180
.L176:
.L177:
.L178:
	b .L174
.L179:
.L180:
	b .L174
.L181:
.L182:
	b .L183
.L183:
	ldr r4, addr_d0
	ldr r5, [r4]
	mov r0, r5
	bl putint
	mov r4, r0
	mov r0, #10
	bl putch
	mov r4, r0
	ldr r4, =2
	add r5, r4, #1
	ldr r4, =3
	sub r6, r4, r5
	ldr r4, =16
	cmp r4, r6
	movge r4, #1
	movlt r4, #0
	bge .L191
	b .L195
.L184:
	mov r0, #4
	bl set_d
	mov r4, r0
	cmp r4, #0
	bne .L182
	b .L189
.L185:
.L186:
.L187:
	b .L184
.L188:
.L189:
	b .L183
.L190:
.L191:
	mov r0, #65
	bl putch
	mov r4, r0
	b .L192
.L192:
	ldr r4, =25
	sub r5, r4, #7
	ldr r4, =6
	ldr r6, =3
	mul r7, r4, r6
	ldr r4, =36
	sub r6, r4, r7
	cmp r5, r6
	bne .L196
	b .L200
.L193:
.L194:
.L195:
	b .L192
.L196:
	mov r0, #66
	bl putch
	mov r4, r0
	b .L197
.L197:
	ldr r4, =1
	cmp r4, #8
	movlt r4, #1
	movge r4, #0
	ldr r5, =7
	ldr r6, =2
	sdiv r7, r5, r6
	mul r6, r7, r6
	sub r7, r5, r6
	mov r5, r4
	cmp r5, r7
	bne .L201
	b .L209
	b .F0
.LTORG
addr_a0:
	.word a
addr_b0:
	.word b
addr_d0:
	.word d
.F0:
.L198:
.L199:
.L200:
	b .L197
.L201:
	mov r0, #67
	bl putch
	mov r4, r0
	b .L202
.L202:
	ldr r4, =3
	cmp r4, #4
	movgt r4, #1
	movle r4, #0
	mov r5, r4
	cmp r5, #0
	beq .L210
	b .L218
.L203:
.L204:
	mov r0, #0
	add sp, sp, #24
	pop {r4, r5, r6, r7, fp, lr}
	bx lr
.L205:
	b .L204
.L207:
.L208:
.L209:
	b .L202
.L210:
	mov r0, #68
	bl putch
	mov r4, r0
	b .L211
.L211:
	ldr r4, =102
	cmp r4, #63
	movle r4, #1
	movgt r4, #0
	mov r5, r4
	ldr r4, =1
	cmp r4, r5
	beq .L219
	b .L227
.L212:
.L213:
	mov r0, #0
	add sp, sp, #24
	pop {r4, r5, r6, r7, fp, lr}
	bx lr
.L214:
	b .L213
.L216:
.L217:
.L218:
	b .L211
.L219:
	mov r0, #69
	bl putch
	mov r4, r0
	b .L220
.L220:
	ldr r4, =5
	sub r5, r4, #6
	ldr r4, =0
	cmp r4, #0
	moveq r4, #1
	movne r4, #0
	mov r6, r4
	ldr r4, =0
	sub r7, r4, r6
	cmp r5, r7
	beq .L228
	b .L234
.L221:
.L222:
	mov r0, #0
	add sp, sp, #24
	pop {r4, r5, r6, r7, fp, lr}
	bx lr
.L223:
	b .L222
.L225:
.L226:
.L227:
	b .L220
.L228:
	mov r0, #70
	bl putch
	mov r4, r0
	b .L229
.L229:
	mov r0, #10
	bl putch
	mov r4, r0
	ldr r4, =0
	str r4, [fp, #-20]
	ldr r4, =1
	str r4, [fp, #-16]
	ldr r4, =2
	str r4, [fp, #-12]
	ldr r4, =3
	str r4, [fp, #-8]
	ldr r4, =4
	str r4, [fp, #-4]
	b .L240
.L232:
.L233:
.L234:
	b .L229
.L240:
	ldr r4, [fp, #-20]
	cmp r4, #0
	bne .L243
	b .L245
.L241:
	mov r0, #32
	bl putch
	mov r4, r0
	b .L240
.L242:
	ldr r4, [fp, #-20]
	cmp r4, #0
	bne .L250
	b .L254
.L243:
	ldr r4, [fp, #-16]
	cmp r4, #0
	bne .L241
	b .L248
.L244:
.L245:
	b .L242
.L246:
.L247:
.L248:
	b .L242
.L249:
.L250:
	mov r0, #67
	bl putch
	mov r4, r0
	b .L251
.L251:
	ldr r4, [fp, #-20]
	ldr r5, [fp, #-16]
	cmp r4, r5
	movge r4, #1
	movlt r4, #0
	bge .L259
	b .L264
.L252:
	ldr r4, [fp, #-16]
	cmp r4, #0
	bne .L250
	b .L257
.L253:
.L254:
	b .L252
.L255:
.L256:
.L257:
	b .L251
.L258:
.L259:
	mov r0, #72
	bl putch
	mov r4, r0
	b .L260
.L260:
	ldr r4, [fp, #-12]
	ldr r5, [fp, #-16]
	cmp r4, r5
	movge r4, #1
	movlt r4, #0
	bge .L270
	b .L273
.L261:
	ldr r4, [fp, #-16]
	ldr r5, [fp, #-20]
	cmp r4, r5
	movle r4, #1
	movgt r4, #0
	ble .L259
	b .L267
.L262:
.L263:
.L264:
	b .L261
.L265:
.L266:
.L267:
	b .L260
.L268:
	mov r0, #73
	bl putch
	mov r4, r0
	b .L269
.L269:
	ldr r4, [fp, #-20]
	ldr r5, [fp, #-16]
	cmp r5, #0
	moveq r5, #1
	movne r5, #0
	mov r6, r5
	cmp r4, r6
	beq .L280
	b .L285
.L270:
	ldr r4, [fp, #-4]
	ldr r5, [fp, #-8]
	cmp r4, r5
	bne .L268
	b .L276
.L271:
.L272:
.L273:
	b .L269
.L274:
.L275:
.L276:
	b .L269
.L277:
	mov r0, #74
	bl putch
	mov r4, r0
	b .L278
.L278:
	ldr r4, [fp, #-20]
	ldr r5, [fp, #-16]
	cmp r5, #0
	moveq r5, #1
	movne r5, #0
	mov r6, r5
	cmp r4, r6
	beq .L292
	b .L299
	b .F1
.LTORG
addr_a1:
	.word a
addr_b1:
	.word b
addr_d1:
	.word d
.F1:
.L279:
	ldr r4, [fp, #-4]
	ldr r5, [fp, #-4]
	cmp r4, r5
	movge r4, #1
	movlt r4, #0
	bge .L277
	b .L291
.L280:
	ldr r4, [fp, #-8]
	ldr r5, [fp, #-8]
	cmp r4, r5
	movlt r4, #1
	movge r4, #0
	blt .L277
	b .L288
.L283:
.L284:
.L285:
	b .L279
.L286:
.L287:
.L288:
	b .L279
.L289:
.L290:
.L291:
	b .L278
.L292:
	mov r0, #75
	bl putch
	mov r4, r0
	b .L293
.L293:
	mov r0, #10
	bl putch
	mov r4, r0
	mov r0, #0
	add sp, sp, #24
	pop {r4, r5, r6, r7, fp, lr}
	bx lr
.L294:
	ldr r4, [fp, #-8]
	ldr r5, [fp, #-8]
	cmp r4, r5
	movlt r4, #1
	movge r4, #0
	blt .L300
	b .L303
.L297:
.L298:
.L299:
	b .L294
.L300:
	ldr r4, [fp, #-4]
	ldr r5, [fp, #-4]
	cmp r4, r5
	movge r4, #1
	movlt r4, #0
	bge .L292
	b .L306
.L301:
.L302:
.L303:
	b .L293
.L304:
.L305:
.L306:
	b .L293

addr_a2:
	.word a
addr_b2:
	.word b
addr_d2:
	.word d
