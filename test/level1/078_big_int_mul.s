     	     	                      	                      	   	   	   	   	     	  	    		  		    			  	    		  		    			      	  	    				    		 		    	    		  		    		    			      			   				  				      										  			    			    				      		    		  		 	  	        		 		    		 	.arch armv8-a
	.arch_extension crc
	.arm
	.data
	.section .rodata
	.global len
	.align 4
	.size len, 4
len:
	.word 20
	.text
	.global main
	.type main , %function
main:
	push {r4, r5, r6, r7, r8, r9, fp, lr}
	mov fp, sp
	ldr r4, =548
	sub sp, sp, r4
.L131:
	mov r4, #0
	ldr r5, =-528
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	add r5, fp, r4
	ldr r4, =1
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =2
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =3
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =4
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =5
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =6
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =7
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =8
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =9
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =0
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =1
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =2
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =3
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =4
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =5
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =6
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =7
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =8
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =9
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =0
	str r5, [r4]
	mov r4, #0
	ldr r5, =-448
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	add r5, fp, r4
	ldr r4, =2
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =3
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =4
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =2
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =5
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =7
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =9
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =9
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =0
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =1
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =9
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =8
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =7
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =6
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =4
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =3
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =2
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =1
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =2
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =2
	str r5, [r4]
	ldr r4, addr_len0
	ldr r5, [r4]
	ldr r4, =-368
	str r5, [fp, r4]
	ldr r4, addr_len0
	ldr r5, [r4]
	ldr r4, =-364
	str r5, [fp, r4]
	mov r4, #0
	mov r5, #-160
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	add r5, fp, r4
	ldr r4, =0
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =0
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =0
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =0
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =0
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =0
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =0
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =0
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =0
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =0
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =0
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =0
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =0
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =0
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =0
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =0
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =0
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =0
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =0
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =0
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =0
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =0
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =0
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =0
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =0
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =0
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =0
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =0
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =0
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =0
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =0
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =0
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =0
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =0
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =0
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =0
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =0
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =0
	str r5, [r4]
	add r5, r4, #4
	ldr r4, =0
	str r4, [r5]
	add r4, r5, #4
	ldr r5, =0
	str r5, [r4]
	ldr r4, =0
	ldr r5, =-548
	str r4, [fp, r5]
	b .L224
	b .F0
.LTORG
addr_len0:
	.word len
.F0:
.L224:
	ldr r5, =-548
	ldr r4, [fp, r5]
	ldr r6, =-368
	ldr r5, [fp, r6]
	cmp r4, r5
	movlt r4, #1
	movge r4, #0
	blt .L225
	b .L229
.L225:
	ldr r5, =-548
	ldr r4, [fp, r5]
	ldr r5, =-528
	mov r7, #4
	mul r6, r4, r7
	add r4, r5, r6
	add r5, fp, r4
	ldr r4, [r5]
	ldr r6, =-548
	ldr r5, [fp, r6]
	ldr r6, =-360
	mov r7, #4
	mul r8, r5, r7
	add r5, r6, r8
	add r6, fp, r5
	str r4, [r6]
	ldr r5, =-548
	ldr r4, [fp, r5]
	add r5, r4, #1
	ldr r4, =-548
	str r5, [fp, r4]
	b .L224
.L226:
	ldr r4, =0
	ldr r5, =-548
	str r4, [fp, r5]
	b .L231
.L227:
.L228:
.L229:
	b .L226
.L231:
	ldr r5, =-548
	ldr r4, [fp, r5]
	ldr r6, =-364
	ldr r5, [fp, r6]
	cmp r4, r5
	movlt r4, #1
	movge r4, #0
	blt .L232
	b .L236
.L232:
	ldr r5, =-548
	ldr r4, [fp, r5]
	ldr r5, =-448
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	add r5, fp, r4
	ldr r4, [r5]
	ldr r5, =-548
	ldr r6, [fp, r5]
	ldr r5, =-260
	mov r7, #4
	mul r8, r6, r7
	add r6, r5, r8
	add r5, fp, r6
	str r4, [r5]
	ldr r5, =-548
	ldr r4, [fp, r5]
	add r5, r4, #1
	ldr r4, =-548
	str r5, [fp, r4]
	b .L231
.L233:
	ldr r4, =-368
	ldr r5, [fp, r4]
	ldr r6, =-364
	ldr r4, [fp, r6]
	add r6, r5, r4
	sub r4, r6, #1
	ldr r5, =-536
	str r4, [fp, r5]
	ldr r4, =0
	ldr r5, =-548
	str r4, [fp, r5]
	b .L238
.L234:
.L235:
.L236:
	b .L233
.L238:
	ldr r5, =-548
	ldr r4, [fp, r5]
	ldr r6, =-536
	ldr r5, [fp, r6]
	cmp r4, r5
	movle r4, #1
	movgt r4, #0
	ble .L239
	b .L243
.L239:
	ldr r5, =-548
	ldr r4, [fp, r5]
	mov r5, #-160
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	add r5, fp, r4
	ldr r4, =0
	str r4, [r5]
	ldr r5, =-548
	ldr r4, [fp, r5]
	add r5, r4, #1
	ldr r4, =-548
	str r5, [fp, r4]
	b .L238
.L240:
	ldr r4, =0
	ldr r5, =-532
	str r4, [fp, r5]
	ldr r5, =-364
	ldr r4, [fp, r5]
	sub r5, r4, #1
	ldr r4, =-548
	str r5, [fp, r4]
	b .L244
.L241:
.L242:
.L243:
	b .L240
