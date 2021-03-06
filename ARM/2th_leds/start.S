
.globl _start
_start:

/* 硬件相关的设置 */
    /* Peri port setup */
    ldr r0, =0x70000000
    orr r0, r0, #0x13
    mcr p15,0,r0,c15,c2,4       @ 256M(0x70000000-0x7fffffff)
    
/* 关看门狗 */
/* 往WTCON(0x7E004000)写0 */
	
	ldr r0, =0x7E004000
	mov r1, #0
	str r1, [r0]
/* 设置GPMCON让GPM0/1/2/3作为输出引脚 */
	ldr r1, =0x7F008820
	ldr r0, =0x1111
	str r0, [r1]

/* 设置GPMDAT让GPM3输出0 */
	ldr r1, =0x7F008824
	mov r0, #0

loop:	
	str r0, [r1]
	add r0, r0, #1
	cmp r0, #16
	moveq r0, #0
	bl delay
	b loop

delay:
	mov r2, #0x10000
delay_loop:
	sub r2, r2, #1
	cmp r2, #0
	bne delay_loop		
	mov pc, lr

halt:
	b halt	