.L244:
	ldr r5, =-548
	ldr r4, [fp, r5]
	ldr r5, =0
	sub r6, r5, #1
	cmp r4, r6
	movgt r4, #1
	movle r4, #0
	bgt .L245
	b .L249
.L245:
	ldr r5, =-548
	ldr r4, [fp, r5]
	ldr r5, =-260
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	add r5, fp, r4
	ldr r4, [r5]
	ldr r5, =-540
	str r4, [fp, r5]
	ldr r5, =-368
	ldr r4, [fp, r5]
	sub r5, r4, #1
	ldr r4, =-544
	str r5, [fp, r4]
	b .L251
.L246:
	mov r4, #0
	mov r5, #-160
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	add r5, fp, r4
	ldr r4, [r5]
	cmp r4, #0
	bne .L266
	b .L271
.L247:
.L248:
.L249:
	b .L246
.L251:
	ldr r5, =-544
	ldr r4, [fp, r5]
	ldr r5, =0
	sub r6, r5, #1
	cmp r4, r6
	movgt r4, #1
	movle r4, #0
	bgt .L252
	b .L256
.L252:
	ldr r5, =-536
	ldr r4, [fp, r5]
	mov r5, #-160
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	add r5, fp, r4
	ldr r4, [r5]
	ldr r6, =-540
	ldr r5, [fp, r6]
	ldr r7, =-544
	ldr r6, [fp, r7]
	ldr r7, =-360
	mov r8, #4
	mul r9, r6, r8
	add r6, r7, r9
	add r7, fp, r6
	ldr r6, [r7]
	mul r7, r5, r6
	add r5, r4, r7
	ldr r4, =-532
	str r5, [fp, r4]
	ldr r5, =-532
	ldr r4, [fp, r5]
	cmp r4, #10
	movge r4, #1
	movlt r4, #0
	bge .L259
	b .L264
	b .F1
.LTORG
addr_len1:
	.word len
.F1:
.L253:
	ldr r5, =-536
	ldr r4, [fp, r5]
	ldr r5, =-368
	ldr r6, [fp, r5]
	add r5, r4, r6
	sub r4, r5, #1
	ldr r5, =-536
	str r4, [fp, r5]
	ldr r5, =-548
	ldr r4, [fp, r5]
	sub r5, r4, #1
	ldr r4, =-548
	str r5, [fp, r4]
	b .L244
.L254:
.L255:
.L256:
	b .L253
.L259:
	ldr r5, =-532
	ldr r4, [fp, r5]
	ldr r5, =-536
	ldr r6, [fp, r5]
	mov r5, #-160
	mov r7, #4
	mul r8, r6, r7
	add r6, r5, r8
	add r5, fp, r6
	str r4, [r5]
	ldr r5, =-536
	ldr r4, [fp, r5]
	sub r5, r4, #1
	mov r4, #-160
	mov r7, #4
	mul r6, r5, r7
	add r5, r4, r6
	add r4, fp, r5
	ldr r5, [r4]
	ldr r6, =-532
	ldr r4, [fp, r6]
	ldr r6, =10
	sdiv r7, r4, r6
	add r4, r5, r7
	ldr r6, =-536
	ldr r5, [fp, r6]
	sub r6, r5, #1
	mov r5, #-160
	mov r8, #4
	mul r7, r6, r8
	add r6, r5, r7
	add r5, fp, r6
	str r4, [r5]
	b .L261
.L260:
	ldr r4, =-532
	ldr r5, [fp, r4]
	ldr r6, =-536
	ldr r4, [fp, r6]
	mov r6, #-160
	mov r7, #4
	mul r8, r4, r7
	add r4, r6, r8
	add r6, fp, r4
	str r5, [r6]
	b .L261
.L261:
	ldr r5, =-544
	ldr r4, [fp, r5]
	sub r5, r4, #1
	ldr r4, =-544
	str r5, [fp, r4]
	ldr r5, =-536
	ldr r4, [fp, r5]
	sub r5, r4, #1
	ldr r4, =-536
	str r5, [fp, r4]
	b .L251
.L262:
.L263:
.L264:
	b .L260
.L266:
	mov r4, #0
	mov r5, #-160
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	add r5, fp, r4
	ldr r4, [r5]
	mov r0, r4
	bl putint
	mov r4, r0
	b .L267
.L267:
	ldr r4, =1
	ldr r5, =-548
	str r4, [fp, r5]
	b .L273
.L269:
.L270:
.L271:
	b .L267
.L273:
	ldr r5, =-548
	ldr r4, [fp, r5]
	ldr r6, =-368
	ldr r5, [fp, r6]
	ldr r7, =-364
	ldr r6, [fp, r7]
	add r7, r5, r6
	sub r5, r7, #1
	cmp r4, r5
	movle r4, #1
	movgt r4, #0
	ble .L274
	b .L278
.L274:
	ldr r5, =-548
	ldr r4, [fp, r5]
	mov r5, #-160
	mov r6, #4
	mul r7, r4, r6
	add r4, r5, r7
	add r5, fp, r4
	ldr r4, [r5]
	mov r0, r4
	bl putint
	mov r4, r0
	ldr r5, =-548
	ldr r4, [fp, r5]
	add r5, r4, #1
	ldr r4, =-548
	str r5, [fp, r4]
	b .L273
.L275:
	mov r0, #0
	ldr r1, =548
	add sp, sp, r1
	pop {r4, r5, r6, r7, r8, r9, fp, lr}
	bx lr
.L276:
.L277:
.L278:
	b .L275

addr_len2:
	.word len
