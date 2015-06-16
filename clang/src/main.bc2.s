	.syntax unified
	.eabi_attribute	6, 10
	.eabi_attribute	7, 77
	.eabi_attribute	8, 0
	.eabi_attribute	9, 2
	.eabi_attribute	20, 1
	.eabi_attribute	21, 1
	.eabi_attribute	23, 3
	.eabi_attribute	24, 1
	.eabi_attribute	25, 1
	.eabi_attribute	44, 0
	.file	"main.bc2"
	.text
	.globl	blinky_blinky_init
	.align	2
	.type	blinky_blinky_init,%function
	.code	16                      @ @blinky_blinky_init
	.thumb_func
blinky_blinky_init:
@ BB#0:
	push	{r7, lr}
	movw	r1, :lower16:variable_delay
	mov	r7, sp
	movt	r1, :upper16:variable_delay
	strb	r0, [r1]
	movw	r0, :lower16:.L.str
	movt	r0, :upper16:.L.str
	bl	led_init
	movw	r0, :lower16:.L.str1
	movt	r0, :upper16:.L.str1
	bl	led_init
	movw	r0, :lower16:.L.str2
	movt	r0, :upper16:.L.str2
	bl	led_init
	movw	r0, :lower16:.L.str3
	movt	r0, :upper16:.L.str3
	bl	led_init
	pop	{r7, pc}
.Ltmp0:
	.size	blinky_blinky_init, .Ltmp0-blinky_blinky_init

	.globl	blinky_blinky
	.align	2
	.type	blinky_blinky,%function
	.code	16                      @ @blinky_blinky
	.thumb_func
blinky_blinky:
@ BB#0:
	push	{r4, r5, r7, lr}
	movw	r1, :lower16:delay_postavljen
	add	r7, sp, #8
	movt	r1, :upper16:delay_postavljen
	ldrb	r2, [r1]
	cbnz	r2, .LBB1_2
@ BB#1:
	movw	r2, :lower16:delay
	movt	r2, :upper16:delay
	strb	r0, [r2]
	movw	r2, :lower16:delay_max
	movt	r2, :upper16:delay_max
	strb	r0, [r2]
	movs	r0, #1
	strb	r0, [r1]
.LBB1_2:
	movw	r4, :lower16:.L.str3
	movs	r1, #2
	movt	r4, :upper16:.L.str3
	mov	r0, r4
	bl	led
	movw	r5, :lower16:delay
	movt	r5, :upper16:delay
	ldrb	r0, [r5]
	bl	delay_ms
	mov	r0, r4
	movs	r1, #2
	bl	led
	movw	r4, :lower16:.L.str
	movs	r1, #2
	movt	r4, :upper16:.L.str
	mov	r0, r4
	bl	led
	ldrb	r0, [r5]
	bl	delay_ms
	mov	r0, r4
	movs	r1, #2
	bl	led
	movw	r4, :lower16:.L.str1
	movs	r1, #2
	movt	r4, :upper16:.L.str1
	mov	r0, r4
	bl	led
	ldrb	r0, [r5]
	bl	delay_ms
	mov	r0, r4
	movs	r1, #2
	bl	led
	movw	r4, :lower16:.L.str2
	movs	r1, #2
	movt	r4, :upper16:.L.str2
	mov	r0, r4
	bl	led
	ldrb	r0, [r5]
	bl	delay_ms
	mov	r0, r4
	movs	r1, #2
	bl	led
	movw	r0, :lower16:variable_delay
	movt	r0, :upper16:variable_delay
	ldrb	r0, [r0]
	cmp	r0, #0
	it	eq
	popeq	{r4, r5, r7, pc}
	movw	r0, :lower16:delay_flag
	movt	r0, :upper16:delay_flag
	ldr	r1, [r0]
	cmp	r1, #0
	bne	.LBB1_4
@ BB#3:                                 @ %.thread.i
	ldrb	r1, [r5]
	adds	r1, #1
	b	.LBB1_6
.LBB1_4:
	cmp	r1, #1
	bne	.LBB1_7
@ BB#5:
	ldrb	r1, [r5]
	subs	r1, #1
.LBB1_6:                                @ %._crit_edge.i
	strb	r1, [r5]
	b	.LBB1_8
.LBB1_7:                                @ %.._crit_edge.i_crit_edge
	ldrb	r1, [r5]
.LBB1_8:                                @ %._crit_edge.i
	movw	r2, :lower16:delay_max
	uxtb	r3, r1
	movt	r2, :upper16:delay_max
	ldrb	r2, [r2]
	cmp	r3, r2
	itt	hs
	movhs	r2, #1
	strhs	r2, [r0]
	tst.w	r1, #255
	itt	eq
	moveq	r1, #0
	streq	r1, [r0]
	pop	{r4, r5, r7, pc}
.Ltmp1:
	.size	blinky_blinky, .Ltmp1-blinky_blinky

	.globl	__aeabi_memset
	.align	2
	.type	__aeabi_memset,%function
	.code	16                      @ @__aeabi_memset
	.thumb_func
__aeabi_memset:
@ BB#0:
	push	{r7, lr}
	mov	r7, sp
	bl	memset
	pop	{r7, pc}
.Ltmp2:
	.size	__aeabi_memset, .Ltmp2-__aeabi_memset

	.globl	__aeabi_memcpy
	.align	2
	.type	__aeabi_memcpy,%function
	.code	16                      @ @__aeabi_memcpy
	.thumb_func
__aeabi_memcpy:
@ BB#0:
	push	{r7, lr}
	mov	r7, sp
	bl	memcpy
	pop	{r7, pc}
.Ltmp3:
	.size	__aeabi_memcpy, .Ltmp3-__aeabi_memcpy

	.globl	__aeabi_memcpy4
	.align	2
	.type	__aeabi_memcpy4,%function
	.code	16                      @ @__aeabi_memcpy4
	.thumb_func
__aeabi_memcpy4:
@ BB#0:
	push	{r7, lr}
	mov	r7, sp
	bl	memcpy
	pop	{r7, pc}
.Ltmp4:
	.size	__aeabi_memcpy4, .Ltmp4-__aeabi_memcpy4

	.globl	__aeabi_memclr
	.align	2
	.type	__aeabi_memclr,%function
	.code	16                      @ @__aeabi_memclr
	.thumb_func
__aeabi_memclr:
@ BB#0:
	push	{r7, lr}
	mov	r2, r1
	movs	r1, #0
	mov	r7, sp
	bl	memset
	pop	{r7, pc}
.Ltmp5:
	.size	__aeabi_memclr, .Ltmp5-__aeabi_memclr

	.globl	__aeabi_memclr4
	.align	2
	.type	__aeabi_memclr4,%function
	.code	16                      @ @__aeabi_memclr4
	.thumb_func
__aeabi_memclr4:
@ BB#0:
	push	{r7, lr}
	mov	r2, r1
	movs	r1, #0
	mov	r7, sp
	bl	memset
	pop	{r7, pc}
.Ltmp6:
	.size	__aeabi_memclr4, .Ltmp6-__aeabi_memclr4

	.globl	clock_print
	.align	2
	.type	clock_print,%function
	.code	16                      @ @clock_print
	.thumb_func
clock_print:
@ BB#0:
	push.w	{r4, r7, r11, lr}
	add	r7, sp, #4
	sub	sp, #16
	movw	r0, :lower16:.L.str4
	movt	r0, :upper16:.L.str4
	bl	printf
	mov	r0, sp
	bl	RCC_GetClocksFreq
	movw	r0, :lower16:SystemCoreClock
	movw	r4, #56963
	movt	r0, :upper16:SystemCoreClock
	movt	r4, #17179
	ldr	r0, [r0]
	umull	r0, r1, r0, r4
	movw	r0, :lower16:.L.str15
	lsrs	r1, r1, #18
	movt	r0, :upper16:.L.str15
	bl	printf
	movw	r0, :lower16:.L.str26
	movs	r1, #16
	movt	r0, :upper16:.L.str26
	bl	printf
	movw	r0, :lower16:.L.str37
	movs	r1, #8
	movt	r0, :upper16:.L.str37
	bl	printf
	ldr	r0, [sp]
	umull	r0, r1, r0, r4
	movw	r0, :lower16:.L.str48
	lsrs	r1, r1, #18
	movt	r0, :upper16:.L.str48
	bl	printf
	ldr	r0, [sp, #4]
	umull	r0, r1, r0, r4
	movw	r0, :lower16:.L.str5
	lsrs	r1, r1, #18
	movt	r0, :upper16:.L.str5
	bl	printf
	ldr	r0, [sp, #8]
	umull	r0, r1, r0, r4
	movw	r0, :lower16:.L.str6
	lsrs	r1, r1, #18
	movt	r0, :upper16:.L.str6
	bl	printf
	ldr	r0, [sp, #12]
	umull	r0, r1, r0, r4
	movw	r0, :lower16:.L.str7
	lsrs	r1, r1, #18
	movt	r0, :upper16:.L.str7
	bl	printf
	bl	RCC_GetSYSCLKSource
	mov	r1, r0
	movw	r0, :lower16:.L.str8
	movt	r0, :upper16:.L.str8
	bl	printf
	movw	r0, :lower16:.L.str9
	movt	r0, :upper16:.L.str9
	bl	printf
	add	sp, #16
	pop.w	{r4, r7, r11, pc}
.Ltmp7:
	.size	clock_print, .Ltmp7-clock_print

	.globl	delay_init
	.align	2
	.type	delay_init,%function
	.code	16                      @ @delay_init
	.thumb_func
delay_init:
@ BB#0:
	movw	r0, :lower16:SystemCoreClock
	movw	r1, #56963
	movt	r0, :upper16:SystemCoreClock
	movt	r1, #17179
	ldr	r0, [r0]
	umull	r0, r1, r0, r1
	mov.w	r0, #-1
	add.w	r0, r0, r1, lsr #18
	movw	r1, #57364
	movt	r1, #57344
	str	r0, [r1]
	movw	r0, #60707
	movs	r1, #240
	movt	r0, #57344
	strb	r1, [r0]
	movw	r0, #57368
	movs	r1, #0
	movt	r0, #57344
	str	r1, [r0]
	movw	r0, #57360
	movs	r1, #7
	movt	r0, #57344
	str	r1, [r0]
	bx	lr
.Ltmp8:
	.size	delay_init, .Ltmp8-delay_init

	.globl	delay_us
	.align	2
	.type	delay_us,%function
	.code	16                      @ @delay_us
	.thumb_func
delay_us:
@ BB#0:
	movw	r1, :lower16:_MergedGlobals
	movt	r1, :upper16:_MergedGlobals
	str	r0, [r1]
.LBB9_1:                                @ =>This Inner Loop Header: Depth=1
	ldr	r0, [r1]
	cmp	r0, #0
	bne	.LBB9_1
@ BB#2:
	bx	lr
.Ltmp9:
	.size	delay_us, .Ltmp9-delay_us

	.globl	delay_ms
	.align	2
	.type	delay_ms,%function
	.code	16                      @ @delay_ms
	.thumb_func
delay_ms:
@ BB#0:
	mov.w	r1, #1000
	muls	r1, r0, r1
	movw	r0, :lower16:_MergedGlobals
	movt	r0, :upper16:_MergedGlobals
	str	r1, [r0]
.LBB10_1:                               @ =>This Inner Loop Header: Depth=1
	ldr	r1, [r0]
	cmp	r1, #0
	bne	.LBB10_1
@ BB#2:                                 @ %delay_us.exit
	bx	lr
.Ltmp10:
	.size	delay_ms, .Ltmp10-delay_ms

	.globl	delay_s
	.align	2
	.type	delay_s,%function
	.code	16                      @ @delay_s
	.thumb_func
delay_s:
@ BB#0:
	movw	r1, #16960
	movt	r1, #15
	muls	r1, r0, r1
	movw	r0, :lower16:_MergedGlobals
	movt	r0, :upper16:_MergedGlobals
	str	r1, [r0]
.LBB11_1:                               @ =>This Inner Loop Header: Depth=1
	ldr	r1, [r0]
	cmp	r1, #0
	bne	.LBB11_1
@ BB#2:                                 @ %delay_us.exit
	bx	lr
.Ltmp11:
	.size	delay_s, .Ltmp11-delay_s

	.globl	get_uptime_us
	.align	2
	.type	get_uptime_us,%function
	.code	16                      @ @get_uptime_us
	.thumb_func
get_uptime_us:
@ BB#0:
	movw	r0, :lower16:uptime_us
	movt	r0, :upper16:uptime_us
	ldr	r0, [r0]
	bx	lr
.Ltmp12:
	.size	get_uptime_us, .Ltmp12-get_uptime_us

	.globl	get_uptime_ms
	.align	2
	.type	get_uptime_ms,%function
	.code	16                      @ @get_uptime_ms
	.thumb_func
get_uptime_ms:
@ BB#0:
	movw	r0, :lower16:uptime_us
	movw	r1, #19923
	movt	r0, :upper16:uptime_us
	movt	r1, #4194
	ldr	r0, [r0]
	umull	r0, r1, r0, r1
	lsrs	r0, r1, #6
	bx	lr
.Ltmp13:
	.size	get_uptime_ms, .Ltmp13-get_uptime_ms

	.globl	get_uptime_s
	.align	2
	.type	get_uptime_s,%function
	.code	16                      @ @get_uptime_s
	.thumb_func
get_uptime_s:
@ BB#0:
	movw	r0, :lower16:uptime_us
	movw	r1, #56963
	movt	r0, :upper16:uptime_us
	movt	r1, #17179
	ldr	r0, [r0]
	umull	r0, r1, r0, r1
	lsrs	r0, r1, #18
	bx	lr
.Ltmp14:
	.size	get_uptime_s, .Ltmp14-get_uptime_s

	.globl	get_uptime
	.align	2
	.type	get_uptime,%function
	.code	16                      @ @get_uptime
	.thumb_func
get_uptime:
@ BB#0:
	push.w	{r4, r5, r6, r7, r8, lr}
	add	r7, sp, #12
	sub	sp, #16
	movw	r0, :lower16:uptime_us
	movt	r0, :upper16:uptime_us
	ldr	r0, [r0]
	bl	__aeabi_ui2d
	movw	r3, #16384
	movs	r2, #0
	movt	r3, #16527
	bl	__aeabi_ddiv
	bl	round
	bl	__aeabi_d2uiz
	movw	r1, #45683
	movw	r4, :lower16:get_uptime.uptime_ms
	movt	r1, #17895
	movt	r4, :upper16:get_uptime.uptime_ms
	umull	r1, r2, r0, r1
	lsrs	r1, r2, #14
	movw	r2, #60000
	mls	r0, r1, r2, r0
	strh	r0, [r4]
	ldrh	r0, [r4]
	cmp.w	r0, #1000
	blo	.LBB15_3
@ BB#1:
	movw	r8, :lower16:get_uptime.msb_ms
	movt	r8, :upper16:get_uptime.msb_ms
	ldrb.w	r5, [r8]
	ldrh	r0, [r4]
	bl	__aeabi_i2d
	movw	r3, #16384
	movs	r2, #0
	movt	r3, #16527
	bl	__aeabi_ddiv
	bl	round
	bl	__aeabi_d2uiz
	movw	r6, #34953
	movt	r6, #34952
	umull	r1, r2, r0, r6
	lsrs	r1, r2, #5
	lsls	r1, r1, #4
	sub.w	r1, r1, r2, lsr #5
	sub.w	r0, r0, r1, lsl #2
	cmp	r5, r0
	beq	.LBB15_3
@ BB#2:
	ldrh	r0, [r4]
	bl	__aeabi_i2d
	movw	r3, #16384
	movs	r2, #0
	movt	r3, #16527
	bl	__aeabi_ddiv
	bl	round
	bl	__aeabi_d2uiz
	umull	r1, r2, r0, r6
	lsrs	r1, r2, #5
	lsls	r1, r1, #4
	sub.w	r1, r1, r2, lsr #5
	sub.w	r0, r0, r1, lsl #2
	strb.w	r0, [r8]
	movw	r0, :lower16:get_uptime.uptime_s
	movt	r0, :upper16:get_uptime.uptime_s
	ldrb	r1, [r0]
	adds	r1, #1
	strb	r1, [r0]
.LBB15_3:
	movw	r0, :lower16:get_uptime.uptime_s
	movt	r0, :upper16:get_uptime.uptime_s
	ldrb	r1, [r0]
	cmp	r1, #60
	blo	.LBB15_5
@ BB#4:
	movs	r1, #0
	strb	r1, [r0]
	movw	r1, :lower16:get_uptime.uptime_m
	movt	r1, :upper16:get_uptime.uptime_m
	ldrb	r2, [r1]
	adds	r2, #1
	strb	r2, [r1]
.LBB15_5:
	movw	r1, :lower16:get_uptime.uptime_m
	movt	r1, :upper16:get_uptime.uptime_m
	ldrb	r2, [r1]
	cmp	r2, #60
	blo	.LBB15_7
@ BB#6:
	movs	r2, #0
	strb	r2, [r1]
	movw	r2, :lower16:get_uptime.uptime_h
	movt	r2, :upper16:get_uptime.uptime_h
	ldrb	r3, [r2]
	adds	r3, #1
	strb	r3, [r2]
.LBB15_7:
	movw	r3, :lower16:get_uptime.uptime_h
	movt	r3, :upper16:get_uptime.uptime_h
	ldrb	r2, [r3]
	cmp	r2, #24
	blo	.LBB15_9
@ BB#8:
	movs	r2, #0
	strb	r2, [r3]
	movw	r2, :lower16:get_uptime.uptime_d
	movt	r2, :upper16:get_uptime.uptime_d
	ldrh	r6, [r2]
	adds	r6, #1
	strh	r6, [r2]
.LBB15_9:
	movw	r2, :lower16:get_uptime.uptime_d
	movw	r5, #19923
	movt	r2, :upper16:get_uptime.uptime_d
	movt	r5, #4194
	ldrh	r2, [r2]
	ldrb	r3, [r3]
	ldrb	r1, [r1]
	ldrb	r0, [r0]
	ldrh	r6, [r4]
	umull	r5, r4, r6, r5
	str	r1, [sp]
	str	r0, [sp, #4]
	movw	r0, :lower16:_MergedGlobals
	movw	r1, :lower16:.L.str10
	lsrs	r5, r4, #6
	mov.w	r4, #1000
	movt	r0, :upper16:_MergedGlobals
	movt	r1, :upper16:.L.str10
	mls	r6, r5, r4, r6
	add.w	r4, r0, #8
	mov	r0, r4
	str	r6, [sp, #8]
	bl	sprintf
	mov	r0, r4
	add	sp, #16
	pop.w	{r4, r5, r6, r7, r8, pc}
.Ltmp15:
	.size	get_uptime, .Ltmp15-get_uptime

	.globl	SysTick_Handler
	.align	2
	.type	SysTick_Handler,%function
	.code	16                      @ @SysTick_Handler
	.thumb_func
SysTick_Handler:
@ BB#0:
	movw	r0, :lower16:_MergedGlobals
	movt	r0, :upper16:_MergedGlobals
	ldr	r1, [r0]
	cmp	r1, #0
	ittt	ne
	ldrne	r1, [r0]
	subne	r1, #1
	strne	r1, [r0]
	movw	r0, :lower16:uptime_us
	movt	r0, :upper16:uptime_us
	ldr	r1, [r0]
	adds	r1, #1
	str	r1, [r0]
	ldr	r1, [r0]
	cmn.w	r1, #7296
	it	lo
	bxlo	lr
	ldr	r1, [r0]
	movw	r2, #5977
	movt	r2, #53687
	umull	r2, r3, r1, r2
	lsrs	r2, r3, #13
	movw	r3, #10000
	mls	r1, r2, r3, r1
	str	r1, [r0]
	bx	lr
.Ltmp16:
	.size	SysTick_Handler, .Ltmp16-SysTick_Handler

	.globl	get_led_structure
	.align	2
	.type	get_led_structure,%function
	.code	16                      @ @get_led_structure
	.thumb_func
get_led_structure:
@ BB#0:
	push	{r4, r5, r7, lr}
	mov	r4, r0
	movs	r0, #0
	mov	r5, r2
	movs	r2, #1
	add	r7, sp, #8
	cmp	r1, #96
	movt	r0, #16386
	bgt	.LBB17_3
@ BB#1:
	subs	r1, #65
	uxtb	r1, r1
	cmp	r1, #3
	bhi	.LBB17_4
@ BB#2:
	tbb	[pc, r1]
.LJTI17_1_1:
	.byte	(.LBB17_9-.LJTI17_1_1)/2
	.byte	(.LBB17_6-.LJTI17_1_1)/2
	.byte	(.LBB17_7-.LJTI17_1_1)/2
	.byte	(.LBB17_8-.LJTI17_1_1)/2
	.align	1
.LBB17_3:
	subs	r1, #97
	uxtb	r1, r1
	cmp	r1, #3
	bls	.LBB17_5
.LBB17_4:
	movw	r0, :lower16:.L.str13
	movt	r0, :upper16:.L.str13
	bl	printf
	movs	r0, #0
	movs	r2, #0
	b	.LBB17_9
.LBB17_5:
	tbb	[pc, r1]
.LJTI17_0_0:
	.byte	(.LBB17_9-.LJTI17_0_0)/2
	.byte	(.LBB17_6-.LJTI17_0_0)/2
	.byte	(.LBB17_7-.LJTI17_0_0)/2
	.byte	(.LBB17_8-.LJTI17_0_0)/2
	.align	1
.LBB17_6:
	movw	r0, #1024
	movs	r2, #2
	movt	r0, #16386
	b	.LBB17_9
.LBB17_7:
	movw	r0, #2048
	movs	r2, #4
	movt	r0, #16386
	b	.LBB17_9
.LBB17_8:
	movw	r0, #3072
	movs	r2, #8
	movt	r0, #16386
.LBB17_9:
	cmp	r5, #15
	bls	.LBB17_11
@ BB#10:
	movw	r0, :lower16:.L.str114
	movt	r0, :upper16:.L.str114
	bl	printf
	movs	r0, #0
	str	r0, [r4]
	str	r0, [r4, #4]
	strh	r0, [r4, #8]
	strh	r0, [r4, #10]
	pop	{r4, r5, r7, pc}
.LBB17_11:
	tbb	[pc, r5]
.LJTI17_2_2:
	.byte	(.LBB17_12-.LJTI17_2_2)/2
	.byte	(.LBB17_13-.LJTI17_2_2)/2
	.byte	(.LBB17_14-.LJTI17_2_2)/2
	.byte	(.LBB17_15-.LJTI17_2_2)/2
	.byte	(.LBB17_16-.LJTI17_2_2)/2
	.byte	(.LBB17_17-.LJTI17_2_2)/2
	.byte	(.LBB17_18-.LJTI17_2_2)/2
	.byte	(.LBB17_19-.LJTI17_2_2)/2
	.byte	(.LBB17_20-.LJTI17_2_2)/2
	.byte	(.LBB17_21-.LJTI17_2_2)/2
	.byte	(.LBB17_22-.LJTI17_2_2)/2
	.byte	(.LBB17_23-.LJTI17_2_2)/2
	.byte	(.LBB17_24-.LJTI17_2_2)/2
	.byte	(.LBB17_25-.LJTI17_2_2)/2
	.byte	(.LBB17_26-.LJTI17_2_2)/2
	.byte	(.LBB17_27-.LJTI17_2_2)/2
	.align	1
.LBB17_12:
	str	r2, [r4]
	str	r0, [r4, #4]
	movs	r0, #1
	b	.LBB17_28
.LBB17_13:
	str	r2, [r4]
	str	r0, [r4, #4]
	movs	r0, #2
	b	.LBB17_28
.LBB17_14:
	str	r2, [r4]
	str	r0, [r4, #4]
	movs	r0, #4
	b	.LBB17_28
.LBB17_15:
	str	r2, [r4]
	str	r0, [r4, #4]
	movs	r0, #8
	b	.LBB17_28
.LBB17_16:
	str	r2, [r4]
	str	r0, [r4, #4]
	movs	r0, #16
	b	.LBB17_28
.LBB17_17:
	str	r2, [r4]
	str	r0, [r4, #4]
	movs	r0, #32
	b	.LBB17_28
.LBB17_18:
	str	r2, [r4]
	str	r0, [r4, #4]
	movs	r0, #64
	b	.LBB17_28
.LBB17_19:
	str	r2, [r4]
	str	r0, [r4, #4]
	movs	r0, #128
	b	.LBB17_28
.LBB17_20:
	str	r2, [r4]
	str	r0, [r4, #4]
	mov.w	r0, #256
	b	.LBB17_28
.LBB17_21:
	str	r2, [r4]
	str	r0, [r4, #4]
	mov.w	r0, #512
	b	.LBB17_28
.LBB17_22:
	str	r2, [r4]
	str	r0, [r4, #4]
	mov.w	r0, #1024
	b	.LBB17_28
.LBB17_23:
	str	r2, [r4]
	str	r0, [r4, #4]
	mov.w	r0, #2048
	b	.LBB17_28
.LBB17_24:
	str	r2, [r4]
	str	r0, [r4, #4]
	mov.w	r0, #4096
	b	.LBB17_28
.LBB17_25:
	str	r2, [r4]
	str	r0, [r4, #4]
	mov.w	r0, #8192
	b	.LBB17_28
.LBB17_26:
	str	r2, [r4]
	str	r0, [r4, #4]
	mov.w	r0, #16384
	b	.LBB17_28
.LBB17_27:
	str	r2, [r4]
	str	r0, [r4, #4]
	mov.w	r0, #32768
.LBB17_28:
	strh	r0, [r4, #8]
	movs	r0, #0
	strh	r0, [r4, #10]
	pop	{r4, r5, r7, pc}
.Ltmp17:
	.size	get_led_structure, .Ltmp17-get_led_structure

	.globl	led_init_structure
	.align	2
	.type	led_init_structure,%function
	.code	16                      @ @led_init_structure
	.thumb_func
led_init_structure:
@ BB#0:
	push.w	{r4, r5, r6, r7, r11, lr}
	add	r7, sp, #12
	sub	sp, #24
	mov	r4, r1
	cbz	r0, .LBB18_3
@ BB#1:
	cmp	r4, #0
	itt	ne
	uxthne	r5, r2
	cmpne	r5, #0
	beq	.LBB18_3
@ BB#2:
	movs	r1, #1
	movs	r6, #1
	bl	RCC_AHB1PeriphClockCmd
	movs	r0, #0
	str	r5, [sp, #4]
	str	r6, [sp, #8]
	add	r1, sp, #4
	str	r0, [sp, #16]
	str	r0, [sp, #20]
	movs	r0, #2
	str	r0, [sp, #12]
	mov	r0, r4
	bl	GPIO_Init
.LBB18_3:
	add	sp, #24
	pop.w	{r4, r5, r6, r7, r11, pc}
.Ltmp18:
	.size	led_init_structure, .Ltmp18-led_init_structure

	.globl	led_init
	.align	2
	.type	led_init,%function
	.code	16                      @ @led_init
	.thumb_func
led_init:
@ BB#0:
	push.w	{r4, r5, r6, r7, r11, lr}
	add	r7, sp, #12
	sub	sp, #32
	ldrsb.w	r4, [r0, #1]
	adds	r0, #2
	bl	atoi
	uxtb	r2, r0
	mov	r0, sp
	mov	r1, r4
	bl	get_led_structure
	ldr	r0, [sp]
	cmp	r0, #0
	itt	ne
	ldrne	r4, [sp, #4]
	cmpne	r4, #0
	beq	.LBB19_3
@ BB#1:
	ldr	r1, [sp, #8]
	uxth	r5, r1
	cbz	r5, .LBB19_3
@ BB#2:
	movs	r1, #1
	movs	r6, #1
	bl	RCC_AHB1PeriphClockCmd
	movs	r0, #0
	str	r5, [sp, #12]
	str	r6, [sp, #16]
	add	r1, sp, #12
	str	r0, [sp, #24]
	str	r0, [sp, #28]
	movs	r0, #2
	str	r0, [sp, #20]
	mov	r0, r4
	bl	GPIO_Init
.LBB19_3:                               @ %led_init_structure.exit
	add	sp, #32
	pop.w	{r4, r5, r6, r7, r11, pc}
.Ltmp19:
	.size	led_init, .Ltmp19-led_init

	.globl	led_set
	.align	2
	.type	led_set,%function
	.code	16                      @ @led_set
	.thumb_func
led_set:
@ BB#0:
	push	{r4, r5, r7, lr}
	add	r7, sp, #8
	cmp	r0, #0
	mov	r4, r1
	it	eq
	popeq	{r4, r5, r7, pc}
	cmp	r4, #0
	itt	ne
	movwne	r0, #65535
	tstne	r2, r0
	beq	.LBB20_7
@ BB#1:
	cmp	r3, #2
	beq	.LBB20_4
@ BB#2:
	cmp	r3, #1
	bhi	.LBB20_6
@ BB#3:
	uxth	r1, r2
	mov	r0, r4
	mov	r2, r3
	bl	GPIO_WriteBit
	pop	{r4, r5, r7, pc}
.LBB20_4:
	uxth	r5, r2
	mov	r0, r4
	mov	r1, r5
	bl	GPIO_ReadInputDataBit
	cbz	r0, .LBB20_8
@ BB#5:
	mov	r0, r4
	mov	r1, r5
	movs	r2, #0
	bl	GPIO_WriteBit
	pop	{r4, r5, r7, pc}
.LBB20_6:
	movw	r0, :lower16:.L.str215
	movt	r0, :upper16:.L.str215
	bl	printf
.LBB20_7:
	pop	{r4, r5, r7, pc}
.LBB20_8:
	mov	r0, r4
	mov	r1, r5
	movs	r2, #1
	bl	GPIO_WriteBit
	pop	{r4, r5, r7, pc}
.Ltmp20:
	.size	led_set, .Ltmp20-led_set

	.globl	led
	.align	2
	.type	led,%function
	.code	16                      @ @led
	.thumb_func
led:
@ BB#0:
	push.w	{r4, r5, r6, r7, r11, lr}
	add	r7, sp, #12
	sub	sp, #16
	ldrb	r6, [r0, #1]
	adds	r0, #2
	mov	r4, r1
	bl	atoi
	mov	r5, r0
	cmp	r4, #3
	blo	.LBB21_2
@ BB#1:
	movw	r0, :lower16:.L.str316
	movt	r0, :upper16:.L.str316
	bl	printf
.LBB21_2:
	sxtb	r1, r6
	uxtb	r2, r5
	add	r0, sp, #4
	bl	get_led_structure
	add	r2, sp, #4
	mov	r3, r4
	ldm	r2, {r0, r1, r2}
	bl	led_set
	add	sp, #16
	pop.w	{r4, r5, r6, r7, r11, pc}
.Ltmp21:
	.size	led, .Ltmp21-led

	.globl	main
	.align	2
	.type	main,%function
	.code	16                      @ @main
	.thumb_func
main:
@ BB#0:
	push	{r7, lr}
	mov	r7, sp
	bl	delay_init
	movs	r0, #0
	bl	blinky_blinky_init
	mov.w	r0, #115200
	bl	USART1_init
	movw	r0, :lower16:.L.str21
	movt	r0, :upper16:.L.str21
	bl	printf
	movw	r0, :lower16:.L.str122
	movt	r0, :upper16:.L.str122
	bl	printf
	movw	r0, :lower16:.L.str223
	movt	r0, :upper16:.L.str223
	bl	printf
	movw	r0, :lower16:.L.str324
	movt	r0, :upper16:.L.str324
	bl	printf
	movw	r0, :lower16:.L.str425
	movt	r0, :upper16:.L.str425
	bl	printf
.LBB22_1:                               @ =>This Inner Loop Header: Depth=1
	movs	r0, #50
	bl	delay_ms
	b	.LBB22_1
.Ltmp22:
	.size	main, .Ltmp22-main

	.globl	NVIC_PriorityGroupConfig
	.align	2
	.type	NVIC_PriorityGroupConfig,%function
	.code	16                      @ @NVIC_PriorityGroupConfig
	.thumb_func
NVIC_PriorityGroupConfig:
@ BB#0:
	orr	r0, r0, #67108864
	movw	r1, #60684
	orr	r0, r0, #33161216
	movt	r1, #57344
	str	r0, [r1]
	bx	lr
.Ltmp23:
	.size	NVIC_PriorityGroupConfig, .Ltmp23-NVIC_PriorityGroupConfig

	.globl	NVIC_Init
	.align	2
	.type	NVIC_Init,%function
	.code	16                      @ @NVIC_Init
	.thumb_func
NVIC_Init:
@ BB#0:
	push.w	{r11, lr}
	ldr	r1, [r0, #4]
	cbz	r1, .LBB24_2
@ BB#1:
	movw	r1, #60684
	movs	r2, #7
	movt	r1, #57344
	ldr	r1, [r1]
	ldrb.w	lr, [r0, #1]
	ldrb	r3, [r0, #2]
	ldrb.w	r12, [r0]
	bic.w	r1, r2, r1, lsr #8
	movs	r2, #15
	lsrs	r2, r1
	rsb.w	r1, r1, #4
	uxtb	r1, r1
	ands	r2, r3
	lsl.w	r1, lr, r1
	orrs	r1, r2
	movw	r2, #58368
	lsls	r1, r1, #4
	movt	r2, #57344
	strb.w	r1, [r12, r2]
	movw	r1, #57600
	movw	r2, #57628
	ldrb	r0, [r0]
	movt	r1, #57344
	orr.w	r1, r1, r0, lsr #3
	b	.LBB24_3
.LBB24_2:
	ldrb	r0, [r0]
	movw	r1, #57728
	movw	r2, #57756
	movt	r1, #57344
	orr.w	r1, r1, r0, lsr #3
.LBB24_3:
	movt	r2, #57344
	and	r0, r0, #31
	ands	r1, r2
	movs	r2, #1
	lsl.w	r0, r2, r0
	str	r0, [r1]
	pop.w	{r11, pc}
.Ltmp24:
	.size	NVIC_Init, .Ltmp24-NVIC_Init

	.globl	NVIC_SetVectorTable
	.align	2
	.type	NVIC_SetVectorTable,%function
	.code	16                      @ @NVIC_SetVectorTable
	.thumb_func
NVIC_SetVectorTable:
@ BB#0:
	movw	r2, #65408
	movt	r2, #8191
	ands	r1, r2
	orrs	r0, r1
	movw	r1, #60680
	movt	r1, #57344
	str	r0, [r1]
	bx	lr
.Ltmp25:
	.size	NVIC_SetVectorTable, .Ltmp25-NVIC_SetVectorTable

	.globl	NVIC_SystemLPConfig
	.align	2
	.type	NVIC_SystemLPConfig,%function
	.code	16                      @ @NVIC_SystemLPConfig
	.thumb_func
NVIC_SystemLPConfig:
@ BB#0:
	cmp	r1, #0
	movw	r1, #60688
	movt	r1, #57344
	ldr	r2, [r1]
	ite	eq
	biceq.w	r0, r2, r0
	orrne	r0, r2
	str	r0, [r1]
	bx	lr
.Ltmp26:
	.size	NVIC_SystemLPConfig, .Ltmp26-NVIC_SystemLPConfig

	.globl	SysTick_CLKSourceConfig
	.align	2
	.type	SysTick_CLKSourceConfig,%function
	.code	16                      @ @SysTick_CLKSourceConfig
	.thumb_func
SysTick_CLKSourceConfig:
@ BB#0:
	movw	r1, #57360
	cmp	r0, #4
	movt	r1, #57344
	ldr	r2, [r1]
	ite	ne
	bicne	r0, r2, #4
	orreq	r0, r2, #4
	str	r0, [r1]
	bx	lr
.Ltmp27:
	.size	SysTick_CLKSourceConfig, .Ltmp27-SysTick_CLKSourceConfig

	.globl	_exit
	.align	2
	.type	_exit,%function
	.code	16                      @ @_exit
	.thumb_func
_exit:
@ BB#0:                                 @ %.preheader.i
	movw	r0, #4096
	movt	r0, #16385
.LBB28_1:                               @ =>This Inner Loop Header: Depth=1
	ldrh	r1, [r0]
	tst.w	r1, #64
	beq	.LBB28_1
@ BB#2:                                 @ %.preheader.i.11
	movw	r1, #4100
	movs	r2, #101
	movt	r1, #16385
	strh	r2, [r1]
.LBB28_3:                               @ =>This Inner Loop Header: Depth=1
	ldrh	r2, [r0]
	tst.w	r2, #64
	beq	.LBB28_3
@ BB#4:                                 @ %.preheader.i.22
	movs	r2, #120
	strh	r2, [r1]
.LBB28_5:                               @ =>This Inner Loop Header: Depth=1
	ldrh	r2, [r0]
	tst.w	r2, #64
	beq	.LBB28_5
@ BB#6:                                 @ %.preheader.i.33
	movs	r2, #105
	strh	r2, [r1]
.LBB28_7:                               @ =>This Inner Loop Header: Depth=1
	ldrh	r2, [r0]
	tst.w	r2, #64
	beq	.LBB28_7
@ BB#8:                                 @ %_write.exit.preheader4
	movs	r0, #116
	strh	r0, [r1]
.LBB28_9:                               @ %_write.exit
                                        @ =>This Inner Loop Header: Depth=1
	b	.LBB28_9
.Ltmp28:
	.size	_exit, .Ltmp28-_exit

	.globl	_write
	.align	2
	.type	_write,%function
	.code	16                      @ @_write
	.thumb_func
_write:
@ BB#0:
	push.w	{r11, lr}
	cmp	r0, #1
	bne	.LBB29_5
@ BB#1:                                 @ %.preheader2
	cmp	r2, #1
	blt	.LBB29_11
@ BB#2:
	movw	r3, #4096
	movw	r12, #4100
	mov.w	lr, #0
	movt	r3, #16385
	movt	r12, #16385
.LBB29_3:                               @ =>This Inner Loop Header: Depth=1
	ldrh	r0, [r3]
	tst.w	r0, #64
	beq	.LBB29_3
@ BB#4:                                 @   in Loop: Header=BB29_3 Depth=1
	ldrsb	r0, [r1], #1
	add.w	lr, lr, #1
	cmp	lr, r2
	bfc	r0, #9, #23
	strh.w	r0, [r12]
	bne	.LBB29_3
	b	.LBB29_11
.LBB29_5:
	cmp	r0, #2
	bne	.LBB29_10
@ BB#6:                                 @ %.preheader4
	cmp	r2, #0
	ble	.LBB29_11
@ BB#7:
	movw	r3, #4096
	movw	r12, #4100
	mov.w	lr, #0
	movt	r3, #16385
	movt	r12, #16385
.LBB29_8:                               @ =>This Inner Loop Header: Depth=1
	ldrh	r0, [r3]
	tst.w	r0, #64
	beq	.LBB29_8
@ BB#9:                                 @   in Loop: Header=BB29_8 Depth=1
	ldrsb	r0, [r1], #1
	add.w	lr, lr, #1
	cmp	lr, r2
	bfc	r0, #9, #23
	strh.w	r0, [r12]
	bne	.LBB29_8
	b	.LBB29_11
.LBB29_10:
	movw	r0, :lower16:errno
	movs	r1, #9
	mov.w	r2, #-1
	movt	r0, :upper16:errno
	str	r1, [r0]
.LBB29_11:                              @ %.loopexit
	mov	r0, r2
	pop.w	{r11, pc}
.Ltmp29:
	.size	_write, .Ltmp29-_write

	.globl	_close
	.align	2
	.type	_close,%function
	.code	16                      @ @_close
	.thumb_func
_close:
@ BB#0:
	mov.w	r0, #-1
	bx	lr
.Ltmp30:
	.size	_close, .Ltmp30-_close

	.globl	_execve
	.align	2
	.type	_execve,%function
	.code	16                      @ @_execve
	.thumb_func
_execve:
@ BB#0:
	movw	r0, :lower16:errno
	movs	r1, #12
	movt	r0, :upper16:errno
	str	r1, [r0]
	mov.w	r0, #-1
	bx	lr
.Ltmp31:
	.size	_execve, .Ltmp31-_execve

	.globl	_fork
	.align	2
	.type	_fork,%function
	.code	16                      @ @_fork
	.thumb_func
_fork:
@ BB#0:
	movw	r0, :lower16:errno
	movs	r1, #35
	movt	r0, :upper16:errno
	str	r1, [r0]
	mov.w	r0, #-1
	bx	lr
.Ltmp32:
	.size	_fork, .Ltmp32-_fork

	.globl	_fstat
	.align	2
	.type	_fstat,%function
	.code	16                      @ @_fstat
	.thumb_func
_fstat:
@ BB#0:
	mov.w	r0, #8192
	strh	r0, [r1, #8]
	movs	r0, #0
	bx	lr
.Ltmp33:
	.size	_fstat, .Ltmp33-_fstat

	.globl	_getpid
	.align	2
	.type	_getpid,%function
	.code	16                      @ @_getpid
	.thumb_func
_getpid:
@ BB#0:
	movs	r0, #1
	bx	lr
.Ltmp34:
	.size	_getpid, .Ltmp34-_getpid

	.globl	_isatty
	.align	2
	.type	_isatty,%function
	.code	16                      @ @_isatty
	.thumb_func
_isatty:
@ BB#0:
	cmp	r0, #3
	itt	lo
	movlo	r0, #1
	bxlo	lr
	movw	r0, :lower16:errno
	movs	r1, #9
	movt	r0, :upper16:errno
	str	r1, [r0]
	movs	r0, #0
	bx	lr
.Ltmp35:
	.size	_isatty, .Ltmp35-_isatty

	.globl	_kill
	.align	2
	.type	_kill,%function
	.code	16                      @ @_kill
	.thumb_func
_kill:
@ BB#0:
	movw	r0, :lower16:errno
	movs	r1, #22
	movt	r0, :upper16:errno
	str	r1, [r0]
	mov.w	r0, #-1
	bx	lr
.Ltmp36:
	.size	_kill, .Ltmp36-_kill

	.globl	_link
	.align	2
	.type	_link,%function
	.code	16                      @ @_link
	.thumb_func
_link:
@ BB#0:
	movw	r0, :lower16:errno
	movs	r1, #31
	movt	r0, :upper16:errno
	str	r1, [r0]
	mov.w	r0, #-1
	bx	lr
.Ltmp37:
	.size	_link, .Ltmp37-_link

	.globl	_lseek
	.align	2
	.type	_lseek,%function
	.code	16                      @ @_lseek
	.thumb_func
_lseek:
@ BB#0:
	movs	r0, #0
	bx	lr
.Ltmp38:
	.size	_lseek, .Ltmp38-_lseek

	.globl	_sbrk
	.align	2
	.type	_sbrk,%function
	.code	16                      @ @_sbrk
	.thumb_func
_sbrk:
@ BB#0:
	movw	r12, :lower16:_MergedGlobals
	mov	r1, r0
	movt	r12, :upper16:_MergedGlobals
	ldr.w	r0, [r12, #4]
	cmp	r0, #0
	ittt	eq
	movweq	r0, :lower16:_ebss
	movteq	r0, :upper16:_ebss
	streq.w	r0, [r12, #4]
	@APP
	MRS r3, msp

	@NO_APP
	ldr.w	r2, [r12, #4]
	add	r1, r2
	cmp	r1, r3
	itt	ls
	strls.w	r1, [r12, #4]
	bxls	lr
	movw	r0, :lower16:.L.str126
	movw	r2, #4096
	movw	r12, #4100
	movs	r1, #0
	movt	r0, :upper16:.L.str126
	movt	r2, #16385
	movt	r12, #16385
.LBB39_1:                               @ =>This Inner Loop Header: Depth=1
	ldrh	r3, [r2]
	tst.w	r3, #64
	beq	.LBB39_1
@ BB#2:                                 @   in Loop: Header=BB39_1 Depth=1
	ldrsb	r3, [r0], #1
	adds	r1, #1
	cmp	r1, #25
	bfc	r3, #9, #23
	strh.w	r3, [r12]
	bne	.LBB39_1
@ BB#3:                                 @ %_write.exit
	movw	r0, :lower16:errno
	movs	r1, #12
	movt	r0, :upper16:errno
	str	r1, [r0]
	mov.w	r0, #-1
	bx	lr
.Ltmp39:
	.size	_sbrk, .Ltmp39-_sbrk

	.globl	_read
	.align	2
	.type	_read,%function
	.code	16                      @ @_read
	.thumb_func
_read:
@ BB#0:
	push.w	{r11, lr}
	cmp	r0, #0
	beq	.LBB40_2
@ BB#1:
	movw	r0, :lower16:errno
	movs	r1, #9
	movt	r0, :upper16:errno
	str	r1, [r0]
	mov.w	r0, #-1
	pop.w	{r11, pc}
.LBB40_2:                               @ %.preheader2
	movs	r0, #0
	cmp	r2, #1
	it	lt
	poplt.w	{r11, pc}
	movw	lr, #4096
	movw	r12, #4100
	movt	lr, #16385
	movt	r12, #16385
	b	.LBB40_4
.LBB40_3:                               @   in Loop: Header=BB40_4 Depth=1
	ldrh.w	r3, [r12]
	adds	r0, #1
	cmp	r0, r2
	strb	r3, [r1], #1
	itt	eq
	moveq	r0, r2
	popeq.w	{r11, pc}
.LBB40_4:                               @ =>This Inner Loop Header: Depth=1
	ldrh.w	r3, [lr]
	tst.w	r3, #32
	beq	.LBB40_4
	b	.LBB40_3
.Ltmp40:
	.size	_read, .Ltmp40-_read

	.globl	_stat
	.align	2
	.type	_stat,%function
	.code	16                      @ @_stat
	.thumb_func
_stat:
@ BB#0:
	mov.w	r0, #8192
	strh	r0, [r1, #8]
	movs	r0, #0
	bx	lr
.Ltmp41:
	.size	_stat, .Ltmp41-_stat

	.globl	_times
	.align	2
	.type	_times,%function
	.code	16                      @ @_times
	.thumb_func
_times:
@ BB#0:
	mov.w	r0, #-1
	bx	lr
.Ltmp42:
	.size	_times, .Ltmp42-_times

	.globl	_unlink
	.align	2
	.type	_unlink,%function
	.code	16                      @ @_unlink
	.thumb_func
_unlink:
@ BB#0:
	movw	r0, :lower16:errno
	movs	r1, #2
	movt	r0, :upper16:errno
	str	r1, [r0]
	mov.w	r0, #-1
	bx	lr
.Ltmp43:
	.size	_unlink, .Ltmp43-_unlink

	.globl	_wait
	.align	2
	.type	_wait,%function
	.code	16                      @ @_wait
	.thumb_func
_wait:
@ BB#0:
	movw	r0, :lower16:errno
	movs	r1, #10
	movt	r0, :upper16:errno
	str	r1, [r0]
	mov.w	r0, #-1
	bx	lr
.Ltmp44:
	.size	_wait, .Ltmp44-_wait

	.globl	ADC_DeInit
	.align	2
	.type	ADC_DeInit,%function
	.code	16                      @ @ADC_DeInit
	.thumb_func
ADC_DeInit:
@ BB#0:
	push	{r7, lr}
	mov.w	r0, #256
	movs	r1, #1
	mov	r7, sp
	bl	RCC_APB2PeriphResetCmd
	mov.w	r0, #256
	movs	r1, #0
	bl	RCC_APB2PeriphResetCmd
	pop	{r7, pc}
.Ltmp45:
	.size	ADC_DeInit, .Ltmp45-ADC_DeInit

	.globl	ADC_Init
	.align	2
	.type	ADC_Init,%function
	.code	16                      @ @ADC_Init
	.thumb_func
ADC_Init:
@ BB#0:
	push	{r4, lr}
	ldr	r2, [r0, #4]
	movw	r3, #65279
	movt	r3, #64767
	and.w	r12, r2, r3
	ldr	r3, [r1]
	ldr	r2, [r1, #4]
	orr.w	r3, r3, r12
	orr.w	r2, r3, r2, lsl #8
	movw	r3, #63485
	str	r2, [r0, #4]
	movt	r3, #49407
	ldr	r2, [r0, #8]
	ldr	r4, [r1, #20]
	ldr.w	r12, [r1, #8]
	and.w	lr, r2, r3
	ldr	r2, [r1, #16]
	ldr	r3, [r1, #12]
	orr.w	r4, r4, lr
	orrs	r2, r4
	orrs	r2, r3
	mov.w	r3, #267386880
	orr.w	r2, r2, r12, lsl #1
	str	r2, [r0, #8]
	ldr	r2, [r0, #44]
	ldrb	r1, [r1, #24]
	add.w	r1, r3, r1, lsl #20
	bic	r2, r2, #15728640
	and	r1, r1, #267386880
	orrs	r1, r2
	str	r1, [r0, #44]
	pop	{r4, pc}
.Ltmp46:
	.size	ADC_Init, .Ltmp46-ADC_Init

	.globl	ADC_StructInit
	.align	2
	.type	ADC_StructInit,%function
	.code	16                      @ @ADC_StructInit
	.thumb_func
ADC_StructInit:
@ BB#0:
	movs	r1, #0
	str	r1, [r0]
	str	r1, [r0, #4]
	str	r1, [r0, #8]
	str	r1, [r0, #12]
	str	r1, [r0, #16]
	str	r1, [r0, #20]
	movs	r1, #1
	strb	r1, [r0, #24]
	bx	lr
.Ltmp47:
	.size	ADC_StructInit, .Ltmp47-ADC_StructInit

	.globl	ADC_CommonInit
	.align	2
	.type	ADC_CommonInit,%function
	.code	16                      @ @ADC_CommonInit
	.thumb_func
ADC_CommonInit:
@ BB#0:
	push.w	{r11, lr}
	movw	r12, #8964
	movw	r3, #12512
	movt	r12, #16385
	movt	r3, #65532
	ldr.w	r2, [r12]
	ldr	r1, [r0, #4]
	and.w	lr, r2, r3
	ldr	r3, [r0]
	ldr	r2, [r0, #8]
	ldr	r0, [r0, #12]
	orr.w	r3, r3, lr
	orrs	r1, r3
	orrs	r1, r2
	orrs	r0, r1
	str.w	r0, [r12]
	pop.w	{r11, pc}
.Ltmp48:
	.size	ADC_CommonInit, .Ltmp48-ADC_CommonInit

	.globl	ADC_CommonStructInit
	.align	2
	.type	ADC_CommonStructInit,%function
	.code	16                      @ @ADC_CommonStructInit
	.thumb_func
ADC_CommonStructInit:
@ BB#0:
	movs	r1, #0
	str	r1, [r0]
	str	r1, [r0, #4]
	str	r1, [r0, #8]
	str	r1, [r0, #12]
	bx	lr
.Ltmp49:
	.size	ADC_CommonStructInit, .Ltmp49-ADC_CommonStructInit

	.globl	ADC_Cmd
	.align	2
	.type	ADC_Cmd,%function
	.code	16                      @ @ADC_Cmd
	.thumb_func
ADC_Cmd:
@ BB#0:
	ldr	r2, [r0, #8]
	cmp	r1, #0
	ite	eq
	biceq	r1, r2, #1
	orrne	r1, r2, #1
	str	r1, [r0, #8]
	bx	lr
.Ltmp50:
	.size	ADC_Cmd, .Ltmp50-ADC_Cmd

	.globl	ADC_AnalogWatchdogCmd
	.align	2
	.type	ADC_AnalogWatchdogCmd,%function
	.code	16                      @ @ADC_AnalogWatchdogCmd
	.thumb_func
ADC_AnalogWatchdogCmd:
@ BB#0:
	ldr	r2, [r0, #4]
	movw	r3, #65023
	movt	r3, #65343
	ands	r2, r3
	orrs	r1, r2
	str	r1, [r0, #4]
	bx	lr
.Ltmp51:
	.size	ADC_AnalogWatchdogCmd, .Ltmp51-ADC_AnalogWatchdogCmd

	.globl	ADC_AnalogWatchdogThresholdsConfig
	.align	2
	.type	ADC_AnalogWatchdogThresholdsConfig,%function
	.code	16                      @ @ADC_AnalogWatchdogThresholdsConfig
	.thumb_func
ADC_AnalogWatchdogThresholdsConfig:
@ BB#0:
	str	r1, [r0, #36]
	str	r2, [r0, #40]
	bx	lr
.Ltmp52:
	.size	ADC_AnalogWatchdogThresholdsConfig, .Ltmp52-ADC_AnalogWatchdogThresholdsConfig

	.globl	ADC_AnalogWatchdogSingleChannelConfig
	.align	2
	.type	ADC_AnalogWatchdogSingleChannelConfig,%function
	.code	16                      @ @ADC_AnalogWatchdogSingleChannelConfig
	.thumb_func
ADC_AnalogWatchdogSingleChannelConfig:
@ BB#0:
	ldr	r2, [r0, #4]
	bic	r2, r2, #31
	orrs	r1, r2
	str	r1, [r0, #4]
	bx	lr
.Ltmp53:
	.size	ADC_AnalogWatchdogSingleChannelConfig, .Ltmp53-ADC_AnalogWatchdogSingleChannelConfig

	.globl	ADC_TempSensorVrefintCmd
	.align	2
	.type	ADC_TempSensorVrefintCmd,%function
	.code	16                      @ @ADC_TempSensorVrefintCmd
	.thumb_func
ADC_TempSensorVrefintCmd:
@ BB#0:
	movw	r1, #8964
	cmp	r0, #0
	movt	r1, #16385
	ldr	r2, [r1]
	ite	eq
	biceq	r0, r2, #8388608
	orrne	r0, r2, #8388608
	str	r0, [r1]
	bx	lr
.Ltmp54:
	.size	ADC_TempSensorVrefintCmd, .Ltmp54-ADC_TempSensorVrefintCmd

	.globl	ADC_VBATCmd
	.align	2
	.type	ADC_VBATCmd,%function
	.code	16                      @ @ADC_VBATCmd
	.thumb_func
ADC_VBATCmd:
@ BB#0:
	movw	r1, #8964
	cmp	r0, #0
	movt	r1, #16385
	ldr	r2, [r1]
	ite	eq
	biceq	r0, r2, #4194304
	orrne	r0, r2, #4194304
	str	r0, [r1]
	bx	lr
.Ltmp55:
	.size	ADC_VBATCmd, .Ltmp55-ADC_VBATCmd

	.globl	ADC_RegularChannelConfig
	.align	2
	.type	ADC_RegularChannelConfig,%function
	.code	16                      @ @ADC_RegularChannelConfig
	.thumb_func
ADC_RegularChannelConfig:
@ BB#0:
	push.w	{r11, lr}
	add.w	r12, r1, r1, lsl #1
	cmp	r1, #10
	blo	.LBB56_2
@ BB#1:
	sub.w	r12, r12, #30
	lsl.w	lr, r3, r12
	movs	r3, #7
	lsl.w	r12, r3, r12
	ldr	r3, [r0, #12]
	bic.w	r3, r3, r12
	orr.w	r3, r3, lr
	str	r3, [r0, #12]
	b	.LBB56_3
.LBB56_2:
	lsl.w	lr, r3, r12
	movs	r3, #7
	lsl.w	r12, r3, r12
	ldr	r3, [r0, #16]
	bic.w	r3, r3, r12
	orr.w	r3, r3, lr
	str	r3, [r0, #16]
.LBB56_3:
	cmp	r2, #6
	bhi	.LBB56_5
@ BB#4:
	add.w	r2, r2, r2, lsl #2
	movs	r3, #31
	subs	r2, #5
	lsls	r1, r2
	lsl.w	r2, r3, r2
	ldr	r3, [r0, #52]
	bic.w	r2, r3, r2
	orrs	r1, r2
	str	r1, [r0, #52]
	pop.w	{r11, pc}
.LBB56_5:
	cmp	r2, #12
	bhi	.LBB56_7
@ BB#6:
	add.w	r2, r2, r2, lsl #2
	movs	r3, #31
	subs	r2, #35
	lsls	r1, r2
	lsl.w	r2, r3, r2
	ldr	r3, [r0, #48]
	bic.w	r2, r3, r2
	orrs	r1, r2
	str	r1, [r0, #48]
	pop.w	{r11, pc}
.LBB56_7:
	add.w	r2, r2, r2, lsl #2
	movs	r3, #31
	subs	r2, #65
	lsls	r1, r2
	lsl.w	r2, r3, r2
	ldr	r3, [r0, #44]
	bic.w	r2, r3, r2
	orrs	r1, r2
	str	r1, [r0, #44]
	pop.w	{r11, pc}
.Ltmp56:
	.size	ADC_RegularChannelConfig, .Ltmp56-ADC_RegularChannelConfig

	.globl	ADC_SoftwareStartConv
	.align	2
	.type	ADC_SoftwareStartConv,%function
	.code	16                      @ @ADC_SoftwareStartConv
	.thumb_func
ADC_SoftwareStartConv:
@ BB#0:
	ldr	r1, [r0, #8]
	orr	r1, r1, #1073741824
	str	r1, [r0, #8]
	bx	lr
.Ltmp57:
	.size	ADC_SoftwareStartConv, .Ltmp57-ADC_SoftwareStartConv

	.globl	ADC_GetSoftwareStartConvStatus
	.align	2
	.type	ADC_GetSoftwareStartConvStatus,%function
	.code	16                      @ @ADC_GetSoftwareStartConvStatus
	.thumb_func
ADC_GetSoftwareStartConvStatus:
@ BB#0:
	ldr	r0, [r0, #8]
	ubfx	r0, r0, #22, #1
	bx	lr
.Ltmp58:
	.size	ADC_GetSoftwareStartConvStatus, .Ltmp58-ADC_GetSoftwareStartConvStatus

	.globl	ADC_EOCOnEachRegularChannelCmd
	.align	2
	.type	ADC_EOCOnEachRegularChannelCmd,%function
	.code	16                      @ @ADC_EOCOnEachRegularChannelCmd
	.thumb_func
ADC_EOCOnEachRegularChannelCmd:
@ BB#0:
	ldr	r2, [r0, #8]
	cmp	r1, #0
	ite	eq
	biceq	r1, r2, #1024
	orrne	r1, r2, #1024
	str	r1, [r0, #8]
	bx	lr
.Ltmp59:
	.size	ADC_EOCOnEachRegularChannelCmd, .Ltmp59-ADC_EOCOnEachRegularChannelCmd

	.globl	ADC_ContinuousModeCmd
	.align	2
	.type	ADC_ContinuousModeCmd,%function
	.code	16                      @ @ADC_ContinuousModeCmd
	.thumb_func
ADC_ContinuousModeCmd:
@ BB#0:
	ldr	r2, [r0, #8]
	cmp	r1, #0
	ite	eq
	biceq	r1, r2, #2
	orrne	r1, r2, #2
	str	r1, [r0, #8]
	bx	lr
.Ltmp60:
	.size	ADC_ContinuousModeCmd, .Ltmp60-ADC_ContinuousModeCmd

	.globl	ADC_DiscModeChannelCountConfig
	.align	2
	.type	ADC_DiscModeChannelCountConfig,%function
	.code	16                      @ @ADC_DiscModeChannelCountConfig
	.thumb_func
ADC_DiscModeChannelCountConfig:
@ BB#0:
	movw	r2, #57344
	movt	r2, #65535
	add.w	r1, r2, r1, lsl #13
	ldr	r2, [r0, #4]
	bic	r2, r2, #57344
	orrs	r1, r2
	str	r1, [r0, #4]
	bx	lr
.Ltmp61:
	.size	ADC_DiscModeChannelCountConfig, .Ltmp61-ADC_DiscModeChannelCountConfig

	.globl	ADC_DiscModeCmd
	.align	2
	.type	ADC_DiscModeCmd,%function
	.code	16                      @ @ADC_DiscModeCmd
	.thumb_func
ADC_DiscModeCmd:
@ BB#0:
	ldr	r2, [r0, #4]
	cmp	r1, #0
	ite	eq
	biceq	r1, r2, #2048
	orrne	r1, r2, #2048
	str	r1, [r0, #4]
	bx	lr
.Ltmp62:
	.size	ADC_DiscModeCmd, .Ltmp62-ADC_DiscModeCmd

	.globl	ADC_GetConversionValue
	.align	2
	.type	ADC_GetConversionValue,%function
	.code	16                      @ @ADC_GetConversionValue
	.thumb_func
ADC_GetConversionValue:
@ BB#0:
	ldr	r0, [r0, #76]
	uxth	r0, r0
	bx	lr
.Ltmp63:
	.size	ADC_GetConversionValue, .Ltmp63-ADC_GetConversionValue

	.globl	ADC_GetMultiModeConversionValue
	.align	2
	.type	ADC_GetMultiModeConversionValue,%function
	.code	16                      @ @ADC_GetMultiModeConversionValue
	.thumb_func
ADC_GetMultiModeConversionValue:
@ BB#0:
	movw	r0, #8968
	movt	r0, #16385
	ldr	r0, [r0]
	bx	lr
.Ltmp64:
	.size	ADC_GetMultiModeConversionValue, .Ltmp64-ADC_GetMultiModeConversionValue

	.globl	ADC_DMACmd
	.align	2
	.type	ADC_DMACmd,%function
	.code	16                      @ @ADC_DMACmd
	.thumb_func
ADC_DMACmd:
@ BB#0:
	ldr	r2, [r0, #8]
	cmp	r1, #0
	ite	eq
	biceq	r1, r2, #256
	orrne	r1, r2, #256
	str	r1, [r0, #8]
	bx	lr
.Ltmp65:
	.size	ADC_DMACmd, .Ltmp65-ADC_DMACmd

	.globl	ADC_DMARequestAfterLastTransferCmd
	.align	2
	.type	ADC_DMARequestAfterLastTransferCmd,%function
	.code	16                      @ @ADC_DMARequestAfterLastTransferCmd
	.thumb_func
ADC_DMARequestAfterLastTransferCmd:
@ BB#0:
	ldr	r2, [r0, #8]
	cmp	r1, #0
	ite	eq
	biceq	r1, r2, #512
	orrne	r1, r2, #512
	str	r1, [r0, #8]
	bx	lr
.Ltmp66:
	.size	ADC_DMARequestAfterLastTransferCmd, .Ltmp66-ADC_DMARequestAfterLastTransferCmd

	.globl	ADC_MultiModeDMARequestAfterLastTransferCmd
	.align	2
	.type	ADC_MultiModeDMARequestAfterLastTransferCmd,%function
	.code	16                      @ @ADC_MultiModeDMARequestAfterLastTransferCmd
	.thumb_func
ADC_MultiModeDMARequestAfterLastTransferCmd:
@ BB#0:
	movw	r1, #8964
	cmp	r0, #0
	movt	r1, #16385
	ldr	r2, [r1]
	ite	eq
	biceq	r0, r2, #8192
	orrne	r0, r2, #8192
	str	r0, [r1]
	bx	lr
.Ltmp67:
	.size	ADC_MultiModeDMARequestAfterLastTransferCmd, .Ltmp67-ADC_MultiModeDMARequestAfterLastTransferCmd

	.globl	ADC_InjectedChannelConfig
	.align	2
	.type	ADC_InjectedChannelConfig,%function
	.code	16                      @ @ADC_InjectedChannelConfig
	.thumb_func
ADC_InjectedChannelConfig:
@ BB#0:
	push.w	{r11, lr}
	add.w	r12, r1, r1, lsl #1
	cmp	r1, #10
	blo	.LBB68_2
@ BB#1:
	sub.w	r12, r12, #30
	lsl.w	lr, r3, r12
	movs	r3, #7
	lsl.w	r12, r3, r12
	ldr	r3, [r0, #12]
	bic.w	r3, r3, r12
	orr.w	r3, r3, lr
	str	r3, [r0, #12]
	b	.LBB68_3
.LBB68_2:
	lsl.w	lr, r3, r12
	movs	r3, #7
	lsl.w	r12, r3, r12
	ldr	r3, [r0, #16]
	bic.w	r3, r3, r12
	orr.w	r3, r3, lr
	str	r3, [r0, #16]
.LBB68_3:
	ldr	r3, [r0, #56]
	add.w	r12, r2, #2
	ubfx	r2, r3, #20, #2
	sub.w	r2, r12, r2
	uxtb	r2, r2
	add.w	r2, r2, r2, lsl #2
	lsl.w	r12, r1, r2
	movs	r1, #31
	lsls	r1, r2
	bic.w	r1, r3, r1
	orr.w	r1, r1, r12
	str	r1, [r0, #56]
	pop.w	{r11, pc}
.Ltmp68:
	.size	ADC_InjectedChannelConfig, .Ltmp68-ADC_InjectedChannelConfig

	.globl	ADC_InjectedSequencerLengthConfig
	.align	2
	.type	ADC_InjectedSequencerLengthConfig,%function
	.code	16                      @ @ADC_InjectedSequencerLengthConfig
	.thumb_func
ADC_InjectedSequencerLengthConfig:
@ BB#0:
	movs	r2, #0
	movt	r2, #65520
	add.w	r1, r2, r1, lsl #20
	ldr	r2, [r0, #56]
	bic	r2, r2, #3145728
	orrs	r1, r2
	str	r1, [r0, #56]
	bx	lr
.Ltmp69:
	.size	ADC_InjectedSequencerLengthConfig, .Ltmp69-ADC_InjectedSequencerLengthConfig

	.globl	ADC_SetInjectedOffset
	.align	2
	.type	ADC_SetInjectedOffset,%function
	.code	16                      @ @ADC_SetInjectedOffset
	.thumb_func
ADC_SetInjectedOffset:
@ BB#0:
	sub	sp, #8
	movs	r3, #0
	str	r3, [sp, #4]
	str	r0, [sp, #4]
	ldr	r0, [sp, #4]
	add	r0, r1
	str	r0, [sp, #4]
	ldr	r0, [sp, #4]
	str	r2, [r0]
	add	sp, #8
	bx	lr
.Ltmp70:
	.size	ADC_SetInjectedOffset, .Ltmp70-ADC_SetInjectedOffset

	.globl	ADC_ExternalTrigInjectedConvConfig
	.align	2
	.type	ADC_ExternalTrigInjectedConvConfig,%function
	.code	16                      @ @ADC_ExternalTrigInjectedConvConfig
	.thumb_func
ADC_ExternalTrigInjectedConvConfig:
@ BB#0:
	ldr	r2, [r0, #8]
	bic	r2, r2, #983040
	orrs	r1, r2
	str	r1, [r0, #8]
	bx	lr
.Ltmp71:
	.size	ADC_ExternalTrigInjectedConvConfig, .Ltmp71-ADC_ExternalTrigInjectedConvConfig

	.globl	ADC_ExternalTrigInjectedConvEdgeConfig
	.align	2
	.type	ADC_ExternalTrigInjectedConvEdgeConfig,%function
	.code	16                      @ @ADC_ExternalTrigInjectedConvEdgeConfig
	.thumb_func
ADC_ExternalTrigInjectedConvEdgeConfig:
@ BB#0:
	ldr	r2, [r0, #8]
	bic	r2, r2, #3145728
	orrs	r1, r2
	str	r1, [r0, #8]
	bx	lr
.Ltmp72:
	.size	ADC_ExternalTrigInjectedConvEdgeConfig, .Ltmp72-ADC_ExternalTrigInjectedConvEdgeConfig

	.globl	ADC_SoftwareStartInjectedConv
	.align	2
	.type	ADC_SoftwareStartInjectedConv,%function
	.code	16                      @ @ADC_SoftwareStartInjectedConv
	.thumb_func
ADC_SoftwareStartInjectedConv:
@ BB#0:
	ldr	r1, [r0, #8]
	orr	r1, r1, #4194304
	str	r1, [r0, #8]
	bx	lr
.Ltmp73:
	.size	ADC_SoftwareStartInjectedConv, .Ltmp73-ADC_SoftwareStartInjectedConv

	.globl	ADC_GetSoftwareStartInjectedConvCmdStatus
	.align	2
	.type	ADC_GetSoftwareStartInjectedConvCmdStatus,%function
	.code	16                      @ @ADC_GetSoftwareStartInjectedConvCmdStatus
	.thumb_func
ADC_GetSoftwareStartInjectedConvCmdStatus:
@ BB#0:
	ldr	r0, [r0, #8]
	ubfx	r0, r0, #22, #1
	bx	lr
.Ltmp74:
	.size	ADC_GetSoftwareStartInjectedConvCmdStatus, .Ltmp74-ADC_GetSoftwareStartInjectedConvCmdStatus

	.globl	ADC_AutoInjectedConvCmd
	.align	2
	.type	ADC_AutoInjectedConvCmd,%function
	.code	16                      @ @ADC_AutoInjectedConvCmd
	.thumb_func
ADC_AutoInjectedConvCmd:
@ BB#0:
	ldr	r2, [r0, #4]
	cmp	r1, #0
	ite	eq
	biceq	r1, r2, #1024
	orrne	r1, r2, #1024
	str	r1, [r0, #4]
	bx	lr
.Ltmp75:
	.size	ADC_AutoInjectedConvCmd, .Ltmp75-ADC_AutoInjectedConvCmd

	.globl	ADC_InjectedDiscModeCmd
	.align	2
	.type	ADC_InjectedDiscModeCmd,%function
	.code	16                      @ @ADC_InjectedDiscModeCmd
	.thumb_func
ADC_InjectedDiscModeCmd:
@ BB#0:
	ldr	r2, [r0, #4]
	cmp	r1, #0
	ite	eq
	biceq	r1, r2, #4096
	orrne	r1, r2, #4096
	str	r1, [r0, #4]
	bx	lr
.Ltmp76:
	.size	ADC_InjectedDiscModeCmd, .Ltmp76-ADC_InjectedDiscModeCmd

	.globl	ADC_GetInjectedConversionValue
	.align	2
	.type	ADC_GetInjectedConversionValue,%function
	.code	16                      @ @ADC_GetInjectedConversionValue
	.thumb_func
ADC_GetInjectedConversionValue:
@ BB#0:
	sub	sp, #8
	movs	r2, #0
	str	r2, [sp, #4]
	str	r0, [sp, #4]
	ldr	r0, [sp, #4]
	add	r0, r1
	adds	r0, #40
	str	r0, [sp, #4]
	ldr	r0, [sp, #4]
	ldr	r0, [r0]
	uxth	r0, r0
	add	sp, #8
	bx	lr
.Ltmp77:
	.size	ADC_GetInjectedConversionValue, .Ltmp77-ADC_GetInjectedConversionValue

	.globl	ADC_ITConfig
	.align	2
	.type	ADC_ITConfig,%function
	.code	16                      @ @ADC_ITConfig
	.thumb_func
ADC_ITConfig:
@ BB#0:
	cmp	r2, #0
	ldr	r2, [r0, #4]
	uxtb	r1, r1
	mov.w	r3, #1
	lsl.w	r1, r3, r1
	ite	eq
	biceq.w	r1, r2, r1
	orrne	r1, r2
	str	r1, [r0, #4]
	bx	lr
.Ltmp78:
	.size	ADC_ITConfig, .Ltmp78-ADC_ITConfig

	.globl	ADC_GetFlagStatus
	.align	2
	.type	ADC_GetFlagStatus,%function
	.code	16                      @ @ADC_GetFlagStatus
	.thumb_func
ADC_GetFlagStatus:
@ BB#0:
	ldr	r0, [r0]
	ands	r0, r1
	it	ne
	movne	r0, #1
	bx	lr
.Ltmp79:
	.size	ADC_GetFlagStatus, .Ltmp79-ADC_GetFlagStatus

	.globl	ADC_ClearFlag
	.align	2
	.type	ADC_ClearFlag,%function
	.code	16                      @ @ADC_ClearFlag
	.thumb_func
ADC_ClearFlag:
@ BB#0:
	mvns	r1, r1
	str	r1, [r0]
	bx	lr
.Ltmp80:
	.size	ADC_ClearFlag, .Ltmp80-ADC_ClearFlag

	.globl	ADC_GetITStatus
	.align	2
	.type	ADC_GetITStatus,%function
	.code	16                      @ @ADC_GetITStatus
	.thumb_func
ADC_GetITStatus:
@ BB#0:
	uxtb	r2, r1
	movs	r3, #1
	lsl.w	r2, r3, r2
	ldr	r3, [r0, #4]
	ands	r2, r3
	it	ne
	movne	r2, #1
	ldr	r0, [r0]
	and.w	r0, r0, r1, lsr #8
	cmp	r0, #0
	it	ne
	movne	r0, #1
	ands	r0, r2
	bx	lr
.Ltmp81:
	.size	ADC_GetITStatus, .Ltmp81-ADC_GetITStatus

	.globl	ADC_ClearITPendingBit
	.align	2
	.type	ADC_ClearITPendingBit,%function
	.code	16                      @ @ADC_ClearITPendingBit
	.thumb_func
ADC_ClearITPendingBit:
@ BB#0:
	mvn	r2, #255
	orn	r1, r2, r1, lsr #8
	str	r1, [r0]
	bx	lr
.Ltmp82:
	.size	ADC_ClearITPendingBit, .Ltmp82-ADC_ClearITPendingBit

	.globl	CAN_DeInit
	.align	2
	.type	CAN_DeInit,%function
	.code	16                      @ @CAN_DeInit
	.thumb_func
CAN_DeInit:
@ BB#0:
	push	{r7, lr}
	movw	r1, #25600
	mov	r7, sp
	movt	r1, #16384
	cmp	r0, r1
	beq	.LBB83_2
@ BB#1:
	mov.w	r0, #67108864
	movs	r1, #1
	bl	RCC_APB1PeriphResetCmd
	mov.w	r0, #67108864
	b	.LBB83_3
.LBB83_2:
	mov.w	r0, #33554432
	movs	r1, #1
	bl	RCC_APB1PeriphResetCmd
	mov.w	r0, #33554432
.LBB83_3:
	movs	r1, #0
	bl	RCC_APB1PeriphResetCmd
	pop	{r7, pc}
.Ltmp83:
	.size	CAN_DeInit, .Ltmp83-CAN_DeInit

	.globl	CAN_Init
	.align	2
	.type	CAN_Init,%function
	.code	16                      @ @CAN_Init
	.thumb_func
CAN_Init:
@ BB#0:
	push.w	{r11, lr}
	ldr	r2, [r0]
	bic	r2, r2, #2
	str	r2, [r0]
	ldr	r2, [r0]
	orr	r2, r2, #1
	str	r2, [r0]
	movw	r2, #65535
.LBB84_1:                               @ =>This Inner Loop Header: Depth=1
	ldr	r3, [r0, #4]
	tst.w	r3, #1
	bne	.LBB84_3
@ BB#2:                                 @   in Loop: Header=BB84_1 Depth=1
	subs	r3, r2, #1
	cmp	r2, #0
	mov	r2, r3
	bne	.LBB84_1
.LBB84_3:                               @ %.critedge
	ldr	r2, [r0, #4]
	tst.w	r2, #1
	itt	eq
	moveq	r0, #0
	popeq.w	{r11, pc}
	ldr	r3, [r1, #8]
	ldr	r2, [r0]
	cmp	r3, #1
	ite	ne
	bicne	r2, r2, #128
	orreq	r2, r2, #128
	str	r2, [r0]
	ldr	r3, [r1, #12]
	ldr	r2, [r0]
	cmp	r3, #1
	ite	ne
	bicne	r2, r2, #64
	orreq	r2, r2, #64
	str	r2, [r0]
	ldr	r3, [r1, #16]
	ldr	r2, [r0]
	cmp	r3, #1
	ite	ne
	bicne	r2, r2, #32
	orreq	r2, r2, #32
	str	r2, [r0]
	ldr	r3, [r1, #20]
	ldr	r2, [r0]
	cmp	r3, #1
	ite	ne
	bicne	r2, r2, #16
	orreq	r2, r2, #16
	str	r2, [r0]
	ldr	r3, [r1, #24]
	ldr	r2, [r0]
	cmp	r3, #1
	ite	ne
	bicne	r2, r2, #8
	orreq	r2, r2, #8
	str	r2, [r0]
	ldr	r3, [r1, #28]
	ldr	r2, [r0]
	cmp	r3, #1
	ite	ne
	bicne	r2, r2, #4
	orreq	r2, r2, #4
	str	r2, [r0]
	ldrb	r3, [r1, #3]
	ldrb.w	r12, [r1, #2]
	ldrb	r2, [r1, #4]
	ldrb.w	lr, [r1, #5]
	ldrh	r1, [r1]
	lsls	r3, r3, #24
	subs	r1, #1
	orr.w	r3, r3, r12, lsl #30
	orr.w	r2, r3, r2, lsl #16
	orr.w	r2, r2, lr, lsl #20
	orrs	r1, r2
	str	r1, [r0, #28]
	ldr	r1, [r0]
	bic	r1, r1, #1
	str	r1, [r0]
	movw	r1, #65535
.LBB84_4:                               @ =>This Inner Loop Header: Depth=1
	ldr	r2, [r0, #4]
	tst.w	r2, #1
	beq	.LBB84_6
@ BB#5:                                 @   in Loop: Header=BB84_4 Depth=1
	subs	r2, r1, #1
	cmp	r1, #0
	mov	r1, r2
	bne	.LBB84_4
.LBB84_6:                               @ %.critedge1
	ldr	r0, [r0, #4]
	movs	r1, #1
	bic.w	r0, r1, r0
	pop.w	{r11, pc}
.Ltmp84:
	.size	CAN_Init, .Ltmp84-CAN_Init

	.globl	CAN_FilterInit
	.align	2
	.type	CAN_FilterInit,%function
	.code	16                      @ @CAN_FilterInit
	.thumb_func
CAN_FilterInit:
@ BB#0:
	push.w	{r4, r5, r11, lr}
	movw	lr, #26112
	ldrb	r1, [r0, #10]
	movw	r12, #26140
	movt	lr, #16384
	movt	r12, #16384
	ldr.w	r2, [lr]
	orr	r2, r2, #1
	str.w	r2, [lr]
	movs	r2, #1
	lsls	r2, r1
	ldr.w	r1, [r12]
	mvns	r3, r2
	bics	r1, r2
	str.w	r1, [r12]
	ldrb	r1, [r0, #12]
	cbnz	r1, .LBB85_2
@ BB#1:
	movw	r1, #26124
	movw	r5, #26176
	movt	r1, #16384
	movt	r5, #16384
	ldr	r4, [r1]
	ands	r4, r3
	str	r4, [r1]
	ldrh	r1, [r0, #6]
	ldrh	r4, [r0, #2]
	orr.w	r1, r4, r1, lsl #16
	ldrb	r4, [r0, #10]
	str.w	r1, [r5, r4, lsl #3]
	movw	r5, #26180
	ldrh	r1, [r0, #4]
	ldrh	r4, [r0]
	movt	r5, #16384
	orr.w	r1, r4, r1, lsl #16
	ldrb	r4, [r0, #10]
	str.w	r1, [r5, r4, lsl #3]
	ldrb	r1, [r0, #12]
.LBB85_2:
	cmp	r1, #1
	bne	.LBB85_4
@ BB#3:
	movw	r1, #26124
	movw	r5, #26176
	movt	r1, #16384
	movt	r5, #16384
	ldr	r4, [r1]
	orrs	r4, r2
	str	r4, [r1]
	ldrh	r1, [r0]
	ldrh	r4, [r0, #2]
	orr.w	r1, r4, r1, lsl #16
	ldrb	r4, [r0, #10]
	str.w	r1, [r5, r4, lsl #3]
	movw	r5, #26180
	ldrh	r1, [r0, #4]
	ldrh	r4, [r0, #6]
	movt	r5, #16384
	orr.w	r1, r4, r1, lsl #16
	ldrb	r4, [r0, #10]
	str.w	r1, [r5, r4, lsl #3]
.LBB85_4:
	movw	r1, #26116
	ldrb	r5, [r0, #11]
	movt	r1, #16384
	ldr	r4, [r1]
	cmp	r5, #0
	beq	.LBB85_6
@ BB#5:
	orrs	r4, r2
	b	.LBB85_7
.LBB85_6:
	ands	r4, r3
.LBB85_7:
	str	r4, [r1]
	ldrh	r1, [r0, #8]
	cbnz	r1, .LBB85_9
@ BB#8:
	movw	r1, #26132
	movt	r1, #16384
	ldr	r4, [r1]
	ands	r3, r4
	str	r3, [r1]
	ldrh	r1, [r0, #8]
.LBB85_9:
	cmp	r1, #1
	bne	.LBB85_11
@ BB#10:
	movw	r1, #26132
	movt	r1, #16384
	ldr	r3, [r1]
	orrs	r3, r2
	str	r3, [r1]
.LBB85_11:
	ldr	r0, [r0, #16]
	cmp	r0, #1
	ittt	eq
	ldreq.w	r0, [r12]
	orreq	r0, r2
	streq.w	r0, [r12]
	ldr.w	r0, [lr]
	bic	r0, r0, #1
	str.w	r0, [lr]
	pop.w	{r4, r5, r11, pc}
.Ltmp85:
	.size	CAN_FilterInit, .Ltmp85-CAN_FilterInit

	.globl	CAN_StructInit
	.align	2
	.type	CAN_StructInit,%function
	.code	16                      @ @CAN_StructInit
	.thumb_func
CAN_StructInit:
@ BB#0:
	movs	r1, #0
	str	r1, [r0, #8]
	str	r1, [r0, #12]
	str	r1, [r0, #16]
	str	r1, [r0, #20]
	str	r1, [r0, #24]
	str	r1, [r0, #28]
	strb	r1, [r0, #2]
	strb	r1, [r0, #3]
	movs	r1, #3
	strb	r1, [r0, #4]
	movs	r1, #2
	strb	r1, [r0, #5]
	movs	r1, #1
	strh	r1, [r0]
	bx	lr
.Ltmp86:
	.size	CAN_StructInit, .Ltmp86-CAN_StructInit

	.globl	CAN_SlaveStartBank
	.align	2
	.type	CAN_SlaveStartBank,%function
	.code	16                      @ @CAN_SlaveStartBank
	.thumb_func
CAN_SlaveStartBank:
@ BB#0:
	movw	r1, #26112
	movw	r3, #49393
	movt	r1, #16384
	movt	r3, #65535
	ldr	r2, [r1]
	orr	r2, r2, #1
	str	r2, [r1]
	ldr	r2, [r1]
	ands	r2, r3
	str	r2, [r1]
	ldr	r2, [r1]
	orr.w	r0, r2, r0, lsl #8
	str	r0, [r1]
	ldr	r0, [r1]
	bic	r0, r0, #1
	str	r0, [r1]
	bx	lr
.Ltmp87:
	.size	CAN_SlaveStartBank, .Ltmp87-CAN_SlaveStartBank

	.globl	CAN_DBGFreeze
	.align	2
	.type	CAN_DBGFreeze,%function
	.code	16                      @ @CAN_DBGFreeze
	.thumb_func
CAN_DBGFreeze:
@ BB#0:
	ldr	r2, [r0]
	cmp	r1, #0
	ite	eq
	biceq	r1, r2, #65536
	orrne	r1, r2, #65536
	str	r1, [r0]
	bx	lr
.Ltmp88:
	.size	CAN_DBGFreeze, .Ltmp88-CAN_DBGFreeze

	.globl	CAN_TTComModeCmd
	.align	2
	.type	CAN_TTComModeCmd,%function
	.code	16                      @ @CAN_TTComModeCmd
	.thumb_func
CAN_TTComModeCmd:
@ BB#0:
	ldr	r2, [r0]
	cbz	r1, .LBB89_2
@ BB#1:
	orr	r1, r2, #128
	str	r1, [r0]
	ldr.w	r1, [r0, #388]
	orr	r1, r1, #256
	str.w	r1, [r0, #388]
	ldr.w	r1, [r0, #404]
	orr	r1, r1, #256
	str.w	r1, [r0, #404]
	ldr.w	r1, [r0, #420]
	orr	r1, r1, #256
	str.w	r1, [r0, #420]
	bx	lr
.LBB89_2:
	bic	r1, r2, #128
	str	r1, [r0]
	ldr.w	r1, [r0, #388]
	bic	r1, r1, #256
	str.w	r1, [r0, #388]
	ldr.w	r1, [r0, #404]
	bic	r1, r1, #256
	str.w	r1, [r0, #404]
	ldr.w	r1, [r0, #420]
	bic	r1, r1, #256
	str.w	r1, [r0, #420]
	bx	lr
.Ltmp89:
	.size	CAN_TTComModeCmd, .Ltmp89-CAN_TTComModeCmd

	.globl	CAN_Transmit
	.align	2
	.type	CAN_Transmit,%function
	.code	16                      @ @CAN_Transmit
	.thumb_func
CAN_Transmit:
@ BB#0:
	push.w	{r4, r5, r11, lr}
	ldr	r2, [r0, #8]
	tst.w	r2, #67108864
	beq	.LBB90_2
@ BB#1:
	mov.w	r12, #0
	b	.LBB90_5
.LBB90_2:
	ldr	r2, [r0, #8]
	tst.w	r2, #134217728
	beq	.LBB90_4
@ BB#3:
	mov.w	r12, #1
	b	.LBB90_5
.LBB90_4:
	ldr	r2, [r0, #8]
	tst.w	r2, #268435456
	ittt	eq
	moveq.w	r12, #4
	uxtbeq.w	r0, r12
	popeq.w	{r4, r5, r11, pc}
	mov.w	r12, #2
.LBB90_5:
	uxtb.w	r2, r12
	add.w	r0, r0, r2, lsl #4
	ldr.w	r2, [r0, #384]
	add.w	r3, r0, #384
	and	r2, r2, #1
	str.w	r2, [r0, #384]
	ldrb	r2, [r1, #8]
	ldrb.w	lr, [r1, #9]
	cmp	r2, #0
	beq	.LBB90_7
@ BB#6:
	ldr	r4, [r1, #4]
	orr.w	r2, r2, r4, lsl #3
	ldr	r4, [r3]
	orr.w	r2, r2, lr
	orrs	r2, r4
	b	.LBB90_8
.LBB90_7:
	ldr	r2, [r1]
	orr.w	lr, lr, r2, lsl #21
	ldr	r2, [r3]
	orr.w	r2, r2, lr
.LBB90_8:
	str	r2, [r3]
	ldrb	r2, [r1, #10]
	and	r2, r2, #15
	strb	r2, [r1, #10]
	ldr.w	r2, [r0, #388]
	bic	r2, r2, #15
	str.w	r2, [r0, #388]
	ldrb	r2, [r1, #10]
	ldr.w	r4, [r0, #388]
	orrs	r2, r4
	str.w	r2, [r0, #388]
	ldrb	r2, [r1, #13]
	ldrb	r5, [r1, #14]
	ldrb	r4, [r1, #12]
	ldrb.w	lr, [r1, #11]
	lsls	r2, r2, #16
	orr.w	r2, r2, r5, lsl #24
	orr.w	r2, r2, r4, lsl #8
	orr.w	r2, r2, lr
	str.w	r2, [r0, #392]
	ldrb	r4, [r1, #17]
	ldrb	r2, [r1, #15]
	ldrb	r5, [r1, #16]
	ldrb	r1, [r1, #18]
	lsls	r4, r4, #16
	orr.w	r1, r4, r1, lsl #24
	orr.w	r1, r1, r5, lsl #8
	orrs	r1, r2
	str.w	r1, [r0, #396]
	ldr	r0, [r3]
	orr	r0, r0, #1
	str	r0, [r3]
	uxtb.w	r0, r12
	pop.w	{r4, r5, r11, pc}
.Ltmp90:
	.size	CAN_Transmit, .Ltmp90-CAN_Transmit

	.globl	CAN_TransmitStatus
	.align	2
	.type	CAN_TransmitStatus,%function
	.code	16                      @ @CAN_TransmitStatus
	.thumb_func
CAN_TransmitStatus:
@ BB#0:
	cmp	r1, #2
	beq	.LBB91_3
@ BB#1:
	cmp	r1, #1
	bne	.LBB91_4
@ BB#2:
	ldr	r0, [r0, #8]
	movw	r1, #768
	movt	r1, #2048
	b	.LBB91_6
.LBB91_3:
	ldr	r0, [r0, #8]
	movs	r1, #0
	movt	r1, #4099
	b	.LBB91_6
.LBB91_4:
	cbnz	r1, .LBB91_8
@ BB#5:
	ldr	r0, [r0, #8]
	movs	r1, #3
	movt	r1, #1024
.LBB91_6:
	ands	r0, r1
	cmp.w	r0, #67108864
	bgt	.LBB91_9
@ BB#7:
	cbnz	r0, .LBB91_19
.LBB91_8:
	movs	r0, #2
	uxtb	r0, r0
	bx	lr
.LBB91_9:
	movs	r1, #255
	movt	r1, #2048
	cmp	r0, r1
	bgt	.LBB91_12
@ BB#10:
	movs	r1, #1
	movt	r1, #1024
	cmp	r0, r1
	beq	.LBB91_19
@ BB#11:
	movs	r1, #3
	movt	r1, #1024
	b	.LBB91_17
.LBB91_12:
	movw	r1, #65535
	movt	r1, #4098
	cmp	r0, r1
	bgt	.LBB91_16
@ BB#13:
	movw	r1, #256
	movt	r1, #2048
	cmp	r0, r1
	beq	.LBB91_19
@ BB#14:
	movw	r1, #768
	movt	r1, #2048
	cmp	r0, r1
	beq	.LBB91_18
@ BB#15:
	movs	r1, #0
	movt	r1, #4097
	cmp	r0, r1
	b	.LBB91_19
.LBB91_16:
	movs	r1, #0
	movt	r1, #4099
.LBB91_17:
	cmp	r0, r1
	bne	.LBB91_19
.LBB91_18:
	movs	r0, #1
	uxtb	r0, r0
	bx	lr
.LBB91_19:
	movs	r0, #0
	uxtb	r0, r0
	bx	lr
.Ltmp91:
	.size	CAN_TransmitStatus, .Ltmp91-CAN_TransmitStatus

	.globl	CAN_CancelTransmit
	.align	2
	.type	CAN_CancelTransmit,%function
	.code	16                      @ @CAN_CancelTransmit
	.thumb_func
CAN_CancelTransmit:
@ BB#0:
	cmp	r1, #2
	beq	.LBB92_3
@ BB#1:
	cmp	r1, #1
	bne	.LBB92_4
@ BB#2:
	ldr	r1, [r0, #8]
	orr	r1, r1, #32768
	b	.LBB92_5
.LBB92_3:
	ldr	r1, [r0, #8]
	orr	r1, r1, #8388608
	b	.LBB92_5
.LBB92_4:
	cmp	r1, #0
	it	ne
	bxne	lr
	ldr	r1, [r0, #8]
	orr	r1, r1, #128
.LBB92_5:
	str	r1, [r0, #8]
	bx	lr
.Ltmp92:
	.size	CAN_CancelTransmit, .Ltmp92-CAN_CancelTransmit

	.globl	CAN_Receive
	.align	2
	.type	CAN_Receive,%function
	.code	16                      @ @CAN_Receive
	.thumb_func
CAN_Receive:
@ BB#0:
	push	{r4, lr}
	add.w	r4, r0, r1, lsl #4
	ldr.w	r3, [r4, #432]
	add.w	r12, r4, #432
	ands	r3, r3, #4
	strb	r3, [r2, #8]
	ldr.w	lr, [r4, #432]
	beq	.LBB93_2
@ BB#1:
	lsr.w	r3, lr, #3
	str	r3, [r2, #4]
	b	.LBB93_3
.LBB93_2:
	lsr.w	r3, lr, #21
	str	r3, [r2]
.LBB93_3:
	ldr.w	r3, [r12]
	cmp	r1, #0
	and	r3, r3, #2
	strb	r3, [r2, #9]
	ldr.w	r3, [r4, #436]
	and	r3, r3, #15
	strb	r3, [r2, #10]
	ldr.w	r3, [r4, #436]
	lsr.w	r3, r3, #8
	strb	r3, [r2, #19]
	ldr.w	r3, [r4, #440]
	strb	r3, [r2, #11]
	ldr.w	r3, [r4, #440]
	lsr.w	r3, r3, #8
	strb	r3, [r2, #12]
	ldr.w	r3, [r4, #440]
	lsr.w	r3, r3, #16
	strb	r3, [r2, #13]
	ldr.w	r3, [r4, #440]
	lsr.w	r3, r3, #24
	strb	r3, [r2, #14]
	ldr.w	r3, [r4, #444]
	strb	r3, [r2, #15]
	ldr.w	r3, [r4, #444]
	lsr.w	r3, r3, #8
	strb	r3, [r2, #16]
	ldr.w	r3, [r4, #444]
	lsr.w	r3, r3, #16
	strb	r3, [r2, #17]
	ldr.w	r3, [r4, #444]
	lsr.w	r3, r3, #24
	strb	r3, [r2, #18]
	itttt	ne
	ldrne	r1, [r0, #16]
	orrne	r1, r1, #32
	strne	r1, [r0, #16]
	popne	{r4, pc}
	ldr	r1, [r0, #12]
	orr	r1, r1, #32
	str	r1, [r0, #12]
	pop	{r4, pc}
.Ltmp93:
	.size	CAN_Receive, .Ltmp93-CAN_Receive

	.globl	CAN_FIFORelease
	.align	2
	.type	CAN_FIFORelease,%function
	.code	16                      @ @CAN_FIFORelease
	.thumb_func
CAN_FIFORelease:
@ BB#0:
	cmp	r1, #0
	itttt	ne
	ldrne	r1, [r0, #16]
	orrne	r1, r1, #32
	strne	r1, [r0, #16]
	bxne	lr
	ldr	r1, [r0, #12]
	orr	r1, r1, #32
	str	r1, [r0, #12]
	bx	lr
.Ltmp94:
	.size	CAN_FIFORelease, .Ltmp94-CAN_FIFORelease

	.globl	CAN_MessagePending
	.align	2
	.type	CAN_MessagePending,%function
	.code	16                      @ @CAN_MessagePending
	.thumb_func
CAN_MessagePending:
@ BB#0:
	cmp	r1, #1
	bne	.LBB95_2
@ BB#1:
	ldr	r0, [r0, #16]
	b	.LBB95_3
.LBB95_2:
	cmp	r1, #0
	ittt	ne
	movne	r0, #0
	uxtbne	r0, r0
	bxne	lr
	ldr	r0, [r0, #12]
.LBB95_3:
	and	r0, r0, #3
	uxtb	r0, r0
	bx	lr
.Ltmp95:
	.size	CAN_MessagePending, .Ltmp95-CAN_MessagePending

	.globl	CAN_OperatingModeRequest
	.align	2
	.type	CAN_OperatingModeRequest,%function
	.code	16                      @ @CAN_OperatingModeRequest
	.thumb_func
CAN_OperatingModeRequest:
@ BB#0:
	cmp	r1, #2
	beq	.LBB96_6
@ BB#1:
	cmp	r1, #1
	bne	.LBB96_10
@ BB#2:
	ldr	r1, [r0]
	bic	r1, r1, #3
	str	r1, [r0]
	movs	r1, #1
	movt	r1, #65535
.LBB96_3:                               @ =>This Inner Loop Header: Depth=1
	ldr	r2, [r0, #4]
	tst.w	r2, #3
	beq	.LBB96_5
@ BB#4:                                 @   in Loop: Header=BB96_3 Depth=1
	adds	r2, r1, #1
	cmp	r1, #0
	mov	r1, r2
	bne	.LBB96_3
.LBB96_5:                               @ %.critedge1
	ldr	r1, [r0, #4]
	movs	r0, #0
	tst.w	r1, #3
	it	eq
	moveq	r0, #1
	bx	lr
.LBB96_6:
	ldr	r1, [r0]
	movs	r2, #2
	bfi	r1, r2, #0, #2
	str	r1, [r0]
	movs	r1, #1
	movt	r1, #65535
.LBB96_7:                               @ =>This Inner Loop Header: Depth=1
	ldr	r2, [r0, #4]
	and	r2, r2, #3
	cmp	r2, #2
	beq	.LBB96_9
@ BB#8:                                 @   in Loop: Header=BB96_7 Depth=1
	adds	r2, r1, #1
	cmp	r1, #0
	mov	r1, r2
	bne	.LBB96_7
.LBB96_9:                               @ %.critedge2
	ldr	r0, [r0, #4]
	and	r1, r0, #3
	movs	r0, #0
	cmp	r1, #2
	it	eq
	moveq	r0, #1
	bx	lr
.LBB96_10:
	cmp	r1, #0
	itt	ne
	movne	r0, #0
	bxne	lr
	ldr	r1, [r0]
	movs	r2, #1
	bfi	r1, r2, #0, #2
	str	r1, [r0]
	movs	r1, #1
	movt	r1, #65535
.LBB96_11:                              @ =>This Inner Loop Header: Depth=1
	ldr	r2, [r0, #4]
	and	r2, r2, #3
	cmp	r2, #1
	beq	.LBB96_13
@ BB#12:                                @   in Loop: Header=BB96_11 Depth=1
	adds	r2, r1, #1
	cmp	r1, #0
	mov	r1, r2
	bne	.LBB96_11
.LBB96_13:                              @ %.critedge
	ldr	r0, [r0, #4]
	and	r0, r0, #3
	cmp	r0, #1
	it	ne
	movne	r0, #0
	bx	lr
.Ltmp96:
	.size	CAN_OperatingModeRequest, .Ltmp96-CAN_OperatingModeRequest

	.globl	CAN_Sleep
	.align	2
	.type	CAN_Sleep,%function
	.code	16                      @ @CAN_Sleep
	.thumb_func
CAN_Sleep:
@ BB#0:
	ldr	r1, [r0]
	movs	r2, #2
	bfi	r1, r2, #0, #2
	str	r1, [r0]
	ldr	r0, [r0, #4]
	and	r1, r0, #3
	movs	r0, #0
	cmp	r1, #2
	it	eq
	moveq	r0, #1
	bx	lr
.Ltmp97:
	.size	CAN_Sleep, .Ltmp97-CAN_Sleep

	.globl	CAN_WakeUp
	.align	2
	.type	CAN_WakeUp,%function
	.code	16                      @ @CAN_WakeUp
	.thumb_func
CAN_WakeUp:
@ BB#0:
	ldr	r1, [r0]
	bic	r1, r1, #2
	str	r1, [r0]
	movs	r1, #1
	movt	r1, #65535
.LBB98_1:                               @ =>This Inner Loop Header: Depth=1
	ldr	r2, [r0, #4]
	tst.w	r2, #2
	beq	.LBB98_3
@ BB#2:                                 @   in Loop: Header=BB98_1 Depth=1
	adds	r2, r1, #1
	cmp	r1, #0
	mov	r1, r2
	bne	.LBB98_1
.LBB98_3:                               @ %.critedge
	ldr	r0, [r0, #4]
	movs	r1, #1
	bic.w	r0, r1, r0, lsr #1
	bx	lr
.Ltmp98:
	.size	CAN_WakeUp, .Ltmp98-CAN_WakeUp

	.globl	CAN_GetLastErrorCode
	.align	2
	.type	CAN_GetLastErrorCode,%function
	.code	16                      @ @CAN_GetLastErrorCode
	.thumb_func
CAN_GetLastErrorCode:
@ BB#0:
	ldr	r0, [r0, #24]
	and	r0, r0, #112
	bx	lr
.Ltmp99:
	.size	CAN_GetLastErrorCode, .Ltmp99-CAN_GetLastErrorCode

	.globl	CAN_GetReceiveErrorCounter
	.align	2
	.type	CAN_GetReceiveErrorCounter,%function
	.code	16                      @ @CAN_GetReceiveErrorCounter
	.thumb_func
CAN_GetReceiveErrorCounter:
@ BB#0:
	ldr	r0, [r0, #24]
	lsrs	r0, r0, #24
	bx	lr
.Ltmp100:
	.size	CAN_GetReceiveErrorCounter, .Ltmp100-CAN_GetReceiveErrorCounter

	.globl	CAN_GetLSBTransmitErrorCounter
	.align	2
	.type	CAN_GetLSBTransmitErrorCounter,%function
	.code	16                      @ @CAN_GetLSBTransmitErrorCounter
	.thumb_func
CAN_GetLSBTransmitErrorCounter:
@ BB#0:
	ldr	r0, [r0, #24]
	ubfx	r0, r0, #16, #8
	bx	lr
.Ltmp101:
	.size	CAN_GetLSBTransmitErrorCounter, .Ltmp101-CAN_GetLSBTransmitErrorCounter

	.globl	CAN_ITConfig
	.align	2
	.type	CAN_ITConfig,%function
	.code	16                      @ @CAN_ITConfig
	.thumb_func
CAN_ITConfig:
@ BB#0:
	cmp	r2, #0
	ldr	r2, [r0, #20]
	ite	eq
	biceq.w	r1, r2, r1
	orrne	r1, r2
	str	r1, [r0, #20]
	bx	lr
.Ltmp102:
	.size	CAN_ITConfig, .Ltmp102-CAN_ITConfig

	.globl	CAN_GetFlagStatus
	.align	2
	.type	CAN_GetFlagStatus,%function
	.code	16                      @ @CAN_GetFlagStatus
	.thumb_func
CAN_GetFlagStatus:
@ BB#0:
	tst.w	r1, #15728640
	beq	.LBB103_2
@ BB#1:
	ldr	r0, [r0, #24]
	b	.LBB103_7
.LBB103_2:
	tst.w	r1, #16777216
	beq	.LBB103_4
@ BB#3:
	ldr	r0, [r0, #4]
	b	.LBB103_7
.LBB103_4:
	tst.w	r1, #134217728
	beq	.LBB103_6
@ BB#5:
	ldr	r0, [r0, #8]
	b	.LBB103_7
.LBB103_6:
	tst.w	r1, #33554432
	ite	eq
	ldreq	r0, [r0, #16]
	ldrne	r0, [r0, #12]
.LBB103_7:
	ands	r0, r1
	bfc	r0, #20, #12
	cmp	r0, #0
	it	ne
	movne	r0, #1
	bx	lr
.Ltmp103:
	.size	CAN_GetFlagStatus, .Ltmp103-CAN_GetFlagStatus

	.globl	CAN_ClearFlag
	.align	2
	.type	CAN_ClearFlag,%function
	.code	16                      @ @CAN_ClearFlag
	.thumb_func
CAN_ClearFlag:
@ BB#0:
	movs	r2, #112
	movt	r2, #12528
	cmp	r1, r2
	bne	.LBB104_2
@ BB#1:
	movs	r1, #0
	str	r1, [r0, #24]
	bx	lr
.LBB104_2:
	mov	r2, r1
	tst.w	r1, #33554432
	bfc	r2, #20, #12
	itt	ne
	strne	r2, [r0, #12]
	bxne	lr
	tst.w	r1, #67108864
	beq	.LBB104_4
@ BB#3:
	str	r2, [r0, #16]
	bx	lr
.LBB104_4:
	tst.w	r1, #134217728
	ite	ne
	strne	r2, [r0, #8]
	streq	r2, [r0, #4]
	bx	lr
.Ltmp104:
	.size	CAN_ClearFlag, .Ltmp104-CAN_ClearFlag

	.globl	CAN_GetITStatus
	.align	2
	.type	CAN_GetITStatus,%function
	.code	16                      @ @CAN_GetITStatus
	.thumb_func
CAN_GetITStatus:
@ BB#0:
	mov	r2, r0
	ldr	r0, [r2, #20]
	tst	r0, r1
	itt	eq
	moveq	r0, #0
	bxeq	lr
	movs	r0, #0
	cmp.w	r1, #131072
	bge	.LBB105_13
@ BB#1:
	cmp.w	r1, #65536
	bge	.LBB105_14
@ BB#2:
	cmp.w	r1, #32768
	bge	.LBB105_15
@ BB#3:
	cmp.w	r1, #2048
	bge	.LBB105_17
@ BB#4:
	cmp.w	r1, #1024
	bge	.LBB105_19
@ BB#5:
	cmp.w	r1, #512
	bge	.LBB105_21
@ BB#6:
	cmp	r1, #255
	bgt	.LBB105_22
@ BB#7:
	cmp	r1, #63
	bgt	.LBB105_23
@ BB#8:
	cmp	r1, #31
	bgt	.LBB105_24
@ BB#9:
	cmp	r1, #15
	bgt	.LBB105_25
@ BB#10:
	subs	r1, #1
	cmp	r1, #7
	bhi	.LBB105_27
@ BB#11:
	tbb	[pc, r1]
.LJTI105_0_0:
	.byte	(.LBB105_12-.LJTI105_0_0)/2
	.byte	(.LBB105_28-.LJTI105_0_0)/2
	.byte	(.LBB105_27-.LJTI105_0_0)/2
	.byte	(.LBB105_30-.LJTI105_0_0)/2
	.byte	(.LBB105_27-.LJTI105_0_0)/2
	.byte	(.LBB105_27-.LJTI105_0_0)/2
	.byte	(.LBB105_27-.LJTI105_0_0)/2
	.byte	(.LBB105_31-.LJTI105_0_0)/2
	.align	1
.LBB105_12:
	ldr	r0, [r2, #8]
	movw	r1, #257
	movt	r1, #1
	ands	r0, r1
	it	ne
	movne	r0, #1
	bx	lr
.LBB105_13:
	ittt	eq
	ldreq	r0, [r2, #4]
	ubfxeq	r0, r0, #4, #1
	bxeq	lr
	b	.LBB105_27
.LBB105_14:
	ittt	eq
	ldreq	r0, [r2, #4]
	ubfxeq	r0, r0, #3, #1
	bxeq	lr
	b	.LBB105_27
.LBB105_15:
	it	ne
	bxne	lr
	ldr	r0, [r2, #4]
.LBB105_16:
	ubfx	r0, r0, #2, #1
	b	.LBB105_27
.LBB105_17:
	bne	.LBB105_27
@ BB#18:
	ldr	r0, [r2, #24]
	ands	r0, r0, #112
	it	ne
	movne	r0, #1
	bx	lr
.LBB105_19:
	bne	.LBB105_27
@ BB#20:
	ldr	r0, [r2, #24]
	b	.LBB105_16
.LBB105_21:
	ittt	eq
	ldreq	r0, [r2, #24]
	ubfxeq	r0, r0, #1, #1
	bxeq	lr
	b	.LBB105_27
.LBB105_22:
	cmp.w	r1, #256
	ittt	eq
	ldreq	r0, [r2, #24]
	andeq	r0, r0, #1
	bxeq	lr
	b	.LBB105_27
.LBB105_23:
	cmp	r1, #64
	ittt	eq
	ldreq	r0, [r2, #16]
	ubfxeq	r0, r0, #4, #1
	bxeq	lr
	b	.LBB105_27
.LBB105_24:
	cmp	r1, #32
	ittt	eq
	ldreq	r0, [r2, #16]
	ubfxeq	r0, r0, #3, #1
	bxeq	lr
	b	.LBB105_27
.LBB105_25:
	cmp	r1, #16
	bne	.LBB105_27
@ BB#26:
	ldr	r0, [r2, #16]
	b	.LBB105_29
.LBB105_27:
	bx	lr
.LBB105_28:
	ldr	r0, [r2, #12]
.LBB105_29:
	ands	r0, r0, #3
	it	ne
	movne	r0, #1
	bx	lr
.LBB105_30:
	ldr	r0, [r2, #12]
	ubfx	r0, r0, #3, #1
	bx	lr
.LBB105_31:
	ldr	r0, [r2, #12]
	ubfx	r0, r0, #4, #1
	bx	lr
.Ltmp105:
	.size	CAN_GetITStatus, .Ltmp105-CAN_GetITStatus

	.globl	CAN_ClearITPendingBit
	.align	2
	.type	CAN_ClearITPendingBit,%function
	.code	16                      @ @CAN_ClearITPendingBit
	.thumb_func
CAN_ClearITPendingBit:
@ BB#0:
	cmp.w	r1, #131072
	bge	.LBB106_10
@ BB#1:
	cmp.w	r1, #65536
	bge	.LBB106_12
@ BB#2:
	cmp.w	r1, #32768
	bge	.LBB106_14
@ BB#3:
	cmp.w	r1, #2048
	bge	.LBB106_15
@ BB#4:
	cmp.w	r1, #1024
	it	lt
	cmplt.w	r1, #512
	bge	.LBB106_21
@ BB#5:
	cmp	r1, #255
	bgt	.LBB106_20
@ BB#6:
	cmp	r1, #63
	bgt	.LBB106_22
@ BB#7:
	cmp	r1, #31
	bgt	.LBB106_23
@ BB#8:
	cmp	r1, #1
	beq	.LBB106_24
@ BB#9:
	cmp	r1, #4
	ittt	eq
	moveq	r1, #8
	streq	r1, [r0, #12]
	bxeq	lr
	cmp	r1, #8
	ittt	eq
	moveq	r1, #16
	streq	r1, [r0, #12]
	bxeq	lr
	b	.LBB106_19
.LBB106_10:
	bne	.LBB106_19
@ BB#11:
	movs	r1, #16
	b	.LBB106_18
.LBB106_12:
	bne	.LBB106_19
@ BB#13:
	movs	r1, #8
	b	.LBB106_18
.LBB106_14:
	beq	.LBB106_16
	b	.LBB106_19
.LBB106_15:
	it	ne
	bxne	lr
.LBB106_16:
	movs	r1, #0
	str	r1, [r0, #24]
.LBB106_17:
	movs	r1, #4
.LBB106_18:
	str	r1, [r0, #4]
.LBB106_19:
	bx	lr
.LBB106_20:
	cmp.w	r1, #256
.LBB106_21:
	beq	.LBB106_17
	b	.LBB106_19
.LBB106_22:
	cmp	r1, #64
	ittt	eq
	moveq	r1, #16
	streq	r1, [r0, #16]
	bxeq	lr
	b	.LBB106_19
.LBB106_23:
	cmp	r1, #32
	ittt	eq
	moveq	r1, #8
	streq	r1, [r0, #16]
	bxeq	lr
	b	.LBB106_19
.LBB106_24:
	movw	r1, #257
	movt	r1, #1
	str	r1, [r0, #8]
	bx	lr
.Ltmp106:
	.size	CAN_ClearITPendingBit, .Ltmp106-CAN_ClearITPendingBit

	.globl	CRC_ResetDR
	.align	2
	.type	CRC_ResetDR,%function
	.code	16                      @ @CRC_ResetDR
	.thumb_func
CRC_ResetDR:
@ BB#0:
	movw	r0, #12296
	movs	r1, #1
	movt	r0, #16386
	str	r1, [r0]
	bx	lr
.Ltmp107:
	.size	CRC_ResetDR, .Ltmp107-CRC_ResetDR

	.globl	CRC_CalcCRC
	.align	2
	.type	CRC_CalcCRC,%function
	.code	16                      @ @CRC_CalcCRC
	.thumb_func
CRC_CalcCRC:
@ BB#0:
	movw	r1, #12288
	movt	r1, #16386
	str	r0, [r1]
	ldr	r0, [r1]
	bx	lr
.Ltmp108:
	.size	CRC_CalcCRC, .Ltmp108-CRC_CalcCRC

	.globl	CRC_CalcBlockCRC
	.align	2
	.type	CRC_CalcBlockCRC,%function
	.code	16                      @ @CRC_CalcBlockCRC
	.thumb_func
CRC_CalcBlockCRC:
@ BB#0:
	cbz	r1, .LBB109_3
@ BB#1:
	movw	r2, #12288
	movt	r2, #16386
.LBB109_2:                              @ %.lr.ph
                                        @ =>This Inner Loop Header: Depth=1
	ldr	r3, [r0], #4
	subs	r1, #1
	str	r3, [r2]
	bne	.LBB109_2
.LBB109_3:                              @ %._crit_edge
	movw	r0, #12288
	movt	r0, #16386
	ldr	r0, [r0]
	bx	lr
.Ltmp109:
	.size	CRC_CalcBlockCRC, .Ltmp109-CRC_CalcBlockCRC

	.globl	CRC_GetCRC
	.align	2
	.type	CRC_GetCRC,%function
	.code	16                      @ @CRC_GetCRC
	.thumb_func
CRC_GetCRC:
@ BB#0:
	movw	r0, #12288
	movt	r0, #16386
	ldr	r0, [r0]
	bx	lr
.Ltmp110:
	.size	CRC_GetCRC, .Ltmp110-CRC_GetCRC

	.globl	CRC_SetIDRegister
	.align	2
	.type	CRC_SetIDRegister,%function
	.code	16                      @ @CRC_SetIDRegister
	.thumb_func
CRC_SetIDRegister:
@ BB#0:
	movw	r1, #12292
	movt	r1, #16386
	strb	r0, [r1]
	bx	lr
.Ltmp111:
	.size	CRC_SetIDRegister, .Ltmp111-CRC_SetIDRegister

	.globl	CRC_GetIDRegister
	.align	2
	.type	CRC_GetIDRegister,%function
	.code	16                      @ @CRC_GetIDRegister
	.thumb_func
CRC_GetIDRegister:
@ BB#0:
	movw	r0, #12292
	movt	r0, #16386
	ldrb	r0, [r0]
	bx	lr
.Ltmp112:
	.size	CRC_GetIDRegister, .Ltmp112-CRC_GetIDRegister

	.globl	CRYP_DeInit
	.align	2
	.type	CRYP_DeInit,%function
	.code	16                      @ @CRYP_DeInit
	.thumb_func
CRYP_DeInit:
@ BB#0:
	push	{r7, lr}
	movs	r0, #16
	movs	r1, #1
	mov	r7, sp
	bl	RCC_AHB2PeriphResetCmd
	movs	r0, #16
	movs	r1, #0
	bl	RCC_AHB2PeriphResetCmd
	pop	{r7, pc}
.Ltmp113:
	.size	CRYP_DeInit, .Ltmp113-CRYP_DeInit

	.globl	CRYP_Init
	.align	2
	.type	CRYP_Init,%function
	.code	16                      @ @CRYP_Init
	.thumb_func
CRYP_Init:
@ BB#0:
	movs	r1, #0
	movt	r1, #20486
	ldr	r2, [r1]
	bic	r2, r2, #56
	str	r2, [r1]
	ldrh	r2, [r0, #2]
	ldr	r3, [r1]
	orrs	r2, r3
	str	r2, [r1]
	ldr	r2, [r1]
	bic	r2, r2, #192
	str	r2, [r1]
	ldrh	r2, [r0, #4]
	ldr	r3, [r1]
	orrs	r2, r3
	str	r2, [r1]
	ldrh	r2, [r0, #2]
	subs	r2, #32
	uxth	r2, r2
	cmp	r2, #24
	bhi	.LBB114_2
@ BB#1:
	movs	r3, #1
	lsl.w	r2, r3, r2
	tst.w	r2, #16843009
	itttt	ne
	ldrne	r2, [r1]
	bicne	r2, r2, #768
	strne	r2, [r1]
	ldrhne	r2, [r0, #6]
	ittt	ne
	ldrne	r3, [r1]
	orrne	r2, r3
	strne	r2, [r1]
.LBB114_2:
	ldr	r2, [r1]
	bic	r2, r2, #4
	str	r2, [r1]
	ldrh	r0, [r0]
	ldr	r2, [r1]
	orrs	r0, r2
	str	r0, [r1]
	bx	lr
.Ltmp114:
	.size	CRYP_Init, .Ltmp114-CRYP_Init

	.globl	CRYP_StructInit
	.align	2
	.type	CRYP_StructInit,%function
	.code	16                      @ @CRYP_StructInit
	.thumb_func
CRYP_StructInit:
@ BB#0:
	movs	r1, #0
	strh	r1, [r0, #2]
	strh	r1, [r0]
	strh	r1, [r0, #6]
	strh	r1, [r0, #4]
	bx	lr
.Ltmp115:
	.size	CRYP_StructInit, .Ltmp115-CRYP_StructInit

	.globl	CRYP_KeyInit
	.align	2
	.type	CRYP_KeyInit,%function
	.code	16                      @ @CRYP_KeyInit
	.thumb_func
CRYP_KeyInit:
@ BB#0:
	ldr	r1, [r0]
	movs	r2, #32
	movt	r2, #20486
	str	r1, [r2]
	movs	r2, #36
	ldr	r1, [r0, #4]
	movt	r2, #20486
	str	r1, [r2]
	movs	r2, #40
	ldr	r1, [r0, #8]
	movt	r2, #20486
	str	r1, [r2]
	movs	r2, #44
	ldr	r1, [r0, #12]
	movt	r2, #20486
	str	r1, [r2]
	movs	r2, #48
	ldr	r1, [r0, #16]
	movt	r2, #20486
	str	r1, [r2]
	movs	r2, #52
	ldr	r1, [r0, #20]
	movt	r2, #20486
	str	r1, [r2]
	movs	r2, #56
	ldr	r1, [r0, #24]
	movt	r2, #20486
	str	r1, [r2]
	movs	r1, #60
	ldr	r0, [r0, #28]
	movt	r1, #20486
	str	r0, [r1]
	bx	lr
.Ltmp116:
	.size	CRYP_KeyInit, .Ltmp116-CRYP_KeyInit

	.globl	CRYP_KeyStructInit
	.align	2
	.type	CRYP_KeyStructInit,%function
	.code	16                      @ @CRYP_KeyStructInit
	.thumb_func
CRYP_KeyStructInit:
@ BB#0:
	movs	r1, #0
	str	r1, [r0]
	str	r1, [r0, #4]
	str	r1, [r0, #8]
	str	r1, [r0, #12]
	str	r1, [r0, #16]
	str	r1, [r0, #20]
	str	r1, [r0, #24]
	str	r1, [r0, #28]
	bx	lr
.Ltmp117:
	.size	CRYP_KeyStructInit, .Ltmp117-CRYP_KeyStructInit

	.globl	CRYP_IVInit
	.align	2
	.type	CRYP_IVInit,%function
	.code	16                      @ @CRYP_IVInit
	.thumb_func
CRYP_IVInit:
@ BB#0:
	ldr	r1, [r0]
	movs	r2, #64
	movt	r2, #20486
	str	r1, [r2]
	movs	r2, #68
	ldr	r1, [r0, #4]
	movt	r2, #20486
	str	r1, [r2]
	movs	r2, #72
	ldr	r1, [r0, #8]
	movt	r2, #20486
	str	r1, [r2]
	movs	r1, #76
	ldr	r0, [r0, #12]
	movt	r1, #20486
	str	r0, [r1]
	bx	lr
.Ltmp118:
	.size	CRYP_IVInit, .Ltmp118-CRYP_IVInit

	.globl	CRYP_IVStructInit
	.align	2
	.type	CRYP_IVStructInit,%function
	.code	16                      @ @CRYP_IVStructInit
	.thumb_func
CRYP_IVStructInit:
@ BB#0:
	movs	r1, #0
	str	r1, [r0]
	str	r1, [r0, #4]
	str	r1, [r0, #8]
	str	r1, [r0, #12]
	bx	lr
.Ltmp119:
	.size	CRYP_IVStructInit, .Ltmp119-CRYP_IVStructInit

	.globl	CRYP_FIFOFlush
	.align	2
	.type	CRYP_FIFOFlush,%function
	.code	16                      @ @CRYP_FIFOFlush
	.thumb_func
CRYP_FIFOFlush:
@ BB#0:
	movs	r0, #0
	movt	r0, #20486
	ldr	r1, [r0]
	orr	r1, r1, #16384
	str	r1, [r0]
	bx	lr
.Ltmp120:
	.size	CRYP_FIFOFlush, .Ltmp120-CRYP_FIFOFlush

	.globl	CRYP_Cmd
	.align	2
	.type	CRYP_Cmd,%function
	.code	16                      @ @CRYP_Cmd
	.thumb_func
CRYP_Cmd:
@ BB#0:
	movs	r1, #0
	cmp	r0, #0
	movt	r1, #20486
	ldr	r2, [r1]
	ite	eq
	biceq	r0, r2, #32768
	orrne	r0, r2, #32768
	str	r0, [r1]
	bx	lr
.Ltmp121:
	.size	CRYP_Cmd, .Ltmp121-CRYP_Cmd

	.globl	CRYP_DataIn
	.align	2
	.type	CRYP_DataIn,%function
	.code	16                      @ @CRYP_DataIn
	.thumb_func
CRYP_DataIn:
@ BB#0:
	movs	r1, #8
	movt	r1, #20486
	str	r0, [r1]
	bx	lr
.Ltmp122:
	.size	CRYP_DataIn, .Ltmp122-CRYP_DataIn

	.globl	CRYP_DataOut
	.align	2
	.type	CRYP_DataOut,%function
	.code	16                      @ @CRYP_DataOut
	.thumb_func
CRYP_DataOut:
@ BB#0:
	movs	r0, #12
	movt	r0, #20486
	ldr	r0, [r0]
	bx	lr
.Ltmp123:
	.size	CRYP_DataOut, .Ltmp123-CRYP_DataOut

	.globl	CRYP_SaveContext
	.align	2
	.type	CRYP_SaveContext,%function
	.code	16                      @ @CRYP_SaveContext
	.thumb_func
CRYP_SaveContext:
@ BB#0:
	push	{r4, r5, r6, lr}
	sub	sp, #8
	movw	lr, #16
	movs	r2, #0
	movw	r12, #0
	movs	r3, #4
	movw	r4, #65535
	str	r2, [sp, #4]
	movt	lr, #20486
	movt	r12, #20486
	ldr.w	r2, [lr]
	bic	r2, r2, #1
	str.w	r2, [lr]
	ldr.w	r2, [r12]
	and.w	r2, r3, r2, lsr #1
	eor	r3, r2, #21
	movs	r2, #4
	movt	r2, #20486
.LBB124_1:                              @ =>This Inner Loop Header: Depth=1
	ldr	r5, [r2]
	ldr	r6, [sp, #4]
	adds	r6, #1
	str	r6, [sp, #4]
	ldr	r6, [sp, #4]
	cmp	r6, r4
	itt	ne
	andne	r5, r3
	cmpne	r5, #1
	bne	.LBB124_1
@ BB#2:                                 @ %.critedge
	ldr	r2, [r2]
	ands	r2, r3
	cmp	r2, #1
	ittt	ne
	movne	r0, #0
	addne	sp, #8
	popne	{r4, r5, r6, pc}
	ldr.w	r2, [lr]
	bic	r2, r2, #2
	str.w	r2, [lr]
	ldr.w	r2, [r12]
	bic	r2, r2, #32768
	str.w	r2, [r12]
	ldr.w	r2, [r12]
	and	r2, r2, #1020
	str	r2, [r0]
	movs	r2, #64
	movt	r2, #20486
	ldr	r2, [r2]
	str	r2, [r0, #4]
	movs	r2, #68
	movt	r2, #20486
	ldr	r2, [r2]
	str	r2, [r0, #8]
	movs	r2, #72
	movt	r2, #20486
	ldr	r2, [r2]
	str	r2, [r0, #12]
	movs	r2, #76
	movt	r2, #20486
	ldr	r2, [r2]
	str	r2, [r0, #16]
	ldr	r2, [r1]
	str	r2, [r0, #20]
	ldr	r2, [r1, #4]
	str	r2, [r0, #24]
	ldr	r2, [r1, #8]
	str	r2, [r0, #28]
	ldr	r2, [r1, #12]
	str	r2, [r0, #32]
	ldr	r2, [r1, #16]
	str	r2, [r0, #36]
	ldr	r2, [r1, #20]
	str	r2, [r0, #40]
	ldr	r2, [r1, #24]
	str	r2, [r0, #44]
	ldr	r1, [r1, #28]
	str	r1, [r0, #48]
	movs	r0, #1
	add	sp, #8
	pop	{r4, r5, r6, pc}
.Ltmp124:
	.size	CRYP_SaveContext, .Ltmp124-CRYP_SaveContext

	.globl	CRYP_RestoreContext
	.align	2
	.type	CRYP_RestoreContext,%function
	.code	16                      @ @CRYP_RestoreContext
	.thumb_func
CRYP_RestoreContext:
@ BB#0:
	ldr	r1, [r0]
	movs	r2, #0
	movs	r3, #32
	movt	r2, #20486
	movt	r3, #20486
	str	r1, [r2]
	ldr	r1, [r0, #20]
	str	r1, [r3]
	movs	r3, #36
	ldr	r1, [r0, #24]
	movt	r3, #20486
	str	r1, [r3]
	movs	r3, #40
	ldr	r1, [r0, #28]
	movt	r3, #20486
	str	r1, [r3]
	movs	r3, #44
	ldr	r1, [r0, #32]
	movt	r3, #20486
	str	r1, [r3]
	movs	r3, #48
	ldr	r1, [r0, #36]
	movt	r3, #20486
	str	r1, [r3]
	movs	r3, #52
	ldr	r1, [r0, #40]
	movt	r3, #20486
	str	r1, [r3]
	movs	r3, #56
	ldr	r1, [r0, #44]
	movt	r3, #20486
	str	r1, [r3]
	movs	r3, #60
	ldr	r1, [r0, #48]
	movt	r3, #20486
	str	r1, [r3]
	movs	r3, #64
	ldr	r1, [r0, #4]
	movt	r3, #20486
	str	r1, [r3]
	movs	r3, #68
	ldr	r1, [r0, #8]
	movt	r3, #20486
	str	r1, [r3]
	movs	r3, #72
	ldr	r1, [r0, #12]
	movt	r3, #20486
	str	r1, [r3]
	movs	r1, #76
	ldr	r0, [r0, #16]
	movt	r1, #20486
	str	r0, [r1]
	ldr	r0, [r2]
	orr	r0, r0, #32768
	str	r0, [r2]
	bx	lr
.Ltmp125:
	.size	CRYP_RestoreContext, .Ltmp125-CRYP_RestoreContext

	.globl	CRYP_DMACmd
	.align	2
	.type	CRYP_DMACmd,%function
	.code	16                      @ @CRYP_DMACmd
	.thumb_func
CRYP_DMACmd:
@ BB#0:
	cbz	r1, .LBB126_2
@ BB#1:
	movs	r1, #16
	movt	r1, #20486
	ldr	r2, [r1]
	orrs	r0, r2
	str	r0, [r1]
	bx	lr
.LBB126_2:
	movs	r1, #16
	eor	r0, r0, #255
	movt	r1, #20486
	ldr	r2, [r1]
	ands	r0, r2
	str	r0, [r1]
	bx	lr
.Ltmp126:
	.size	CRYP_DMACmd, .Ltmp126-CRYP_DMACmd

	.globl	CRYP_ITConfig
	.align	2
	.type	CRYP_ITConfig,%function
	.code	16                      @ @CRYP_ITConfig
	.thumb_func
CRYP_ITConfig:
@ BB#0:
	cbz	r1, .LBB127_2
@ BB#1:
	movs	r1, #20
	movt	r1, #20486
	ldr	r2, [r1]
	orrs	r0, r2
	str	r0, [r1]
	bx	lr
.LBB127_2:
	movs	r1, #20
	eor	r0, r0, #255
	movt	r1, #20486
	ldr	r2, [r1]
	ands	r0, r2
	str	r0, [r1]
	bx	lr
.Ltmp127:
	.size	CRYP_ITConfig, .Ltmp127-CRYP_ITConfig

	.globl	CRYP_GetITStatus
	.align	2
	.type	CRYP_GetITStatus,%function
	.code	16                      @ @CRYP_GetITStatus
	.thumb_func
CRYP_GetITStatus:
@ BB#0:
	movs	r1, #28
	movt	r1, #20486
	ldr	r1, [r1]
	ands	r0, r1
	it	ne
	movne	r0, #1
	bx	lr
.Ltmp128:
	.size	CRYP_GetITStatus, .Ltmp128-CRYP_GetITStatus

	.globl	CRYP_GetFlagStatus
	.align	2
	.type	CRYP_GetFlagStatus,%function
	.code	16                      @ @CRYP_GetFlagStatus
	.thumb_func
CRYP_GetFlagStatus:
@ BB#0:
	movs	r1, #24
	tst.w	r0, #32
	movt	r1, #20486
	itt	eq
	moveq	r1, #4
	movteq	r1, #20486
	ldr	r1, [r1]
	ands	r0, r1
	it	ne
	movne	r0, #1
	bx	lr
.Ltmp129:
	.size	CRYP_GetFlagStatus, .Ltmp129-CRYP_GetFlagStatus

	.globl	CRYP_AES_ECB
	.align	2
	.type	CRYP_AES_ECB,%function
	.code	16                      @ @CRYP_AES_ECB
	.thumb_func
CRYP_AES_ECB:
@ BB#0:
	push.w	{r4, r5, r6, r7, r8, r9, r10, r11, lr}
	add	r7, sp, #12
	sub	sp, #44
	mov	r8, r0
	movs	r0, #0
	mov	r9, r3
	mov	r5, r2
	mov	r6, r1
	str	r0, [sp]
	add	r0, sp, #4
	bl	CRYP_KeyStructInit
	ldr	r4, [r7, #28]
	ldr.w	r10, [r7, #24]
	cmp.w	r5, #256
	beq	.LBB130_3
@ BB#1:
	cmp	r5, #192
	bne	.LBB130_4
@ BB#2:
	mov.w	r0, #256
	strh.w	r0, [sp, #42]
	ldr	r0, [r6]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #12]
	ldr	r0, [r6, #4]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #16]
	ldr	r0, [r6, #8]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #20]
	ldr	r0, [r6, #12]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #24]
	ldr	r0, [r6, #16]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #28]
	ldr	r0, [r6, #20]
	@APP
	rev r0, r0
	@NO_APP
	b	.LBB130_6
.LBB130_3:
	mov.w	r0, #512
	strh.w	r0, [sp, #42]
	ldr	r0, [r6]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #4]
	ldr	r0, [r6, #4]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #8]
	ldr	r0, [r6, #8]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #12]
	ldr	r0, [r6, #12]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #16]
	ldr	r0, [r6, #16]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #20]
	ldr	r0, [r6, #20]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #24]
	ldr	r0, [r6, #24]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #28]
	ldr	r0, [r6, #28]
	@APP
	rev r0, r0
	@NO_APP
	b	.LBB130_6
.LBB130_4:
	cmp	r5, #128
	bne	.LBB130_7
@ BB#5:
	movs	r0, #0
	strh.w	r0, [sp, #42]
	ldr	r0, [r6]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #20]
	ldr	r0, [r6, #4]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #24]
	ldr	r0, [r6, #8]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #28]
	ldr	r0, [r6, #12]
	@APP
	rev r0, r0
	@NO_APP
.LBB130_6:
	str	r0, [sp, #32]
.LBB130_7:
	cmp.w	r8, #0
	beq	.LBB130_9
@ BB#8:
	add	r0, sp, #4
	bl	CRYP_KeyInit
	movs	r0, #0
	strh.w	r0, [sp, #36]
	add	r0, sp, #36
	adds	r6, r0, #4
	orr	r5, r0, #2
	b	.LBB130_14
.LBB130_9:
	bl	CRYP_FIFOFlush
	movs	r0, #4
	add	r5, sp, #36
	strh.w	r0, [sp, #36]
	movs	r0, #56
	strh.w	r0, [sp, #38]
	movs	r0, #0
	strh.w	r0, [sp, #40]
	mov	r0, r5
	bl	CRYP_Init
	add	r0, sp, #4
	bl	CRYP_KeyInit
	movs	r0, #1
	bl	CRYP_Cmd
	adds	r6, r5, #4
	orr	r5, r5, #2
.LBB130_10:                             @ =>This Inner Loop Header: Depth=1
	movs	r0, #16
	bl	CRYP_GetFlagStatus
	ldr	r1, [sp]
	adds	r1, #1
	str	r1, [sp]
	ldr	r1, [sp]
	cmp.w	r1, #65536
	it	ne
	cmpne	r0, #0
	bne	.LBB130_10
@ BB#11:                                @ %.critedge
	cbz	r0, .LBB130_13
@ BB#12:
	mov.w	r11, #0
	b	.LBB130_15
.LBB130_13:
	movs	r0, #4
	strh.w	r0, [sp, #36]
.LBB130_14:
	mov.w	r11, #1
.LBB130_15:
	movs	r0, #32
	strh	r0, [r5]
	movs	r0, #128
	strh	r0, [r6]
	add	r0, sp, #36
	bl	CRYP_Init
	bl	CRYP_FIFOFlush
	movs	r0, #1
	bl	CRYP_Cmd
	cmp.w	r10, #0
	it	ne
	cmpne.w	r11, #0
	beq	.LBB130_23
@ BB#16:
	movs	r6, #0
	mov.w	r8, #0
.LBB130_17:                             @ %.lr.ph
                                        @ =>This Loop Header: Depth=1
                                        @     Child Loop BB130_18 Depth 2
	ldr.w	r0, [r9]
	bl	CRYP_DataIn
	ldr.w	r0, [r9, #4]
	bl	CRYP_DataIn
	ldr.w	r0, [r9, #8]
	bl	CRYP_DataIn
	ldr.w	r0, [r9, #12]
	bl	CRYP_DataIn
	str.w	r8, [sp]
.LBB130_18:                             @   Parent Loop BB130_17 Depth=1
                                        @ =>  This Inner Loop Header: Depth=2
	movs	r0, #16
	bl	CRYP_GetFlagStatus
	ldr	r1, [sp]
	adds	r1, #1
	str	r1, [sp]
	ldr	r1, [sp]
	cmp.w	r1, #65536
	it	ne
	cmpne	r0, #0
	bne	.LBB130_18
@ BB#19:                                @ %.critedge2
                                        @   in Loop: Header=BB130_17 Depth=1
	cmp	r0, #0
	bne	.LBB130_22
@ BB#20:                                @   in Loop: Header=BB130_17 Depth=1
	bl	CRYP_DataOut
	str	r0, [r4]
	bl	CRYP_DataOut
	str	r0, [r4, #4]
	bl	CRYP_DataOut
	str	r0, [r4, #8]
	bl	CRYP_DataOut
	adds	r6, #16
	str	r0, [r4, #12]
	cmp	r6, r10
	bhs	.LBB130_23
@ BB#21:                                @   in Loop: Header=BB130_17 Depth=1
	adds	r4, #16
	add.w	r9, r9, #16
	cmp.w	r11, #0
	bne	.LBB130_17
	b	.LBB130_23
.LBB130_22:
	mov.w	r11, #0
.LBB130_23:                             @ %.critedge1
	movs	r0, #0
	bl	CRYP_Cmd
	mov	r0, r11
	add	sp, #44
	pop.w	{r4, r5, r6, r7, r8, r9, r10, r11, pc}
.Ltmp130:
	.size	CRYP_AES_ECB, .Ltmp130-CRYP_AES_ECB

	.globl	CRYP_AES_CBC
	.align	2
	.type	CRYP_AES_CBC,%function
	.code	16                      @ @CRYP_AES_CBC
	.thumb_func
CRYP_AES_CBC:
@ BB#0:
	push.w	{r4, r5, r6, r7, r8, r9, r10, r11, lr}
	add	r7, sp, #12
	sub	sp, #60
	mov	r8, r0
	movs	r0, #0
	mov	r4, r3
	mov	r6, r2
	mov	r5, r1
	str	r0, [sp]
	add	r0, sp, #20
	bl	CRYP_KeyStructInit
	ldr.w	r9, [r7, #32]
	ldr.w	r10, [r7, #28]
	ldr.w	r11, [r7, #24]
	cmp.w	r4, #256
	beq	.LBB131_3
@ BB#1:
	cmp	r4, #192
	bne	.LBB131_4
@ BB#2:
	mov.w	r0, #256
	strh.w	r0, [sp, #58]
	ldr	r0, [r6]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #28]
	ldr	r0, [r6, #4]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #32]
	ldr	r0, [r6, #8]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #36]
	ldr	r0, [r6, #12]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #40]
	ldr	r0, [r6, #16]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #44]
	ldr	r0, [r6, #20]
	@APP
	rev r0, r0
	@NO_APP
	b	.LBB131_6
.LBB131_3:
	mov.w	r0, #512
	strh.w	r0, [sp, #58]
	ldr	r0, [r6]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #20]
	ldr	r0, [r6, #4]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #24]
	ldr	r0, [r6, #8]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #28]
	ldr	r0, [r6, #12]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #32]
	ldr	r0, [r6, #16]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #36]
	ldr	r0, [r6, #20]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #40]
	ldr	r0, [r6, #24]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #44]
	ldr	r0, [r6, #28]
	@APP
	rev r0, r0
	@NO_APP
	b	.LBB131_6
.LBB131_4:
	cmp	r4, #128
	bne	.LBB131_7
@ BB#5:
	movs	r0, #0
	strh.w	r0, [sp, #58]
	ldr	r0, [r6]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #36]
	ldr	r0, [r6, #4]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #40]
	ldr	r0, [r6, #8]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #44]
	ldr	r0, [r6, #12]
	@APP
	rev r0, r0
	@NO_APP
.LBB131_6:
	str	r0, [sp, #48]
.LBB131_7:
	ldr	r0, [r5]
	cmp.w	r8, #0
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #4]
	ldr	r0, [r5, #4]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #8]
	ldr	r0, [r5, #8]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #12]
	ldr	r0, [r5, #12]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #16]
	beq	.LBB131_9
@ BB#8:
	add	r0, sp, #20
	bl	CRYP_KeyInit
	movs	r0, #0
	strh.w	r0, [sp, #52]
	add	r0, sp, #52
	adds	r5, r0, #4
	orr	r6, r0, #2
	b	.LBB131_14
.LBB131_9:
	bl	CRYP_FIFOFlush
	movs	r0, #4
	add	r4, sp, #52
	strh.w	r0, [sp, #52]
	movs	r0, #56
	strh.w	r0, [sp, #54]
	movs	r0, #0
	strh.w	r0, [sp, #56]
	mov	r0, r4
	bl	CRYP_Init
	add	r0, sp, #20
	bl	CRYP_KeyInit
	movs	r0, #1
	bl	CRYP_Cmd
	adds	r5, r4, #4
	orr	r6, r4, #2
.LBB131_10:                             @ =>This Inner Loop Header: Depth=1
	movs	r0, #16
	bl	CRYP_GetFlagStatus
	ldr	r1, [sp]
	adds	r1, #1
	str	r1, [sp]
	ldr	r1, [sp]
	cmp.w	r1, #65536
	it	ne
	cmpne	r0, #0
	bne	.LBB131_10
@ BB#11:                                @ %.critedge
	cbz	r0, .LBB131_13
@ BB#12:
	movs	r4, #0
	b	.LBB131_15
.LBB131_13:
	movs	r0, #4
	strh.w	r0, [sp, #52]
.LBB131_14:
	movs	r4, #1
.LBB131_15:
	movs	r0, #40
	strh	r0, [r6]
	movs	r0, #128
	strh	r0, [r5]
	add	r0, sp, #52
	bl	CRYP_Init
	add	r0, sp, #4
	bl	CRYP_IVInit
	bl	CRYP_FIFOFlush
	movs	r0, #1
	bl	CRYP_Cmd
	cmp.w	r10, #0
	it	ne
	cmpne	r4, #0
	beq	.LBB131_23
@ BB#16:
	movs	r5, #0
	movs	r6, #0
.LBB131_17:                             @ %.lr.ph
                                        @ =>This Loop Header: Depth=1
                                        @     Child Loop BB131_18 Depth 2
	ldr.w	r0, [r11]
	bl	CRYP_DataIn
	ldr.w	r0, [r11, #4]
	bl	CRYP_DataIn
	ldr.w	r0, [r11, #8]
	bl	CRYP_DataIn
	ldr.w	r0, [r11, #12]
	bl	CRYP_DataIn
	str	r6, [sp]
.LBB131_18:                             @   Parent Loop BB131_17 Depth=1
                                        @ =>  This Inner Loop Header: Depth=2
	movs	r0, #16
	bl	CRYP_GetFlagStatus
	ldr	r1, [sp]
	adds	r1, #1
	str	r1, [sp]
	ldr	r1, [sp]
	cmp.w	r1, #65536
	it	ne
	cmpne	r0, #0
	bne	.LBB131_18
@ BB#19:                                @ %.critedge2
                                        @   in Loop: Header=BB131_17 Depth=1
	cmp	r0, #0
	bne	.LBB131_22
@ BB#20:                                @   in Loop: Header=BB131_17 Depth=1
	bl	CRYP_DataOut
	str.w	r0, [r9]
	bl	CRYP_DataOut
	str.w	r0, [r9, #4]
	bl	CRYP_DataOut
	str.w	r0, [r9, #8]
	bl	CRYP_DataOut
	adds	r5, #16
	str.w	r0, [r9, #12]
	cmp	r5, r10
	bhs	.LBB131_23
@ BB#21:                                @   in Loop: Header=BB131_17 Depth=1
	add.w	r9, r9, #16
	add.w	r11, r11, #16
	cmp	r4, #0
	bne	.LBB131_17
	b	.LBB131_23
.LBB131_22:
	movs	r4, #0
.LBB131_23:                             @ %.critedge1
	movs	r0, #0
	bl	CRYP_Cmd
	mov	r0, r4
	add	sp, #60
	pop.w	{r4, r5, r6, r7, r8, r9, r10, r11, pc}
.Ltmp131:
	.size	CRYP_AES_CBC, .Ltmp131-CRYP_AES_CBC

	.globl	CRYP_AES_CTR
	.align	2
	.type	CRYP_AES_CTR,%function
	.code	16                      @ @CRYP_AES_CTR
	.thumb_func
CRYP_AES_CTR:
@ BB#0:
	push.w	{r4, r5, r6, r7, r8, r9, r10, r11, lr}
	add	r7, sp, #12
	sub	sp, #60
	mov	r8, r0
	movs	r0, #0
	mov	r4, r3
	mov	r11, r2
	mov	r9, r1
	str	r0, [sp]
	add	r0, sp, #20
	bl	CRYP_KeyStructInit
	ldr	r5, [r7, #32]
	ldr.w	r10, [r7, #28]
	ldr	r6, [r7, #24]
	cmp.w	r4, #256
	beq	.LBB132_3
@ BB#1:
	cmp	r4, #192
	bne	.LBB132_4
@ BB#2:
	mov.w	r0, #256
	strh.w	r0, [sp, #58]
	ldr.w	r0, [r11]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #28]
	ldr.w	r0, [r11, #4]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #32]
	ldr.w	r0, [r11, #8]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #36]
	ldr.w	r0, [r11, #12]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #40]
	ldr.w	r0, [r11, #16]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #44]
	ldr.w	r0, [r11, #20]
	@APP
	rev r0, r0
	@NO_APP
	b	.LBB132_6
.LBB132_3:
	mov.w	r0, #512
	strh.w	r0, [sp, #58]
	ldr.w	r0, [r11]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #20]
	ldr.w	r0, [r11, #4]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #24]
	ldr.w	r0, [r11, #8]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #28]
	ldr.w	r0, [r11, #12]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #32]
	ldr.w	r0, [r11, #16]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #36]
	ldr.w	r0, [r11, #20]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #40]
	ldr.w	r0, [r11, #24]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #44]
	ldr.w	r0, [r11, #28]
	@APP
	rev r0, r0
	@NO_APP
	b	.LBB132_6
.LBB132_4:
	cmp	r4, #128
	bne	.LBB132_7
@ BB#5:
	movs	r0, #0
	strh.w	r0, [sp, #58]
	ldr.w	r0, [r11]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #36]
	ldr.w	r0, [r11, #4]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #40]
	ldr.w	r0, [r11, #8]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #44]
	ldr.w	r0, [r11, #12]
	@APP
	rev r0, r0
	@NO_APP
.LBB132_6:
	str	r0, [sp, #48]
.LBB132_7:
	ldr.w	r0, [r9]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #4]
	ldr.w	r0, [r9, #4]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #8]
	ldr.w	r0, [r9, #8]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #12]
	ldr.w	r0, [r9, #12]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #16]
	add	r0, sp, #20
	bl	CRYP_KeyInit
	cmp.w	r8, #0
	mov.w	r0, #0
	mov.w	r9, #0
	it	eq
	moveq	r0, #4
	strh.w	r0, [sp, #52]
	movs	r0, #48
	strh.w	r0, [sp, #54]
	movs	r0, #128
	strh.w	r0, [sp, #56]
	add	r0, sp, #52
	bl	CRYP_Init
	add	r0, sp, #4
	bl	CRYP_IVInit
	bl	CRYP_FIFOFlush
	movs	r0, #1
	movs	r4, #1
	bl	CRYP_Cmd
	cmp.w	r10, #0
	beq	.LBB132_15
@ BB#8:
	movs	r4, #0
.LBB132_9:                              @ %.lr.ph
                                        @ =>This Loop Header: Depth=1
                                        @     Child Loop BB132_10 Depth 2
	ldr	r0, [r6]
	bl	CRYP_DataIn
	ldr	r0, [r6, #4]
	bl	CRYP_DataIn
	ldr	r0, [r6, #8]
	bl	CRYP_DataIn
	ldr	r0, [r6, #12]
	bl	CRYP_DataIn
	str.w	r9, [sp]
.LBB132_10:                             @   Parent Loop BB132_9 Depth=1
                                        @ =>  This Inner Loop Header: Depth=2
	movs	r0, #16
	bl	CRYP_GetFlagStatus
	ldr	r1, [sp]
	adds	r1, #1
	str	r1, [sp]
	ldr	r1, [sp]
	cmp.w	r1, #65536
	it	ne
	cmpne	r0, #0
	bne	.LBB132_10
@ BB#11:                                @ %.critedge1
                                        @   in Loop: Header=BB132_9 Depth=1
	cmp	r0, #0
	bne	.LBB132_14
@ BB#12:                                @   in Loop: Header=BB132_9 Depth=1
	bl	CRYP_DataOut
	str	r0, [r5]
	bl	CRYP_DataOut
	str	r0, [r5, #4]
	bl	CRYP_DataOut
	str	r0, [r5, #8]
	bl	CRYP_DataOut
	str	r0, [r5, #12]
	adds	r4, #16
	adds	r5, #16
	adds	r6, #16
	cmp	r4, r10
	blo	.LBB132_9
@ BB#13:
	movs	r4, #1
	b	.LBB132_15
.LBB132_14:
	movs	r4, #0
.LBB132_15:                             @ %.critedge
	movs	r0, #0
	bl	CRYP_Cmd
	mov	r0, r4
	add	sp, #60
	pop.w	{r4, r5, r6, r7, r8, r9, r10, r11, pc}
.Ltmp132:
	.size	CRYP_AES_CTR, .Ltmp132-CRYP_AES_CTR

	.globl	CRYP_DES_ECB
	.align	2
	.type	CRYP_DES_ECB,%function
	.code	16                      @ @CRYP_DES_ECB
	.thumb_func
CRYP_DES_ECB:
@ BB#0:
	push.w	{r4, r5, r6, r7, r8, r9, r10, r11, lr}
	add	r7, sp, #12
	sub	sp, #44
	add.w	r9, sp, #4
	mov	r8, r0
	mov.w	r10, #0
	mov	r11, r3
	mov	r5, r2
	mov	r6, r1
	mov	r0, r9
	str.w	r10, [sp]
	bl	CRYP_KeyStructInit
	movs	r0, #4
	cmp.w	r8, #1
	it	eq
	moveq	r0, #0
	strh.w	r0, [sp, #36]
	movs	r0, #16
	strh.w	r0, [sp, #38]
	movs	r0, #128
	strh.w	r0, [sp, #40]
	add	r0, sp, #36
	bl	CRYP_Init
	ldr	r0, [r6]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #12]
	ldr	r0, [r6, #4]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #16]
	mov	r0, r9
	bl	CRYP_KeyInit
	bl	CRYP_FIFOFlush
	movs	r0, #1
	movs	r6, #1
	bl	CRYP_Cmd
	cmp.w	r11, #0
	beq	.LBB133_8
@ BB#1:                                 @ %.lr.ph
	ldr	r6, [r7, #24]
	movs	r4, #0
.LBB133_2:                              @ =>This Loop Header: Depth=1
                                        @     Child Loop BB133_3 Depth 2
	ldr	r0, [r5]
	bl	CRYP_DataIn
	ldr	r0, [r5, #4]
	bl	CRYP_DataIn
	str.w	r10, [sp]
.LBB133_3:                              @   Parent Loop BB133_2 Depth=1
                                        @ =>  This Inner Loop Header: Depth=2
	movs	r0, #16
	bl	CRYP_GetFlagStatus
	ldr	r1, [sp]
	adds	r1, #1
	str	r1, [sp]
	ldr	r1, [sp]
	cmp.w	r1, #65536
	it	ne
	cmpne	r0, #0
	bne	.LBB133_3
@ BB#4:                                 @ %.critedge1
                                        @   in Loop: Header=BB133_2 Depth=1
	cmp	r0, #0
	bne	.LBB133_7
@ BB#5:                                 @   in Loop: Header=BB133_2 Depth=1
	bl	CRYP_DataOut
	str	r0, [r6]
	bl	CRYP_DataOut
	str	r0, [r6, #4]
	adds	r4, #8
	adds	r6, #8
	adds	r5, #8
	cmp	r4, r11
	blo	.LBB133_2
@ BB#6:
	movs	r6, #1
	b	.LBB133_8
.LBB133_7:
	movs	r6, #0
.LBB133_8:                              @ %.critedge
	movs	r0, #0
	bl	CRYP_Cmd
	mov	r0, r6
	add	sp, #44
	pop.w	{r4, r5, r6, r7, r8, r9, r10, r11, pc}
.Ltmp133:
	.size	CRYP_DES_ECB, .Ltmp133-CRYP_DES_ECB

	.globl	CRYP_DES_CBC
	.align	2
	.type	CRYP_DES_CBC,%function
	.code	16                      @ @CRYP_DES_CBC
	.thumb_func
CRYP_DES_CBC:
@ BB#0:
	push.w	{r4, r5, r6, r7, r8, r9, r10, lr}
	add	r7, sp, #12
	sub	sp, #64
	add.w	r9, sp, #24
	mov	r5, r0
	mov.w	r10, #0
	mov	r4, r3
	mov	r8, r2
	mov	r6, r1
	mov	r0, r9
	str.w	r10, [sp, #4]
	bl	CRYP_KeyStructInit
	movs	r0, #4
	cmp	r5, #1
	it	eq
	moveq	r0, #0
	strh.w	r0, [sp, #56]
	movs	r0, #24
	strh.w	r0, [sp, #58]
	movs	r0, #128
	strh.w	r0, [sp, #60]
	add	r0, sp, #56
	bl	CRYP_Init
	ldr	r0, [r6]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #32]
	ldr	r0, [r6, #4]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #36]
	mov	r0, r9
	bl	CRYP_KeyInit
	ldr.w	r0, [r8]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #8]
	ldr.w	r0, [r8, #4]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #12]
	add	r0, sp, #8
	bl	CRYP_IVInit
	bl	CRYP_FIFOFlush
	movs	r0, #1
	movs	r5, #1
	bl	CRYP_Cmd
	ldr.w	r8, [r7, #20]
	cmp.w	r8, #0
	beq	.LBB134_8
@ BB#1:                                 @ %.lr.ph
	ldr	r5, [r7, #24]
	movs	r6, #0
.LBB134_2:                              @ =>This Loop Header: Depth=1
                                        @     Child Loop BB134_3 Depth 2
	ldr	r0, [r4]
	bl	CRYP_DataIn
	ldr	r0, [r4, #4]
	bl	CRYP_DataIn
	str.w	r10, [sp, #4]
.LBB134_3:                              @   Parent Loop BB134_2 Depth=1
                                        @ =>  This Inner Loop Header: Depth=2
	movs	r0, #16
	bl	CRYP_GetFlagStatus
	ldr	r1, [sp, #4]
	adds	r1, #1
	str	r1, [sp, #4]
	ldr	r1, [sp, #4]
	cmp.w	r1, #65536
	it	ne
	cmpne	r0, #0
	bne	.LBB134_3
@ BB#4:                                 @ %.critedge1
                                        @   in Loop: Header=BB134_2 Depth=1
	cmp	r0, #0
	bne	.LBB134_7
@ BB#5:                                 @   in Loop: Header=BB134_2 Depth=1
	bl	CRYP_DataOut
	str	r0, [r5]
	bl	CRYP_DataOut
	str	r0, [r5, #4]
	adds	r6, #8
	adds	r5, #8
	adds	r4, #8
	cmp	r6, r8
	blo	.LBB134_2
@ BB#6:
	movs	r5, #1
	b	.LBB134_8
.LBB134_7:
	movs	r5, #0
.LBB134_8:                              @ %.critedge
	movs	r0, #0
	bl	CRYP_Cmd
	mov	r0, r5
	add	sp, #64
	pop.w	{r4, r5, r6, r7, r8, r9, r10, pc}
.Ltmp134:
	.size	CRYP_DES_CBC, .Ltmp134-CRYP_DES_CBC

	.globl	CRYP_TDES_ECB
	.align	2
	.type	CRYP_TDES_ECB,%function
	.code	16                      @ @CRYP_TDES_ECB
	.thumb_func
CRYP_TDES_ECB:
@ BB#0:
	push.w	{r4, r5, r6, r7, r8, r9, r10, r11, lr}
	add	r7, sp, #12
	sub	sp, #44
	add.w	r9, sp, #4
	mov	r8, r0
	mov.w	r10, #0
	mov	r11, r3
	mov	r5, r2
	mov	r6, r1
	mov	r0, r9
	str.w	r10, [sp]
	bl	CRYP_KeyStructInit
	movs	r0, #4
	cmp.w	r8, #1
	it	eq
	moveq	r0, #0
	strh.w	r0, [sp, #36]
	movs	r0, #128
	strh.w	r10, [sp, #38]
	strh.w	r0, [sp, #40]
	add	r0, sp, #36
	bl	CRYP_Init
	ldr	r0, [r6]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #12]
	ldr	r0, [r6, #4]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #16]
	ldr	r0, [r6, #8]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #20]
	ldr	r0, [r6, #12]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #24]
	ldr	r0, [r6, #16]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #28]
	ldr	r0, [r6, #20]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #32]
	mov	r0, r9
	bl	CRYP_KeyInit
	bl	CRYP_FIFOFlush
	movs	r0, #1
	movs	r6, #1
	bl	CRYP_Cmd
	cmp.w	r11, #0
	beq	.LBB135_8
@ BB#1:                                 @ %.lr.ph
	ldr	r6, [r7, #24]
	movs	r4, #0
.LBB135_2:                              @ =>This Loop Header: Depth=1
                                        @     Child Loop BB135_3 Depth 2
	ldr	r0, [r5]
	bl	CRYP_DataIn
	ldr	r0, [r5, #4]
	bl	CRYP_DataIn
	str.w	r10, [sp]
.LBB135_3:                              @   Parent Loop BB135_2 Depth=1
                                        @ =>  This Inner Loop Header: Depth=2
	movs	r0, #16
	bl	CRYP_GetFlagStatus
	ldr	r1, [sp]
	adds	r1, #1
	str	r1, [sp]
	ldr	r1, [sp]
	cmp.w	r1, #65536
	it	ne
	cmpne	r0, #0
	bne	.LBB135_3
@ BB#4:                                 @ %.critedge1
                                        @   in Loop: Header=BB135_2 Depth=1
	cmp	r0, #0
	bne	.LBB135_7
@ BB#5:                                 @   in Loop: Header=BB135_2 Depth=1
	bl	CRYP_DataOut
	str	r0, [r6]
	bl	CRYP_DataOut
	str	r0, [r6, #4]
	adds	r4, #8
	adds	r6, #8
	adds	r5, #8
	cmp	r4, r11
	blo	.LBB135_2
@ BB#6:
	movs	r6, #1
	b	.LBB135_8
.LBB135_7:
	movs	r6, #0
.LBB135_8:                              @ %.critedge
	movs	r0, #0
	bl	CRYP_Cmd
	mov	r0, r6
	add	sp, #44
	pop.w	{r4, r5, r6, r7, r8, r9, r10, r11, pc}
.Ltmp135:
	.size	CRYP_TDES_ECB, .Ltmp135-CRYP_TDES_ECB

	.globl	CRYP_TDES_CBC
	.align	2
	.type	CRYP_TDES_CBC,%function
	.code	16                      @ @CRYP_TDES_CBC
	.thumb_func
CRYP_TDES_CBC:
@ BB#0:
	push.w	{r4, r5, r6, r7, r8, r9, r10, lr}
	add	r7, sp, #12
	sub	sp, #64
	add.w	r9, sp, #24
	mov	r5, r0
	mov.w	r10, #0
	mov	r4, r3
	mov	r8, r2
	mov	r6, r1
	mov	r0, r9
	str.w	r10, [sp, #4]
	bl	CRYP_KeyStructInit
	movs	r0, #4
	cmp	r5, #1
	it	eq
	moveq	r0, #0
	strh.w	r0, [sp, #56]
	movs	r0, #8
	strh.w	r0, [sp, #58]
	movs	r0, #128
	strh.w	r0, [sp, #60]
	add	r0, sp, #56
	bl	CRYP_Init
	ldr	r0, [r6]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #32]
	ldr	r0, [r6, #4]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #36]
	ldr	r0, [r6, #8]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #40]
	ldr	r0, [r6, #12]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #44]
	ldr	r0, [r6, #16]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #48]
	ldr	r0, [r6, #20]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #52]
	mov	r0, r9
	bl	CRYP_KeyInit
	ldr.w	r0, [r8]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #8]
	ldr.w	r0, [r8, #4]
	@APP
	rev r0, r0
	@NO_APP
	str	r0, [sp, #12]
	add	r0, sp, #8
	bl	CRYP_IVInit
	bl	CRYP_FIFOFlush
	movs	r0, #1
	movs	r5, #1
	bl	CRYP_Cmd
	ldr.w	r8, [r7, #20]
	cmp.w	r8, #0
	beq	.LBB136_8
@ BB#1:                                 @ %.lr.ph
	ldr	r5, [r7, #24]
	movs	r6, #0
.LBB136_2:                              @ =>This Loop Header: Depth=1
                                        @     Child Loop BB136_3 Depth 2
	ldr	r0, [r4]
	bl	CRYP_DataIn
	ldr	r0, [r4, #4]
	bl	CRYP_DataIn
	str.w	r10, [sp, #4]
.LBB136_3:                              @   Parent Loop BB136_2 Depth=1
                                        @ =>  This Inner Loop Header: Depth=2
	movs	r0, #16
	bl	CRYP_GetFlagStatus
	ldr	r1, [sp, #4]
	adds	r1, #1
	str	r1, [sp, #4]
	ldr	r1, [sp, #4]
	cmp.w	r1, #65536
	it	ne
	cmpne	r0, #0
	bne	.LBB136_3
@ BB#4:                                 @ %.critedge1
                                        @   in Loop: Header=BB136_2 Depth=1
	cmp	r0, #0
	bne	.LBB136_7
@ BB#5:                                 @   in Loop: Header=BB136_2 Depth=1
	bl	CRYP_DataOut
	str	r0, [r5]
	bl	CRYP_DataOut
	str	r0, [r5, #4]
	adds	r6, #8
	adds	r5, #8
	adds	r4, #8
	cmp	r6, r8
	blo	.LBB136_2
@ BB#6:
	movs	r5, #1
	b	.LBB136_8
.LBB136_7:
	movs	r5, #0
.LBB136_8:                              @ %.critedge
	movs	r0, #0
	bl	CRYP_Cmd
	mov	r0, r5
	add	sp, #64
	pop.w	{r4, r5, r6, r7, r8, r9, r10, pc}
.Ltmp136:
	.size	CRYP_TDES_CBC, .Ltmp136-CRYP_TDES_CBC

	.globl	DAC_DeInit
	.align	2
	.type	DAC_DeInit,%function
	.code	16                      @ @DAC_DeInit
	.thumb_func
DAC_DeInit:
@ BB#0:
	push	{r7, lr}
	mov.w	r0, #536870912
	movs	r1, #1
	mov	r7, sp
	bl	RCC_APB1PeriphResetCmd
	mov.w	r0, #536870912
	movs	r1, #0
	bl	RCC_APB1PeriphResetCmd
	pop	{r7, pc}
.Ltmp137:
	.size	DAC_DeInit, .Ltmp137-DAC_DeInit

	.globl	DAC_Init
	.align	2
	.type	DAC_Init,%function
	.code	16                      @ @DAC_Init
	.thumb_func
DAC_Init:
@ BB#0:
	push	{r4, lr}
	movw	r12, #29696
	movw	r2, #4094
	movt	r12, #16384
	lsls	r2, r0
	ldr.w	r3, [r12]
	ldr	r4, [r1, #8]
	bic.w	lr, r3, r2
	ldr	r3, [r1]
	ldr	r2, [r1, #4]
	ldr	r1, [r1, #12]
	orrs	r2, r3
	orrs	r2, r4
	orrs	r1, r2
	lsl.w	r0, r1, r0
	orr.w	r0, r0, lr
	str.w	r0, [r12]
	pop	{r4, pc}
.Ltmp138:
	.size	DAC_Init, .Ltmp138-DAC_Init

	.globl	DAC_StructInit
	.align	2
	.type	DAC_StructInit,%function
	.code	16                      @ @DAC_StructInit
	.thumb_func
DAC_StructInit:
@ BB#0:
	movs	r1, #0
	str	r1, [r0]
	str	r1, [r0, #4]
	str	r1, [r0, #8]
	str	r1, [r0, #12]
	bx	lr
.Ltmp139:
	.size	DAC_StructInit, .Ltmp139-DAC_StructInit

	.globl	DAC_Cmd
	.align	2
	.type	DAC_Cmd,%function
	.code	16                      @ @DAC_Cmd
	.thumb_func
DAC_Cmd:
@ BB#0:
	cmp	r1, #0
	movw	r1, #29696
	mov.w	r2, #1
	movt	r1, #16384
	lsl.w	r0, r2, r0
	ldr	r2, [r1]
	ite	eq
	biceq.w	r0, r2, r0
	orrne	r0, r2
	str	r0, [r1]
	bx	lr
.Ltmp140:
	.size	DAC_Cmd, .Ltmp140-DAC_Cmd

	.globl	DAC_SoftwareTriggerCmd
	.align	2
	.type	DAC_SoftwareTriggerCmd,%function
	.code	16                      @ @DAC_SoftwareTriggerCmd
	.thumb_func
DAC_SoftwareTriggerCmd:
@ BB#0:
	cmp	r1, #0
	movw	r1, #29700
	lsr.w	r0, r0, #4
	mov.w	r2, #1
	movt	r1, #16384
	lsl.w	r0, r2, r0
	ldr	r2, [r1]
	ite	eq
	biceq.w	r0, r2, r0
	orrne	r0, r2
	str	r0, [r1]
	bx	lr
.Ltmp141:
	.size	DAC_SoftwareTriggerCmd, .Ltmp141-DAC_SoftwareTriggerCmd

	.globl	DAC_DualSoftwareTriggerCmd
	.align	2
	.type	DAC_DualSoftwareTriggerCmd,%function
	.code	16                      @ @DAC_DualSoftwareTriggerCmd
	.thumb_func
DAC_DualSoftwareTriggerCmd:
@ BB#0:
	movw	r1, #29700
	cmp	r0, #0
	movt	r1, #16384
	ldr	r2, [r1]
	ite	eq
	biceq	r0, r2, #3
	orrne	r0, r2, #3
	str	r0, [r1]
	bx	lr
.Ltmp142:
	.size	DAC_DualSoftwareTriggerCmd, .Ltmp142-DAC_DualSoftwareTriggerCmd

	.globl	DAC_WaveGenerationCmd
	.align	2
	.type	DAC_WaveGenerationCmd,%function
	.code	16                      @ @DAC_WaveGenerationCmd
	.thumb_func
DAC_WaveGenerationCmd:
@ BB#0:
	lsl.w	r0, r1, r0
	movw	r1, #29696
	cmp	r2, #0
	movt	r1, #16384
	ldr	r2, [r1]
	ite	eq
	biceq.w	r0, r2, r0
	orrne	r0, r2
	str	r0, [r1]
	bx	lr
.Ltmp143:
	.size	DAC_WaveGenerationCmd, .Ltmp143-DAC_WaveGenerationCmd

	.globl	DAC_SetChannel1Data
	.align	2
	.type	DAC_SetChannel1Data,%function
	.code	16                      @ @DAC_SetChannel1Data
	.thumb_func
DAC_SetChannel1Data:
@ BB#0:
	sub	sp, #8
	movs	r2, #0
	str	r2, [sp, #4]
	movw	r2, #29696
	movt	r2, #16384
	str	r2, [sp, #4]
	ldr	r2, [sp, #4]
	add	r0, r2
	adds	r0, #8
	str	r0, [sp, #4]
	ldr	r0, [sp, #4]
	str	r1, [r0]
	add	sp, #8
	bx	lr
.Ltmp144:
	.size	DAC_SetChannel1Data, .Ltmp144-DAC_SetChannel1Data

	.globl	DAC_SetChannel2Data
	.align	2
	.type	DAC_SetChannel2Data,%function
	.code	16                      @ @DAC_SetChannel2Data
	.thumb_func
DAC_SetChannel2Data:
@ BB#0:
	sub	sp, #8
	movs	r2, #0
	str	r2, [sp, #4]
	movw	r2, #29696
	movt	r2, #16384
	str	r2, [sp, #4]
	ldr	r2, [sp, #4]
	add	r0, r2
	adds	r0, #20
	str	r0, [sp, #4]
	ldr	r0, [sp, #4]
	str	r1, [r0]
	add	sp, #8
	bx	lr
.Ltmp145:
	.size	DAC_SetChannel2Data, .Ltmp145-DAC_SetChannel2Data

	.globl	DAC_SetDualChannelData
	.align	2
	.type	DAC_SetDualChannelData,%function
	.code	16                      @ @DAC_SetDualChannelData
	.thumb_func
DAC_SetDualChannelData:
@ BB#0:
	cmp	r0, #8
	ite	ne
	orrne.w	r1, r2, r1, lsl #16
	orreq.w	r1, r2, r1, lsl #8
	movw	r2, #29728
	movt	r2, #16384
	str	r1, [r0, r2]
	bx	lr
.Ltmp146:
	.size	DAC_SetDualChannelData, .Ltmp146-DAC_SetDualChannelData

	.globl	DAC_GetDataOutputValue
	.align	2
	.type	DAC_GetDataOutputValue,%function
	.code	16                      @ @DAC_GetDataOutputValue
	.thumb_func
DAC_GetDataOutputValue:
@ BB#0:
	sub	sp, #8
	movs	r1, #0
	str	r1, [sp, #4]
	movw	r1, #29696
	movt	r1, #16384
	str	r1, [sp, #4]
	ldr	r1, [sp, #4]
	add.w	r0, r1, r0, lsr #2
	adds	r0, #44
	str	r0, [sp, #4]
	ldr	r0, [sp, #4]
	ldr	r0, [r0]
	uxth	r0, r0
	add	sp, #8
	bx	lr
.Ltmp147:
	.size	DAC_GetDataOutputValue, .Ltmp147-DAC_GetDataOutputValue

	.globl	DAC_DMACmd
	.align	2
	.type	DAC_DMACmd,%function
	.code	16                      @ @DAC_DMACmd
	.thumb_func
DAC_DMACmd:
@ BB#0:
	cmp	r1, #0
	movw	r1, #29696
	mov.w	r2, #4096
	movt	r1, #16384
	lsl.w	r0, r2, r0
	ldr	r2, [r1]
	ite	eq
	biceq.w	r0, r2, r0
	orrne	r0, r2
	str	r0, [r1]
	bx	lr
.Ltmp148:
	.size	DAC_DMACmd, .Ltmp148-DAC_DMACmd

	.globl	DAC_ITConfig
	.align	2
	.type	DAC_ITConfig,%function
	.code	16                      @ @DAC_ITConfig
	.thumb_func
DAC_ITConfig:
@ BB#0:
	lsl.w	r0, r1, r0
	movw	r1, #29696
	cmp	r2, #0
	movt	r1, #16384
	ldr	r2, [r1]
	ite	eq
	biceq.w	r0, r2, r0
	orrne	r0, r2
	str	r0, [r1]
	bx	lr
.Ltmp149:
	.size	DAC_ITConfig, .Ltmp149-DAC_ITConfig

	.globl	DAC_GetFlagStatus
	.align	2
	.type	DAC_GetFlagStatus,%function
	.code	16                      @ @DAC_GetFlagStatus
	.thumb_func
DAC_GetFlagStatus:
@ BB#0:
	lsl.w	r0, r1, r0
	movw	r1, #29748
	movt	r1, #16384
	ldr	r1, [r1]
	ands	r0, r1
	it	ne
	movne	r0, #1
	bx	lr
.Ltmp150:
	.size	DAC_GetFlagStatus, .Ltmp150-DAC_GetFlagStatus

	.globl	DAC_ClearFlag
	.align	2
	.type	DAC_ClearFlag,%function
	.code	16                      @ @DAC_ClearFlag
	.thumb_func
DAC_ClearFlag:
@ BB#0:
	lsl.w	r0, r1, r0
	movw	r1, #29748
	movt	r1, #16384
	str	r0, [r1]
	bx	lr
.Ltmp151:
	.size	DAC_ClearFlag, .Ltmp151-DAC_ClearFlag

	.globl	DAC_GetITStatus
	.align	2
	.type	DAC_GetITStatus,%function
	.code	16                      @ @DAC_GetITStatus
	.thumb_func
DAC_GetITStatus:
@ BB#0:
	lsl.w	r0, r1, r0
	movw	r1, #29696
	movw	r2, #29748
	movt	r1, #16384
	movt	r2, #16384
	ldr	r1, [r1]
	ands	r1, r0
	it	ne
	movne	r1, #1
	ldr	r2, [r2]
	ands	r0, r2
	it	ne
	movne	r0, #1
	ands	r0, r1
	bx	lr
.Ltmp152:
	.size	DAC_GetITStatus, .Ltmp152-DAC_GetITStatus

	.globl	DAC_ClearITPendingBit
	.align	2
	.type	DAC_ClearITPendingBit,%function
	.code	16                      @ @DAC_ClearITPendingBit
	.thumb_func
DAC_ClearITPendingBit:
@ BB#0:
	lsl.w	r0, r1, r0
	movw	r1, #29748
	movt	r1, #16384
	str	r0, [r1]
	bx	lr
.Ltmp153:
	.size	DAC_ClearITPendingBit, .Ltmp153-DAC_ClearITPendingBit

	.globl	DBGMCU_GetREVID
	.align	2
	.type	DBGMCU_GetREVID,%function
	.code	16                      @ @DBGMCU_GetREVID
	.thumb_func
DBGMCU_GetREVID:
@ BB#0:
	movw	r0, #8192
	movt	r0, #57348
	ldr	r0, [r0]
	lsrs	r0, r0, #16
	bx	lr
.Ltmp154:
	.size	DBGMCU_GetREVID, .Ltmp154-DBGMCU_GetREVID

	.globl	DBGMCU_GetDEVID
	.align	2
	.type	DBGMCU_GetDEVID,%function
	.code	16                      @ @DBGMCU_GetDEVID
	.thumb_func
DBGMCU_GetDEVID:
@ BB#0:
	movw	r0, #8192
	movt	r0, #57348
	ldr	r0, [r0]
	bfc	r0, #12, #20
	bx	lr
.Ltmp155:
	.size	DBGMCU_GetDEVID, .Ltmp155-DBGMCU_GetDEVID

	.globl	DBGMCU_Config
	.align	2
	.type	DBGMCU_Config,%function
	.code	16                      @ @DBGMCU_Config
	.thumb_func
DBGMCU_Config:
@ BB#0:
	cmp	r1, #0
	movw	r1, #8196
	movt	r1, #57348
	ldr	r2, [r1]
	ite	eq
	biceq.w	r0, r2, r0
	orrne	r0, r2
	str	r0, [r1]
	bx	lr
.Ltmp156:
	.size	DBGMCU_Config, .Ltmp156-DBGMCU_Config

	.globl	DBGMCU_APB1PeriphConfig
	.align	2
	.type	DBGMCU_APB1PeriphConfig,%function
	.code	16                      @ @DBGMCU_APB1PeriphConfig
	.thumb_func
DBGMCU_APB1PeriphConfig:
@ BB#0:
	cmp	r1, #0
	movw	r1, #8200
	movt	r1, #57348
	ldr	r2, [r1]
	ite	eq
	biceq.w	r0, r2, r0
	orrne	r0, r2
	str	r0, [r1]
	bx	lr
.Ltmp157:
	.size	DBGMCU_APB1PeriphConfig, .Ltmp157-DBGMCU_APB1PeriphConfig

	.globl	DBGMCU_APB2PeriphConfig
	.align	2
	.type	DBGMCU_APB2PeriphConfig,%function
	.code	16                      @ @DBGMCU_APB2PeriphConfig
	.thumb_func
DBGMCU_APB2PeriphConfig:
@ BB#0:
	cmp	r1, #0
	movw	r1, #8204
	movt	r1, #57348
	ldr	r2, [r1]
	ite	eq
	biceq.w	r0, r2, r0
	orrne	r0, r2
	str	r0, [r1]
	bx	lr
.Ltmp158:
	.size	DBGMCU_APB2PeriphConfig, .Ltmp158-DBGMCU_APB2PeriphConfig

	.globl	DCMI_DeInit
	.align	2
	.type	DCMI_DeInit,%function
	.code	16                      @ @DCMI_DeInit
	.thumb_func
DCMI_DeInit:
@ BB#0:
	movs	r0, #0
	movs	r1, #0
	movs	r2, #31
	movt	r0, #20485
	str	r1, [r0]
	movs	r0, #12
	movt	r0, #20485
	str	r1, [r0]
	movs	r0, #20
	movt	r0, #20485
	str	r2, [r0]
	movs	r0, #24
	movt	r0, #20485
	str	r1, [r0]
	movs	r0, #28
	movt	r0, #20485
	str	r1, [r0]
	movs	r0, #32
	movt	r0, #20485
	str	r1, [r0]
	movs	r0, #36
	movt	r0, #20485
	str	r1, [r0]
	bx	lr
.Ltmp159:
	.size	DCMI_DeInit, .Ltmp159-DCMI_DeInit

	.globl	DCMI_Init
	.align	2
	.type	DCMI_Init,%function
	.code	16                      @ @DCMI_Init
	.thumb_func
DCMI_Init:
@ BB#0:
	movs	r1, #0
	movw	r3, #49150
	movt	r1, #20485
	movt	r3, #65535
	ldr	r2, [r1]
	ands	r2, r3
	movw	r3, #61453
	str	r2, [r1]
	movt	r3, #65535
	ldr	r2, [r1]
	and.w	r12, r2, r3
	ldrh	r3, [r0]
	ldrh	r2, [r0, #2]
	orrs	r2, r3
	ldrh	r3, [r0, #4]
	orrs	r2, r3
	ldrh	r3, [r0, #6]
	orrs	r2, r3
	ldrh	r3, [r0, #8]
	orrs	r2, r3
	ldrh	r3, [r0, #10]
	ldrh	r0, [r0, #12]
	orrs	r2, r3
	orrs	r0, r2
	uxth	r0, r0
	orr.w	r0, r0, r12
	str	r0, [r1]
	bx	lr
.Ltmp160:
	.size	DCMI_Init, .Ltmp160-DCMI_Init

	.globl	DCMI_StructInit
	.align	2
	.type	DCMI_StructInit,%function
	.code	16                      @ @DCMI_StructInit
	.thumb_func
DCMI_StructInit:
@ BB#0:
	movs	r1, #0
	strh	r1, [r0, #2]
	strh	r1, [r0]
	strh	r1, [r0, #6]
	strh	r1, [r0, #4]
	strh	r1, [r0, #10]
	strh	r1, [r0, #8]
	strh	r1, [r0, #12]
	bx	lr
.Ltmp161:
	.size	DCMI_StructInit, .Ltmp161-DCMI_StructInit

	.globl	DCMI_CROPConfig
	.align	2
	.type	DCMI_CROPConfig,%function
	.code	16                      @ @DCMI_CROPConfig
	.thumb_func
DCMI_CROPConfig:
@ BB#0:
	ldrh	r1, [r0]
	ldrh	r2, [r0, #2]
	orr.w	r1, r2, r1, lsl #16
	movs	r2, #32
	movt	r2, #20485
	str	r1, [r2]
	ldrh	r1, [r0, #4]
	ldrh	r0, [r0, #6]
	orr.w	r0, r0, r1, lsl #16
	movs	r1, #36
	movt	r1, #20485
	str	r0, [r1]
	bx	lr
.Ltmp162:
	.size	DCMI_CROPConfig, .Ltmp162-DCMI_CROPConfig

	.globl	DCMI_CROPCmd
	.align	2
	.type	DCMI_CROPCmd,%function
	.code	16                      @ @DCMI_CROPCmd
	.thumb_func
DCMI_CROPCmd:
@ BB#0:
	movs	r1, #0
	cmp	r0, #0
	movt	r1, #20485
	ldr	r2, [r1]
	ite	eq
	biceq	r0, r2, #4
	orrne	r0, r2, #4
	str	r0, [r1]
	bx	lr
.Ltmp163:
	.size	DCMI_CROPCmd, .Ltmp163-DCMI_CROPCmd

	.globl	DCMI_SetEmbeddedSynchroCodes
	.align	2
	.type	DCMI_SetEmbeddedSynchroCodes,%function
	.code	16                      @ @DCMI_SetEmbeddedSynchroCodes
	.thumb_func
DCMI_SetEmbeddedSynchroCodes:
@ BB#0:
	ldrb	r1, [r0]
	ldrb	r2, [r0, #1]
	ldrb	r3, [r0, #2]
	ldrb	r0, [r0, #3]
	orr.w	r1, r1, r2, lsl #8
	orr.w	r1, r1, r3, lsl #16
	orr.w	r0, r1, r0, lsl #24
	movs	r1, #24
	movt	r1, #20485
	str	r0, [r1]
	bx	lr
.Ltmp164:
	.size	DCMI_SetEmbeddedSynchroCodes, .Ltmp164-DCMI_SetEmbeddedSynchroCodes

	.globl	DCMI_JPEGCmd
	.align	2
	.type	DCMI_JPEGCmd,%function
	.code	16                      @ @DCMI_JPEGCmd
	.thumb_func
DCMI_JPEGCmd:
@ BB#0:
	movs	r1, #0
	cmp	r0, #0
	movt	r1, #20485
	ldr	r2, [r1]
	ite	eq
	biceq	r0, r2, #8
	orrne	r0, r2, #8
	str	r0, [r1]
	bx	lr
.Ltmp165:
	.size	DCMI_JPEGCmd, .Ltmp165-DCMI_JPEGCmd

	.globl	DCMI_Cmd
	.align	2
	.type	DCMI_Cmd,%function
	.code	16                      @ @DCMI_Cmd
	.thumb_func
DCMI_Cmd:
@ BB#0:
	movs	r1, #0
	cmp	r0, #0
	movt	r1, #20485
	ldr	r2, [r1]
	ite	eq
	biceq	r0, r2, #16384
	orrne	r0, r2, #16384
	str	r0, [r1]
	bx	lr
.Ltmp166:
	.size	DCMI_Cmd, .Ltmp166-DCMI_Cmd

	.globl	DCMI_CaptureCmd
	.align	2
	.type	DCMI_CaptureCmd,%function
	.code	16                      @ @DCMI_CaptureCmd
	.thumb_func
DCMI_CaptureCmd:
@ BB#0:
	movs	r1, #0
	cmp	r0, #0
	movt	r1, #20485
	ldr	r2, [r1]
	ite	eq
	biceq	r0, r2, #1
	orrne	r0, r2, #1
	str	r0, [r1]
	bx	lr
.Ltmp167:
	.size	DCMI_CaptureCmd, .Ltmp167-DCMI_CaptureCmd

	.globl	DCMI_ReadData
	.align	2
	.type	DCMI_ReadData,%function
	.code	16                      @ @DCMI_ReadData
	.thumb_func
DCMI_ReadData:
@ BB#0:
	movs	r0, #40
	movt	r0, #20485
	ldr	r0, [r0]
	bx	lr
.Ltmp168:
	.size	DCMI_ReadData, .Ltmp168-DCMI_ReadData

	.globl	DCMI_ITConfig
	.align	2
	.type	DCMI_ITConfig,%function
	.code	16                      @ @DCMI_ITConfig
	.thumb_func
DCMI_ITConfig:
@ BB#0:
	cbz	r1, .LBB169_2
@ BB#1:
	movs	r1, #12
	movt	r1, #20485
	ldr	r2, [r1]
	orrs	r0, r2
	str	r0, [r1]
	bx	lr
.LBB169_2:
	movw	r1, #65535
	eors	r0, r1
	movs	r1, #12
	movt	r1, #20485
	ldr	r2, [r1]
	ands	r0, r2
	str	r0, [r1]
	bx	lr
.Ltmp169:
	.size	DCMI_ITConfig, .Ltmp169-DCMI_ITConfig

	.globl	DCMI_GetFlagStatus
	.align	2
	.type	DCMI_GetFlagStatus,%function
	.code	16                      @ @DCMI_GetFlagStatus
	.thumb_func
DCMI_GetFlagStatus:
@ BB#0:
	movs	r1, #1
	cmp.w	r1, r0, lsr #12
	bne	.LBB170_2
@ BB#1:
	movs	r1, #8
	b	.LBB170_3
.LBB170_2:
	lsrs	r1, r0, #12
	cmp	r1, #2
	ite	ne
	movne	r1, #16
	moveq	r1, #4
.LBB170_3:
	movt	r1, #20485
	ldr	r1, [r1]
	ands	r0, r1
	it	ne
	movne	r0, #1
	bx	lr
.Ltmp170:
	.size	DCMI_GetFlagStatus, .Ltmp170-DCMI_GetFlagStatus

	.globl	DCMI_ClearFlag
	.align	2
	.type	DCMI_ClearFlag,%function
	.code	16                      @ @DCMI_ClearFlag
	.thumb_func
DCMI_ClearFlag:
@ BB#0:
	movs	r1, #20
	movt	r1, #20485
	str	r0, [r1]
	bx	lr
.Ltmp171:
	.size	DCMI_ClearFlag, .Ltmp171-DCMI_ClearFlag

	.globl	DCMI_GetITStatus
	.align	2
	.type	DCMI_GetITStatus,%function
	.code	16                      @ @DCMI_GetITStatus
	.thumb_func
DCMI_GetITStatus:
@ BB#0:
	movs	r1, #16
	movt	r1, #20485
	ldr	r1, [r1]
	ands	r0, r1
	it	ne
	movne	r0, #1
	bx	lr
.Ltmp172:
	.size	DCMI_GetITStatus, .Ltmp172-DCMI_GetITStatus

	.globl	DCMI_ClearITPendingBit
	.align	2
	.type	DCMI_ClearITPendingBit,%function
	.code	16                      @ @DCMI_ClearITPendingBit
	.thumb_func
DCMI_ClearITPendingBit:
@ BB#0:
	movs	r1, #20
	movt	r1, #20485
	str	r0, [r1]
	bx	lr
.Ltmp173:
	.size	DCMI_ClearITPendingBit, .Ltmp173-DCMI_ClearITPendingBit

	.globl	DMA_DeInit
	.align	2
	.type	DMA_DeInit,%function
	.code	16                      @ @DMA_DeInit
	.thumb_func
DMA_DeInit:
@ BB#0:
	ldr	r1, [r0]
	bic	r1, r1, #1
	str	r1, [r0]
	movs	r1, #0
	str	r1, [r0]
	str	r1, [r0, #4]
	str	r1, [r0, #8]
	str	r1, [r0, #12]
	str	r1, [r0, #16]
	movs	r1, #33
	str	r1, [r0, #20]
	movw	r1, #24615
	movt	r1, #16386
	cmp	r0, r1
	bgt	.LBB174_4
@ BB#1:
	movw	r1, #24592
	movt	r1, #16386
	cmp	r0, r1
	bne.w	.LBB174_33
@ BB#2:
	movw	r0, #24584
.LBB174_3:
	movt	r0, #16386
	movs	r1, #61
	b	.LBB174_32
.LBB174_4:
	movw	r1, #24639
	movt	r1, #16386
	cmp	r0, r1
	bgt	.LBB174_8
@ BB#5:
	movw	r1, #24616
	movt	r1, #16386
	cmp	r0, r1
	bne.w	.LBB174_33
@ BB#6:
	movw	r0, #24584
.LBB174_7:
	movt	r0, #16386
	mov.w	r1, #3904
	b	.LBB174_32
.LBB174_8:
	movw	r1, #24663
	movt	r1, #16386
	cmp	r0, r1
	bgt	.LBB174_12
@ BB#9:
	movw	r1, #24640
	movt	r1, #16386
	cmp	r0, r1
	bne	.LBB174_33
@ BB#10:
	movw	r0, #24584
.LBB174_11:
	movt	r0, #16386
	mov.w	r1, #3997696
	b	.LBB174_32
.LBB174_12:
	movw	r1, #24687
	movt	r1, #16386
	cmp	r0, r1
	bgt	.LBB174_16
@ BB#13:
	movw	r1, #24664
	movt	r1, #16386
	cmp	r0, r1
	bne	.LBB174_33
@ BB#14:
	movw	r0, #24584
.LBB174_15:
	movt	r0, #16386
	mov.w	r1, #255852544
	b	.LBB174_32
.LBB174_16:
	movw	r1, #24711
	movt	r1, #16386
	cmp	r0, r1
	bgt	.LBB174_20
@ BB#17:
	movw	r1, #24688
	movt	r1, #16386
	cmp	r0, r1
	bne	.LBB174_33
@ BB#18:
	movw	r0, #24588
.LBB174_19:
	movs	r1, #61
	movt	r0, #16386
	movt	r1, #8192
	b	.LBB174_32
.LBB174_20:
	movw	r1, #24735
	movt	r1, #16386
	cmp	r0, r1
	bgt	.LBB174_24
@ BB#21:
	movw	r1, #24712
	movt	r1, #16386
	cmp	r0, r1
	bne	.LBB174_33
@ BB#22:
	movw	r0, #24588
.LBB174_23:
	movw	r1, #3904
	movt	r0, #16386
	movt	r1, #8192
	b	.LBB174_32
.LBB174_24:
	movw	r1, #24759
	movt	r1, #16386
	cmp	r0, r1
	bgt	.LBB174_28
@ BB#25:
	movw	r1, #24736
	movt	r1, #16386
	cmp	r0, r1
	bne	.LBB174_33
@ BB#26:
	movw	r0, #24588
.LBB174_27:
	movs	r1, #0
	movt	r0, #16386
	movt	r1, #8253
	b	.LBB174_32
.LBB174_28:
	movw	r1, #25615
	movt	r1, #16386
	cmp	r0, r1
	bgt	.LBB174_34
@ BB#29:
	movw	r1, #24760
	movt	r1, #16386
	cmp	r0, r1
	bne	.LBB174_33
@ BB#30:
	movw	r0, #24588
.LBB174_31:
	movt	r0, #16386
	mov.w	r1, #792723456
.LBB174_32:
	str	r1, [r0]
.LBB174_33:
	bx	lr
.LBB174_34:
	movw	r1, #25639
	movt	r1, #16386
	cmp	r0, r1
	bgt	.LBB174_37
@ BB#35:
	movw	r1, #25616
	movt	r1, #16386
	cmp	r0, r1
	bne	.LBB174_33
@ BB#36:
	movw	r0, #25608
	b	.LBB174_3
.LBB174_37:
	movw	r1, #25663
	movt	r1, #16386
	cmp	r0, r1
	bgt	.LBB174_40
@ BB#38:
	movw	r1, #25640
	movt	r1, #16386
	cmp	r0, r1
	bne	.LBB174_33
@ BB#39:
	movw	r0, #25608
	b	.LBB174_7
.LBB174_40:
	movw	r1, #25687
	movt	r1, #16386
	cmp	r0, r1
	bgt	.LBB174_43
@ BB#41:
	movw	r1, #25664
	movt	r1, #16386
	cmp	r0, r1
	bne	.LBB174_33
@ BB#42:
	movw	r0, #25608
	b	.LBB174_11
.LBB174_43:
	movw	r1, #25711
	movt	r1, #16386
	cmp	r0, r1
	bgt	.LBB174_46
@ BB#44:
	movw	r1, #25688
	movt	r1, #16386
	cmp	r0, r1
	bne	.LBB174_33
@ BB#45:
	movw	r0, #25608
	b	.LBB174_15
.LBB174_46:
	movw	r1, #25735
	movt	r1, #16386
	cmp	r0, r1
	bgt	.LBB174_49
@ BB#47:
	movw	r1, #25712
	movt	r1, #16386
	cmp	r0, r1
	bne	.LBB174_33
@ BB#48:
	movw	r0, #25612
	b	.LBB174_19
.LBB174_49:
	movw	r1, #25736
	movt	r1, #16386
	cmp	r0, r1
	beq	.LBB174_52
@ BB#50:
	movw	r1, #25760
	movt	r1, #16386
	cmp	r0, r1
	bne	.LBB174_53
@ BB#51:
	movw	r0, #25612
	b	.LBB174_27
.LBB174_52:
	movw	r0, #25612
	b	.LBB174_23
.LBB174_53:
	movw	r1, #25784
	movt	r1, #16386
	cmp	r0, r1
	it	ne
	bxne	lr
	movw	r0, #25612
	b	.LBB174_31
.Ltmp174:
	.size	DMA_DeInit, .Ltmp174-DMA_DeInit

	.globl	DMA_Init
	.align	2
	.type	DMA_Init,%function
	.code	16                      @ @DMA_Init
	.thumb_func
DMA_Init:
@ BB#0:
	push	{r4, lr}
	ldr	r2, [r0]
	movw	r3, #32831
	ldr.w	lr, [r1, #20]
	ldr	r4, [r1, #24]
	movt	r3, #61468
	and.w	r12, r2, r3
	ldr	r3, [r1]
	ldr	r2, [r1, #12]
	orr.w	r3, r3, r12
	orrs	r2, r3
	ldr	r3, [r1, #28]
	orr.w	r2, r2, lr
	orrs	r2, r4
	orrs	r2, r3
	ldr	r3, [r1, #32]
	orrs	r2, r3
	ldr	r3, [r1, #36]
	orrs	r2, r3
	ldr	r3, [r1, #40]
	orrs	r2, r3
	ldr	r3, [r1, #52]
	orrs	r2, r3
	ldr	r3, [r1, #56]
	orrs	r2, r3
	str	r2, [r0]
	ldr	r2, [r0, #20]
	ldr	r3, [r1, #44]
	ldr	r4, [r1, #48]
	bic	r2, r2, #7
	orrs	r2, r3
	orrs	r2, r4
	str	r2, [r0, #20]
	ldr	r2, [r1, #16]
	str	r2, [r0, #4]
	ldr	r2, [r1, #4]
	str	r2, [r0, #8]
	ldr	r1, [r1, #8]
	str	r1, [r0, #12]
	pop	{r4, pc}
.Ltmp175:
	.size	DMA_Init, .Ltmp175-DMA_Init

	.globl	DMA_StructInit
	.align	2
	.type	DMA_StructInit,%function
	.code	16                      @ @DMA_StructInit
	.thumb_func
DMA_StructInit:
@ BB#0:
	movs	r1, #0
	str	r1, [r0]
	str	r1, [r0, #4]
	str	r1, [r0, #8]
	str	r1, [r0, #12]
	str	r1, [r0, #16]
	str	r1, [r0, #20]
	str	r1, [r0, #24]
	str	r1, [r0, #28]
	str	r1, [r0, #32]
	str	r1, [r0, #36]
	str	r1, [r0, #40]
	str	r1, [r0, #44]
	str	r1, [r0, #48]
	str	r1, [r0, #52]
	str	r1, [r0, #56]
	bx	lr
.Ltmp176:
	.size	DMA_StructInit, .Ltmp176-DMA_StructInit

	.globl	DMA_Cmd
	.align	2
	.type	DMA_Cmd,%function
	.code	16                      @ @DMA_Cmd
	.thumb_func
DMA_Cmd:
@ BB#0:
	ldr	r2, [r0]
	cmp	r1, #0
	ite	eq
	biceq	r1, r2, #1
	orrne	r1, r2, #1
	str	r1, [r0]
	bx	lr
.Ltmp177:
	.size	DMA_Cmd, .Ltmp177-DMA_Cmd

	.globl	DMA_PeriphIncOffsetSizeConfig
	.align	2
	.type	DMA_PeriphIncOffsetSizeConfig,%function
	.code	16                      @ @DMA_PeriphIncOffsetSizeConfig
	.thumb_func
DMA_PeriphIncOffsetSizeConfig:
@ BB#0:
	ldr	r2, [r0]
	cmp	r1, #0
	ite	eq
	biceq	r1, r2, #32768
	orrne	r1, r2, #32768
	str	r1, [r0]
	bx	lr
.Ltmp178:
	.size	DMA_PeriphIncOffsetSizeConfig, .Ltmp178-DMA_PeriphIncOffsetSizeConfig

	.globl	DMA_FlowControllerConfig
	.align	2
	.type	DMA_FlowControllerConfig,%function
	.code	16                      @ @DMA_FlowControllerConfig
	.thumb_func
DMA_FlowControllerConfig:
@ BB#0:
	ldr	r2, [r0]
	cmp	r1, #0
	ite	eq
	biceq	r1, r2, #32
	orrne	r1, r2, #32
	str	r1, [r0]
	bx	lr
.Ltmp179:
	.size	DMA_FlowControllerConfig, .Ltmp179-DMA_FlowControllerConfig

	.globl	DMA_SetCurrDataCounter
	.align	2
	.type	DMA_SetCurrDataCounter,%function
	.code	16                      @ @DMA_SetCurrDataCounter
	.thumb_func
DMA_SetCurrDataCounter:
@ BB#0:
	str	r1, [r0, #4]
	bx	lr
.Ltmp180:
	.size	DMA_SetCurrDataCounter, .Ltmp180-DMA_SetCurrDataCounter

	.globl	DMA_GetCurrDataCounter
	.align	2
	.type	DMA_GetCurrDataCounter,%function
	.code	16                      @ @DMA_GetCurrDataCounter
	.thumb_func
DMA_GetCurrDataCounter:
@ BB#0:
	ldr	r0, [r0, #4]
	uxth	r0, r0
	bx	lr
.Ltmp181:
	.size	DMA_GetCurrDataCounter, .Ltmp181-DMA_GetCurrDataCounter

	.globl	DMA_DoubleBufferModeConfig
	.align	2
	.type	DMA_DoubleBufferModeConfig,%function
	.code	16                      @ @DMA_DoubleBufferModeConfig
	.thumb_func
DMA_DoubleBufferModeConfig:
@ BB#0:
	ldr	r3, [r0]
	cmp	r2, #0
	ite	eq
	biceq	r2, r3, #524288
	orrne	r2, r3, #524288
	str	r2, [r0]
	str	r1, [r0, #16]
	bx	lr
.Ltmp182:
	.size	DMA_DoubleBufferModeConfig, .Ltmp182-DMA_DoubleBufferModeConfig

	.globl	DMA_DoubleBufferModeCmd
	.align	2
	.type	DMA_DoubleBufferModeCmd,%function
	.code	16                      @ @DMA_DoubleBufferModeCmd
	.thumb_func
DMA_DoubleBufferModeCmd:
@ BB#0:
	ldr	r2, [r0]
	cmp	r1, #0
	ite	eq
	biceq	r1, r2, #262144
	orrne	r1, r2, #262144
	str	r1, [r0]
	bx	lr
.Ltmp183:
	.size	DMA_DoubleBufferModeCmd, .Ltmp183-DMA_DoubleBufferModeCmd

	.globl	DMA_MemoryTargetConfig
	.align	2
	.type	DMA_MemoryTargetConfig,%function
	.code	16                      @ @DMA_MemoryTargetConfig
	.thumb_func
DMA_MemoryTargetConfig:
@ BB#0:
	cmp	r2, #0
	ite	eq
	streq	r1, [r0, #12]
	strne	r1, [r0, #16]
	bx	lr
.Ltmp184:
	.size	DMA_MemoryTargetConfig, .Ltmp184-DMA_MemoryTargetConfig

	.globl	DMA_GetCurrentMemoryTarget
	.align	2
	.type	DMA_GetCurrentMemoryTarget,%function
	.code	16                      @ @DMA_GetCurrentMemoryTarget
	.thumb_func
DMA_GetCurrentMemoryTarget:
@ BB#0:
	ldr	r0, [r0]
	ubfx	r0, r0, #19, #1
	bx	lr
.Ltmp185:
	.size	DMA_GetCurrentMemoryTarget, .Ltmp185-DMA_GetCurrentMemoryTarget

	.globl	DMA_GetCmdStatus
	.align	2
	.type	DMA_GetCmdStatus,%function
	.code	16                      @ @DMA_GetCmdStatus
	.thumb_func
DMA_GetCmdStatus:
@ BB#0:
	ldr	r0, [r0]
	and	r0, r0, #1
	bx	lr
.Ltmp186:
	.size	DMA_GetCmdStatus, .Ltmp186-DMA_GetCmdStatus

	.globl	DMA_GetFIFOStatus
	.align	2
	.type	DMA_GetFIFOStatus,%function
	.code	16                      @ @DMA_GetFIFOStatus
	.thumb_func
DMA_GetFIFOStatus:
@ BB#0:
	ldr	r0, [r0, #20]
	and	r0, r0, #56
	bx	lr
.Ltmp187:
	.size	DMA_GetFIFOStatus, .Ltmp187-DMA_GetFIFOStatus

	.globl	DMA_GetFlagStatus
	.align	2
	.type	DMA_GetFlagStatus,%function
	.code	16                      @ @DMA_GetFlagStatus
	.thumb_func
DMA_GetFlagStatus:
@ BB#0:
	movw	r2, #25616
	movw	r3, #25600
	movt	r2, #16386
	movt	r3, #16386
	cmp	r0, r2
	itt	lo
	movwlo	r3, #24576
	movtlo	r3, #16386
	tst.w	r1, #536870912
	it	ne
	orrne	r3, r3, #4
	ldr	r0, [r3]
	ands	r0, r1
	movw	r1, #3965
	movt	r1, #3965
	ands	r0, r1
	it	ne
	movne	r0, #1
	bx	lr
.Ltmp188:
	.size	DMA_GetFlagStatus, .Ltmp188-DMA_GetFlagStatus

	.globl	DMA_ClearFlag
	.align	2
	.type	DMA_ClearFlag,%function
	.code	16                      @ @DMA_ClearFlag
	.thumb_func
DMA_ClearFlag:
@ BB#0:
	movw	r3, #25616
	movw	r2, #25600
	movt	r3, #16386
	movt	r2, #16386
	cmp	r0, r3
	movw	r0, #3965
	movt	r0, #3965
	itt	lo
	movwlo	r2, #24576
	movtlo	r2, #16386
	tst.w	r1, #536870912
	and.w	r0, r0, r1
	ite	eq
	streq	r0, [r2, #8]
	strne	r0, [r2, #12]
	bx	lr
.Ltmp189:
	.size	DMA_ClearFlag, .Ltmp189-DMA_ClearFlag

	.globl	DMA_ITConfig
	.align	2
	.type	DMA_ITConfig,%function
	.code	16                      @ @DMA_ITConfig
	.thumb_func
DMA_ITConfig:
@ BB#0:
	tst.w	r1, #128
	beq	.LBB190_2
@ BB#1:
	ldr	r3, [r0, #20]
	cmp	r2, #0
	ite	eq
	biceq	r3, r3, #128
	orrne	r3, r3, #128
	str	r3, [r0, #20]
.LBB190_2:
	cmp	r1, #128
	it	eq
	bxeq	lr
	cbz	r2, .LBB190_4
.LBB190_3:
	ldr	r2, [r0]
	and	r1, r1, #30
	orrs	r1, r2
	b	.LBB190_5
.LBB190_4:
	ldr	r2, [r0]
	orn	r1, r1, #30
	eor	r1, r1, #30
	ands	r1, r2
.LBB190_5:
	str	r1, [r0]
	bx	lr
.Ltmp190:
	.size	DMA_ITConfig, .Ltmp190-DMA_ITConfig

	.globl	DMA_GetITStatus
	.align	2
	.type	DMA_GetITStatus,%function
	.code	16                      @ @DMA_GetITStatus
	.thumb_func
DMA_GetITStatus:
@ BB#0:
	movw	r3, #25616
	movw	r2, #25600
	movt	r3, #16386
	movt	r2, #16386
	cmp	r0, r3
	movw	r3, #3900
	itt	lo
	movwlo	r2, #24576
	movtlo	r2, #16386
	movt	r3, #3900
	tst	r1, r3
	beq	.LBB191_2
@ BB#1:
	ldr	r0, [r0]
	and.w	r0, r0, r1, lsr #11
	and	r0, r0, #30
	b	.LBB191_3
.LBB191_2:
	ldr	r0, [r0, #20]
	and	r0, r0, #128
.LBB191_3:
	tst.w	r1, #536870912
	it	ne
	addne	r2, #4
	ldr	r2, [r2]
	ands	r1, r2
	movw	r2, #3965
	movt	r2, #3965
	ands	r1, r2
	it	ne
	movne	r1, #1
	cmp	r0, #0
	it	ne
	movne	r0, #1
	ands	r0, r1
	bx	lr
.Ltmp191:
	.size	DMA_GetITStatus, .Ltmp191-DMA_GetITStatus

	.globl	DMA_ClearITPendingBit
	.align	2
	.type	DMA_ClearITPendingBit,%function
	.code	16                      @ @DMA_ClearITPendingBit
	.thumb_func
DMA_ClearITPendingBit:
@ BB#0:
	movw	r3, #25616
	movw	r2, #25600
	movt	r3, #16386
	movt	r2, #16386
	cmp	r0, r3
	movw	r0, #3965
	movt	r0, #3965
	itt	lo
	movwlo	r2, #24576
	movtlo	r2, #16386
	tst.w	r1, #536870912
	and.w	r0, r0, r1
	ite	eq
	streq	r0, [r2, #8]
	strne	r0, [r2, #12]
	bx	lr
.Ltmp192:
	.size	DMA_ClearITPendingBit, .Ltmp192-DMA_ClearITPendingBit

	.globl	EXTI_DeInit
	.align	2
	.type	EXTI_DeInit,%function
	.code	16                      @ @EXTI_DeInit
	.thumb_func
EXTI_DeInit:
@ BB#0:
	movw	r0, #15360
	movs	r1, #0
	movt	r0, #16385
	str	r1, [r0]
	movw	r0, #15364
	movt	r0, #16385
	str	r1, [r0]
	movw	r0, #15368
	movt	r0, #16385
	str	r1, [r0]
	movw	r0, #15372
	movt	r0, #16385
	str	r1, [r0]
	movw	r0, #15380
	movw	r1, #65535
	movt	r0, #16385
	movt	r1, #127
	str	r1, [r0]
	bx	lr
.Ltmp193:
	.size	EXTI_DeInit, .Ltmp193-EXTI_DeInit

	.globl	EXTI_Init
	.align	2
	.type	EXTI_Init,%function
	.code	16                      @ @EXTI_Init
	.thumb_func
EXTI_Init:
@ BB#0:
	push.w	{r11, lr}
	ldr	r1, [r0, #12]
	cbz	r1, .LBB194_3
@ BB#1:
	movw	lr, #15360
	ldr	r2, [r0]
	movw	r12, #15368
	movt	lr, #16385
	movt	r12, #16385
	ldr.w	r3, [lr]
	bic.w	r2, r3, r2
	movw	r3, #15364
	str.w	r2, [lr]
	movt	r3, #16385
	ldr	r2, [r0]
	ldr	r1, [r3]
	bics	r1, r2
	str	r1, [r3]
	ldm.w	r0, {r1, r2}
	ldr.w	r3, [r2, lr]
	orrs	r1, r3
	movw	r3, #15372
	str.w	r1, [r2, lr]
	movt	r3, #16385
	ldr	r1, [r0]
	ldr.w	r2, [r12]
	bic.w	r1, r2, r1
	str.w	r1, [r12]
	ldr	r1, [r0]
	ldr	r2, [r3]
	bic.w	r1, r2, r1
	str	r1, [r3]
	ldr	r2, [r0, #8]
	cmp	r2, #16
	bne	.LBB194_4
@ BB#2:
	ldr	r1, [r0]
	ldr.w	r2, [r12]
	orrs	r1, r2
	str.w	r1, [r12]
	ldr	r0, [r0]
	ldr	r1, [r3]
	orrs	r0, r1
	str	r0, [r3]
	pop.w	{r11, pc}
.LBB194_3:
	ldr	r1, [r0]
	ldr	r0, [r0, #4]
	movw	r2, #15360
	movt	r2, #16385
	ldr	r3, [r0, r2]
	bic.w	r1, r3, r1
	str	r1, [r0, r2]
	pop.w	{r11, pc}
.LBB194_4:
	ldr	r0, [r0]
	ldr.w	r1, [r2, lr]
	orrs	r0, r1
	str.w	r0, [r2, lr]
	pop.w	{r11, pc}
.Ltmp194:
	.size	EXTI_Init, .Ltmp194-EXTI_Init

	.globl	EXTI_StructInit
	.align	2
	.type	EXTI_StructInit,%function
	.code	16                      @ @EXTI_StructInit
	.thumb_func
EXTI_StructInit:
@ BB#0:
	movs	r1, #0
	movs	r2, #12
	str	r1, [r0]
	str	r1, [r0, #4]
	str	r2, [r0, #8]
	str	r1, [r0, #12]
	bx	lr
.Ltmp195:
	.size	EXTI_StructInit, .Ltmp195-EXTI_StructInit

	.globl	EXTI_GenerateSWInterrupt
	.align	2
	.type	EXTI_GenerateSWInterrupt,%function
	.code	16                      @ @EXTI_GenerateSWInterrupt
	.thumb_func
EXTI_GenerateSWInterrupt:
@ BB#0:
	movw	r1, #15376
	movt	r1, #16385
	ldr	r2, [r1]
	orrs	r0, r2
	str	r0, [r1]
	bx	lr
.Ltmp196:
	.size	EXTI_GenerateSWInterrupt, .Ltmp196-EXTI_GenerateSWInterrupt

	.globl	EXTI_GetFlagStatus
	.align	2
	.type	EXTI_GetFlagStatus,%function
	.code	16                      @ @EXTI_GetFlagStatus
	.thumb_func
EXTI_GetFlagStatus:
@ BB#0:
	movw	r1, #15380
	movt	r1, #16385
	ldr	r1, [r1]
	ands	r0, r1
	it	ne
	movne	r0, #1
	bx	lr
.Ltmp197:
	.size	EXTI_GetFlagStatus, .Ltmp197-EXTI_GetFlagStatus

	.globl	EXTI_ClearFlag
	.align	2
	.type	EXTI_ClearFlag,%function
	.code	16                      @ @EXTI_ClearFlag
	.thumb_func
EXTI_ClearFlag:
@ BB#0:
	movw	r1, #15380
	movt	r1, #16385
	str	r0, [r1]
	bx	lr
.Ltmp198:
	.size	EXTI_ClearFlag, .Ltmp198-EXTI_ClearFlag

	.globl	EXTI_GetITStatus
	.align	2
	.type	EXTI_GetITStatus,%function
	.code	16                      @ @EXTI_GetITStatus
	.thumb_func
EXTI_GetITStatus:
@ BB#0:
	movw	r1, #15360
	movw	r2, #15380
	movt	r1, #16385
	movt	r2, #16385
	ldr	r1, [r1]
	ands	r1, r0
	it	ne
	movne	r1, #1
	ldr	r2, [r2]
	ands	r0, r2
	it	ne
	movne	r0, #1
	ands	r0, r1
	bx	lr
.Ltmp199:
	.size	EXTI_GetITStatus, .Ltmp199-EXTI_GetITStatus

	.globl	EXTI_ClearITPendingBit
	.align	2
	.type	EXTI_ClearITPendingBit,%function
	.code	16                      @ @EXTI_ClearITPendingBit
	.thumb_func
EXTI_ClearITPendingBit:
@ BB#0:
	movw	r1, #15380
	movt	r1, #16385
	str	r0, [r1]
	bx	lr
.Ltmp200:
	.size	EXTI_ClearITPendingBit, .Ltmp200-EXTI_ClearITPendingBit

	.globl	FLASH_SetLatency
	.align	2
	.type	FLASH_SetLatency,%function
	.code	16                      @ @FLASH_SetLatency
	.thumb_func
FLASH_SetLatency:
@ BB#0:
	movw	r1, #15360
	movt	r1, #16386
	strb	r0, [r1]
	bx	lr
.Ltmp201:
	.size	FLASH_SetLatency, .Ltmp201-FLASH_SetLatency

	.globl	FLASH_PrefetchBufferCmd
	.align	2
	.type	FLASH_PrefetchBufferCmd,%function
	.code	16                      @ @FLASH_PrefetchBufferCmd
	.thumb_func
FLASH_PrefetchBufferCmd:
@ BB#0:
	movw	r1, #15360
	cmp	r0, #0
	movt	r1, #16386
	ldr	r2, [r1]
	ite	eq
	biceq	r0, r2, #256
	orrne	r0, r2, #256
	str	r0, [r1]
	bx	lr
.Ltmp202:
	.size	FLASH_PrefetchBufferCmd, .Ltmp202-FLASH_PrefetchBufferCmd

	.globl	FLASH_InstructionCacheCmd
	.align	2
	.type	FLASH_InstructionCacheCmd,%function
	.code	16                      @ @FLASH_InstructionCacheCmd
	.thumb_func
FLASH_InstructionCacheCmd:
@ BB#0:
	movw	r1, #15360
	cmp	r0, #0
	movt	r1, #16386
	ldr	r2, [r1]
	ite	eq
	biceq	r0, r2, #512
	orrne	r0, r2, #512
	str	r0, [r1]
	bx	lr
.Ltmp203:
	.size	FLASH_InstructionCacheCmd, .Ltmp203-FLASH_InstructionCacheCmd

	.globl	FLASH_DataCacheCmd
	.align	2
	.type	FLASH_DataCacheCmd,%function
	.code	16                      @ @FLASH_DataCacheCmd
	.thumb_func
FLASH_DataCacheCmd:
@ BB#0:
	movw	r1, #15360
	cmp	r0, #0
	movt	r1, #16386
	ldr	r2, [r1]
	ite	eq
	biceq	r0, r2, #1024
	orrne	r0, r2, #1024
	str	r0, [r1]
	bx	lr
.Ltmp204:
	.size	FLASH_DataCacheCmd, .Ltmp204-FLASH_DataCacheCmd

	.globl	FLASH_InstructionCacheReset
	.align	2
	.type	FLASH_InstructionCacheReset,%function
	.code	16                      @ @FLASH_InstructionCacheReset
	.thumb_func
FLASH_InstructionCacheReset:
@ BB#0:
	movw	r0, #15360
	movt	r0, #16386
	ldr	r1, [r0]
	orr	r1, r1, #2048
	str	r1, [r0]
	bx	lr
.Ltmp205:
	.size	FLASH_InstructionCacheReset, .Ltmp205-FLASH_InstructionCacheReset

	.globl	FLASH_DataCacheReset
	.align	2
	.type	FLASH_DataCacheReset,%function
	.code	16                      @ @FLASH_DataCacheReset
	.thumb_func
FLASH_DataCacheReset:
@ BB#0:
	movw	r0, #15360
	movt	r0, #16386
	ldr	r1, [r0]
	orr	r1, r1, #4096
	str	r1, [r0]
	bx	lr
.Ltmp206:
	.size	FLASH_DataCacheReset, .Ltmp206-FLASH_DataCacheReset

	.globl	FLASH_Unlock
	.align	2
	.type	FLASH_Unlock,%function
	.code	16                      @ @FLASH_Unlock
	.thumb_func
FLASH_Unlock:
@ BB#0:
	movw	r0, #15376
	movt	r0, #16386
	ldr	r0, [r0]
	cmp.w	r0, #-1
	it	gt
	bxgt	lr
	movw	r0, #15364
	movw	r1, #291
	movt	r0, #16386
	movt	r1, #17767
	str	r1, [r0]
	movw	r1, #35243
	movt	r1, #52719
	str	r1, [r0]
	bx	lr
.Ltmp207:
	.size	FLASH_Unlock, .Ltmp207-FLASH_Unlock

	.globl	FLASH_Lock
	.align	2
	.type	FLASH_Lock,%function
	.code	16                      @ @FLASH_Lock
	.thumb_func
FLASH_Lock:
@ BB#0:
	movw	r0, #15376
	movt	r0, #16386
	ldr	r1, [r0]
	orr	r1, r1, #-2147483648
	str	r1, [r0]
	bx	lr
.Ltmp208:
	.size	FLASH_Lock, .Ltmp208-FLASH_Lock

	.globl	FLASH_EraseSector
	.align	2
	.type	FLASH_EraseSector,%function
	.code	16                      @ @FLASH_EraseSector
	.thumb_func
FLASH_EraseSector:
@ BB#0:
	sub	sp, #8
	cmp	r1, #2
	bhi	.LBB209_2
@ BB#1:                                 @ %switch.lookup
	movw	r2, :lower16:.Lswitch.table1
	sxtb	r1, r1
	movt	r2, :upper16:.Lswitch.table1
	ldr.w	r12, [r2, r1, lsl #2]
	b	.LBB209_3
.LBB209_2:
	mov.w	r12, #768
.LBB209_3:
	movw	r2, #15372
	movs	r1, #8
	movt	r2, #16386
	str	r1, [sp]
	ldr	r1, [r2]
	tst.w	r1, #65536
	beq	.LBB209_5
@ BB#4:
	movs	r1, #1
	b	.LBB209_11
.LBB209_5:
	ldr	r1, [r2]
	tst.w	r1, #16
	beq	.LBB209_7
@ BB#6:
	movs	r1, #5
	b	.LBB209_11
.LBB209_7:
	ldr	r1, [r2]
	tst.w	r1, #239
	beq	.LBB209_9
@ BB#8:
	movs	r1, #6
	b	.LBB209_11
.LBB209_9:
	ldr	r1, [r2]
	ubfx	r1, r1, #1, #1
	rsb.w	r1, r1, #8
	b	.LBB209_11
.LBB209_10:                             @   in Loop: Header=BB209_11 Depth=1
	movs	r1, #1
.LBB209_11:                             @ %FLASH_GetStatus.exit.i
                                        @ =>This Inner Loop Header: Depth=1
	str	r1, [sp]
	ldr	r1, [sp]
	cmp	r1, #1
	bne	.LBB209_17
@ BB#12:                                @ %.lr.ph.i
                                        @   in Loop: Header=BB209_11 Depth=1
	ldr	r1, [r2]
	tst.w	r1, #65536
	bne	.LBB209_10
@ BB#13:                                @   in Loop: Header=BB209_11 Depth=1
	ldr	r1, [r2]
	tst.w	r1, #16
	bne	.LBB209_16
@ BB#14:                                @   in Loop: Header=BB209_11 Depth=1
	ldr	r1, [r2]
	tst.w	r1, #239
	beq	.LBB209_9
@ BB#15:                                @   in Loop: Header=BB209_11 Depth=1
	movs	r1, #6
	b	.LBB209_11
.LBB209_16:                             @   in Loop: Header=BB209_11 Depth=1
	movs	r1, #5
	b	.LBB209_11
.LBB209_17:                             @ %FLASH_WaitForLastOperation.exit
	ldr	r1, [sp]
	cmp	r1, #8
	bne	.LBB209_33
@ BB#18:
	movw	r3, #15376
	movt	r3, #16386
	ldr	r1, [r3]
	bic	r1, r1, #768
	str	r1, [r3]
	ldr	r1, [r3]
	orr.w	r1, r1, r12
	str	r1, [r3]
	ldr	r1, [r3]
	bic	r1, r1, #248
	str	r1, [r3]
	ldr	r1, [r3]
	orrs	r0, r1
	orr	r0, r0, #2
	str	r0, [r3]
	ldr	r0, [r3]
	orr	r0, r0, #65536
	str	r0, [r3]
	movs	r0, #8
	str	r0, [sp, #4]
	ldr	r0, [r2]
	tst.w	r0, #65536
	beq	.LBB209_20
@ BB#19:
	movs	r0, #1
	b	.LBB209_26
.LBB209_20:
	ldr	r0, [r2]
	tst.w	r0, #16
	beq	.LBB209_22
@ BB#21:
	movs	r0, #5
	b	.LBB209_26
.LBB209_22:
	ldr	r0, [r2]
	tst.w	r0, #239
	beq	.LBB209_24
@ BB#23:
	movs	r0, #6
	b	.LBB209_26
.LBB209_24:
	ldr	r0, [r2]
	ubfx	r0, r0, #1, #1
	rsb.w	r0, r0, #8
	b	.LBB209_26
.LBB209_25:                             @   in Loop: Header=BB209_26 Depth=1
	movs	r0, #1
.LBB209_26:                             @ %FLASH_GetStatus.exit.i3
                                        @ =>This Inner Loop Header: Depth=1
	str	r0, [sp, #4]
	ldr	r0, [sp, #4]
	cmp	r0, #1
	bne	.LBB209_32
@ BB#27:                                @ %.lr.ph.i4
                                        @   in Loop: Header=BB209_26 Depth=1
	ldr	r0, [r2]
	tst.w	r0, #65536
	bne	.LBB209_25
@ BB#28:                                @   in Loop: Header=BB209_26 Depth=1
	ldr	r0, [r2]
	tst.w	r0, #16
	bne	.LBB209_31
@ BB#29:                                @   in Loop: Header=BB209_26 Depth=1
	ldr	r0, [r2]
	tst.w	r0, #239
	beq	.LBB209_24
@ BB#30:                                @   in Loop: Header=BB209_26 Depth=1
	movs	r0, #6
	b	.LBB209_26
.LBB209_31:                             @   in Loop: Header=BB209_26 Depth=1
	movs	r0, #5
	b	.LBB209_26
.LBB209_32:                             @ %FLASH_WaitForLastOperation.exit7
	ldr	r1, [sp, #4]
	ldr	r0, [r3]
	bic	r0, r0, #2
	str	r0, [r3]
	ldr	r0, [r3]
	bic	r0, r0, #248
	str	r0, [r3]
.LBB209_33:
	mov	r0, r1
	add	sp, #8
	bx	lr
.Ltmp209:
	.size	FLASH_EraseSector, .Ltmp209-FLASH_EraseSector

	.globl	FLASH_WaitForLastOperation
	.align	2
	.type	FLASH_WaitForLastOperation,%function
	.code	16                      @ @FLASH_WaitForLastOperation
	.thumb_func
FLASH_WaitForLastOperation:
@ BB#0:
	sub	sp, #8
	movs	r0, #8
	str	r0, [sp, #4]
	movw	r0, #15372
	movt	r0, #16386
	ldr	r1, [r0]
	tst.w	r1, #65536
	beq	.LBB210_2
@ BB#1:
	movs	r1, #1
	b	.LBB210_8
.LBB210_2:
	ldr	r1, [r0]
	tst.w	r1, #16
	beq	.LBB210_4
@ BB#3:
	movs	r1, #5
	b	.LBB210_8
.LBB210_4:
	ldr	r1, [r0]
	tst.w	r1, #239
	beq	.LBB210_6
@ BB#5:
	movs	r1, #6
	b	.LBB210_8
.LBB210_6:
	ldr	r1, [r0]
	ubfx	r1, r1, #1, #1
	rsb.w	r1, r1, #8
	b	.LBB210_8
.LBB210_7:                              @   in Loop: Header=BB210_8 Depth=1
	movs	r1, #1
.LBB210_8:                              @ %FLASH_GetStatus.exit
                                        @ =>This Inner Loop Header: Depth=1
	str	r1, [sp, #4]
	ldr	r1, [sp, #4]
	cmp	r1, #1
	ittt	ne
	ldrne	r0, [sp, #4]
	addne	sp, #8
	bxne	lr
	ldr	r1, [r0]
	tst.w	r1, #65536
	bne	.LBB210_7
@ BB#9:                                 @   in Loop: Header=BB210_8 Depth=1
	ldr	r1, [r0]
	tst.w	r1, #16
	bne	.LBB210_12
@ BB#10:                                @   in Loop: Header=BB210_8 Depth=1
	ldr	r1, [r0]
	tst.w	r1, #239
	beq	.LBB210_6
@ BB#11:                                @   in Loop: Header=BB210_8 Depth=1
	movs	r1, #6
	b	.LBB210_8
.LBB210_12:                             @   in Loop: Header=BB210_8 Depth=1
	movs	r1, #5
	b	.LBB210_8
.Ltmp210:
	.size	FLASH_WaitForLastOperation, .Ltmp210-FLASH_WaitForLastOperation

	.globl	FLASH_EraseAllSectors
	.align	2
	.type	FLASH_EraseAllSectors,%function
	.code	16                      @ @FLASH_EraseAllSectors
	.thumb_func
FLASH_EraseAllSectors:
@ BB#0:
	sub	sp, #8
	movw	r2, #15372
	movs	r1, #8
	movt	r2, #16386
	str	r1, [sp]
	ldr	r1, [r2]
	tst.w	r1, #65536
	beq	.LBB211_2
@ BB#1:
	movs	r1, #1
	b	.LBB211_8
.LBB211_2:
	ldr	r1, [r2]
	tst.w	r1, #16
	beq	.LBB211_4
@ BB#3:
	movs	r1, #5
	b	.LBB211_8
.LBB211_4:
	ldr	r1, [r2]
	tst.w	r1, #239
	beq	.LBB211_6
@ BB#5:
	movs	r1, #6
	b	.LBB211_8
.LBB211_6:
	ldr	r1, [r2]
	ubfx	r1, r1, #1, #1
	rsb.w	r1, r1, #8
	b	.LBB211_8
.LBB211_7:                              @   in Loop: Header=BB211_8 Depth=1
	movs	r1, #1
.LBB211_8:                              @ %FLASH_GetStatus.exit.i
                                        @ =>This Inner Loop Header: Depth=1
	str	r1, [sp]
	ldr	r1, [sp]
	cmp	r1, #1
	bne	.LBB211_14
@ BB#9:                                 @ %.lr.ph.i
                                        @   in Loop: Header=BB211_8 Depth=1
	ldr	r1, [r2]
	tst.w	r1, #65536
	bne	.LBB211_7
@ BB#10:                                @   in Loop: Header=BB211_8 Depth=1
	ldr	r1, [r2]
	tst.w	r1, #16
	bne	.LBB211_13
@ BB#11:                                @   in Loop: Header=BB211_8 Depth=1
	ldr	r1, [r2]
	tst.w	r1, #239
	beq	.LBB211_6
@ BB#12:                                @   in Loop: Header=BB211_8 Depth=1
	movs	r1, #6
	b	.LBB211_8
.LBB211_13:                             @   in Loop: Header=BB211_8 Depth=1
	movs	r1, #5
	b	.LBB211_8
.LBB211_14:                             @ %FLASH_WaitForLastOperation.exit
	ldr	r1, [sp]
	cmp	r0, #2
	bhi	.LBB211_16
@ BB#15:                                @ %switch.lookup
	movw	r3, :lower16:.Lswitch.table1
	sxtb	r0, r0
	movt	r3, :upper16:.Lswitch.table1
	ldr.w	r3, [r3, r0, lsl #2]
	b	.LBB211_17
.LBB211_16:
	mov.w	r3, #768
.LBB211_17:
	cmp	r1, #8
	bne	.LBB211_33
@ BB#18:
	movw	r0, #15376
	movt	r0, #16386
	ldr	r1, [r0]
	bic	r1, r1, #768
	str	r1, [r0]
	ldr	r1, [r0]
	orrs	r1, r3
	str	r1, [r0]
	ldr	r1, [r0]
	orr	r1, r1, #4
	str	r1, [r0]
	ldr	r1, [r0]
	orr	r1, r1, #65536
	str	r1, [r0]
	movs	r1, #8
	str	r1, [sp, #4]
	ldr	r1, [r2]
	tst.w	r1, #65536
	beq	.LBB211_20
@ BB#19:
	movs	r1, #1
	b	.LBB211_26
.LBB211_20:
	ldr	r1, [r2]
	tst.w	r1, #16
	beq	.LBB211_22
@ BB#21:
	movs	r1, #5
	b	.LBB211_26
.LBB211_22:
	ldr	r1, [r2]
	tst.w	r1, #239
	beq	.LBB211_24
@ BB#23:
	movs	r1, #6
	b	.LBB211_26
.LBB211_24:
	ldr	r1, [r2]
	ubfx	r1, r1, #1, #1
	rsb.w	r1, r1, #8
	b	.LBB211_26
.LBB211_25:                             @   in Loop: Header=BB211_26 Depth=1
	movs	r1, #1
.LBB211_26:                             @ %FLASH_GetStatus.exit.i3
                                        @ =>This Inner Loop Header: Depth=1
	str	r1, [sp, #4]
	ldr	r1, [sp, #4]
	cmp	r1, #1
	bne	.LBB211_32
@ BB#27:                                @ %.lr.ph.i4
                                        @   in Loop: Header=BB211_26 Depth=1
	ldr	r1, [r2]
	tst.w	r1, #65536
	bne	.LBB211_25
@ BB#28:                                @   in Loop: Header=BB211_26 Depth=1
	ldr	r1, [r2]
	tst.w	r1, #16
	bne	.LBB211_31
@ BB#29:                                @   in Loop: Header=BB211_26 Depth=1
	ldr	r1, [r2]
	tst.w	r1, #239
	beq	.LBB211_24
@ BB#30:                                @   in Loop: Header=BB211_26 Depth=1
	movs	r1, #6
	b	.LBB211_26
.LBB211_31:                             @   in Loop: Header=BB211_26 Depth=1
	movs	r1, #5
	b	.LBB211_26
.LBB211_32:                             @ %FLASH_WaitForLastOperation.exit7
	ldr	r1, [sp, #4]
	ldr	r2, [r0]
	bic	r2, r2, #4
	str	r2, [r0]
.LBB211_33:
	mov	r0, r1
	add	sp, #8
	bx	lr
.Ltmp211:
	.size	FLASH_EraseAllSectors, .Ltmp211-FLASH_EraseAllSectors

	.globl	FLASH_ProgramDoubleWord
	.align	2
	.type	FLASH_ProgramDoubleWord,%function
	.code	16                      @ @FLASH_ProgramDoubleWord
	.thumb_func
FLASH_ProgramDoubleWord:
@ BB#0:
	push	{r4, lr}
	sub	sp, #8
	movw	r4, #15372
	movs	r1, #8
	movt	r4, #16386
	str	r1, [sp]
	ldr	r1, [r4]
	tst.w	r1, #65536
	beq	.LBB212_2
@ BB#1:
	mov.w	r12, #1
	b	.LBB212_7
.LBB212_2:
	ldr	r1, [r4]
	tst.w	r1, #16
	beq	.LBB212_4
@ BB#3:
	mov.w	r12, #5
	b	.LBB212_7
.LBB212_4:
	ldr	r1, [r4]
	tst.w	r1, #239
	beq	.LBB212_6
@ BB#5:
	mov.w	r12, #6
	b	.LBB212_7
.LBB212_6:
	ldr	r1, [r4]
	ubfx	r1, r1, #1, #1
	rsb.w	r12, r1, #8
.LBB212_7:                              @ %FLASH_GetStatus.exit.i
	str.w	r12, [sp]
	b	.LBB212_9
.LBB212_8:                              @   in Loop: Header=BB212_9 Depth=1
	movs	r1, #1
	str	r1, [sp]
.LBB212_9:                              @ %FLASH_GetStatus.exit.i
                                        @ =>This Inner Loop Header: Depth=1
	ldr	r1, [sp]
	cmp	r1, #1
	bne	.LBB212_16
@ BB#10:                                @ %.lr.ph.i
                                        @   in Loop: Header=BB212_9 Depth=1
	ldr	r1, [r4]
	tst.w	r1, #65536
	bne	.LBB212_8
@ BB#11:                                @   in Loop: Header=BB212_9 Depth=1
	ldr	r1, [r4]
	tst.w	r1, #16
	bne	.LBB212_14
@ BB#12:                                @   in Loop: Header=BB212_9 Depth=1
	ldr	r1, [r4]
	tst.w	r1, #239
	bne	.LBB212_15
@ BB#13:                                @   in Loop: Header=BB212_9 Depth=1
	ldr	r1, [r4]
	ubfx	r1, r1, #1, #1
	rsb.w	r1, r1, #8
	str	r1, [sp]
	b	.LBB212_9
.LBB212_14:                             @   in Loop: Header=BB212_9 Depth=1
	movs	r1, #5
	str	r1, [sp]
	b	.LBB212_9
.LBB212_15:                             @   in Loop: Header=BB212_9 Depth=1
	movs	r1, #6
	str	r1, [sp]
	b	.LBB212_9
.LBB212_16:                             @ %FLASH_WaitForLastOperation.exit
	ldr.w	r12, [sp]
	cmp.w	r12, #8
	bne	.LBB212_32
@ BB#17:
	movw	lr, #15376
	movt	lr, #16386
	ldr.w	r1, [lr]
	bic	r1, r1, #768
	str.w	r1, [lr]
	ldr.w	r1, [lr]
	orr	r1, r1, #768
	str.w	r1, [lr]
	ldr.w	r1, [lr]
	orr	r1, r1, #1
	str.w	r1, [lr]
	str	r3, [r0, #4]
	str	r2, [r0]
	movs	r0, #8
	str	r0, [sp, #4]
	ldr	r0, [r4]
	tst.w	r0, #65536
	beq	.LBB212_19
@ BB#18:
	movs	r0, #1
	b	.LBB212_25
.LBB212_19:
	ldr	r0, [r4]
	tst.w	r0, #16
	beq	.LBB212_21
@ BB#20:
	movs	r0, #5
	b	.LBB212_25
.LBB212_21:
	ldr	r0, [r4]
	tst.w	r0, #239
	beq	.LBB212_23
@ BB#22:
	movs	r0, #6
	b	.LBB212_25
.LBB212_23:
	ldr	r0, [r4]
	ubfx	r0, r0, #1, #1
	rsb.w	r0, r0, #8
	b	.LBB212_25
.LBB212_24:                             @   in Loop: Header=BB212_25 Depth=1
	movs	r0, #1
.LBB212_25:                             @ %FLASH_GetStatus.exit.i3
                                        @ =>This Inner Loop Header: Depth=1
	str	r0, [sp, #4]
	ldr	r0, [sp, #4]
	cmp	r0, #1
	bne	.LBB212_31
@ BB#26:                                @ %.lr.ph.i4
                                        @   in Loop: Header=BB212_25 Depth=1
	ldr	r0, [r4]
	tst.w	r0, #65536
	bne	.LBB212_24
@ BB#27:                                @   in Loop: Header=BB212_25 Depth=1
	ldr	r0, [r4]
	tst.w	r0, #16
	bne	.LBB212_30
@ BB#28:                                @   in Loop: Header=BB212_25 Depth=1
	ldr	r0, [r4]
	tst.w	r0, #239
	beq	.LBB212_23
@ BB#29:                                @   in Loop: Header=BB212_25 Depth=1
	movs	r0, #6
	b	.LBB212_25
.LBB212_30:                             @   in Loop: Header=BB212_25 Depth=1
	movs	r0, #5
	b	.LBB212_25
.LBB212_31:                             @ %FLASH_WaitForLastOperation.exit7
	ldr.w	r12, [sp, #4]
	ldr.w	r0, [lr]
	bic	r0, r0, #1
	str.w	r0, [lr]
.LBB212_32:
	mov	r0, r12
	add	sp, #8
	pop	{r4, pc}
.Ltmp212:
	.size	FLASH_ProgramDoubleWord, .Ltmp212-FLASH_ProgramDoubleWord

	.globl	FLASH_ProgramWord
	.align	2
	.type	FLASH_ProgramWord,%function
	.code	16                      @ @FLASH_ProgramWord
	.thumb_func
FLASH_ProgramWord:
@ BB#0:
	sub	sp, #8
	movw	r3, #15372
	movs	r2, #8
	movt	r3, #16386
	str	r2, [sp]
	ldr	r2, [r3]
	tst.w	r2, #65536
	beq	.LBB213_2
@ BB#1:
	movs	r2, #1
	b	.LBB213_8
.LBB213_2:
	ldr	r2, [r3]
	tst.w	r2, #16
	beq	.LBB213_4
@ BB#3:
	movs	r2, #5
	b	.LBB213_8
.LBB213_4:
	ldr	r2, [r3]
	tst.w	r2, #239
	beq	.LBB213_6
@ BB#5:
	movs	r2, #6
	b	.LBB213_8
.LBB213_6:
	ldr	r2, [r3]
	ubfx	r2, r2, #1, #1
	rsb.w	r2, r2, #8
	b	.LBB213_8
.LBB213_7:                              @   in Loop: Header=BB213_8 Depth=1
	movs	r2, #1
.LBB213_8:                              @ %FLASH_GetStatus.exit.i
                                        @ =>This Inner Loop Header: Depth=1
	str	r2, [sp]
	ldr	r2, [sp]
	cmp	r2, #1
	bne	.LBB213_14
@ BB#9:                                 @ %.lr.ph.i
                                        @   in Loop: Header=BB213_8 Depth=1
	ldr	r2, [r3]
	tst.w	r2, #65536
	bne	.LBB213_7
@ BB#10:                                @   in Loop: Header=BB213_8 Depth=1
	ldr	r2, [r3]
	tst.w	r2, #16
	bne	.LBB213_13
@ BB#11:                                @   in Loop: Header=BB213_8 Depth=1
	ldr	r2, [r3]
	tst.w	r2, #239
	beq	.LBB213_6
@ BB#12:                                @   in Loop: Header=BB213_8 Depth=1
	movs	r2, #6
	b	.LBB213_8
.LBB213_13:                             @   in Loop: Header=BB213_8 Depth=1
	movs	r2, #5
	b	.LBB213_8
.LBB213_14:                             @ %FLASH_WaitForLastOperation.exit
	ldr	r2, [sp]
	cmp	r2, #8
	bne	.LBB213_30
@ BB#15:
	movw	r12, #15376
	movt	r12, #16386
	ldr.w	r2, [r12]
	bic	r2, r2, #768
	str.w	r2, [r12]
	ldr.w	r2, [r12]
	orr	r2, r2, #512
	str.w	r2, [r12]
	ldr.w	r2, [r12]
	orr	r2, r2, #1
	str.w	r2, [r12]
	str	r1, [r0]
	movs	r0, #8
	str	r0, [sp, #4]
	ldr	r0, [r3]
	tst.w	r0, #65536
	beq	.LBB213_17
@ BB#16:
	movs	r0, #1
	b	.LBB213_23
.LBB213_17:
	ldr	r0, [r3]
	tst.w	r0, #16
	beq	.LBB213_19
@ BB#18:
	movs	r0, #5
	b	.LBB213_23
.LBB213_19:
	ldr	r0, [r3]
	tst.w	r0, #239
	beq	.LBB213_21
@ BB#20:
	movs	r0, #6
	b	.LBB213_23
.LBB213_21:
	ldr	r0, [r3]
	ubfx	r0, r0, #1, #1
	rsb.w	r0, r0, #8
	b	.LBB213_23
.LBB213_22:                             @   in Loop: Header=BB213_23 Depth=1
	movs	r0, #1
.LBB213_23:                             @ %FLASH_GetStatus.exit.i3
                                        @ =>This Inner Loop Header: Depth=1
	str	r0, [sp, #4]
	ldr	r0, [sp, #4]
	cmp	r0, #1
	bne	.LBB213_29
@ BB#24:                                @ %.lr.ph.i4
                                        @   in Loop: Header=BB213_23 Depth=1
	ldr	r0, [r3]
	tst.w	r0, #65536
	bne	.LBB213_22
@ BB#25:                                @   in Loop: Header=BB213_23 Depth=1
	ldr	r0, [r3]
	tst.w	r0, #16
	bne	.LBB213_28
@ BB#26:                                @   in Loop: Header=BB213_23 Depth=1
	ldr	r0, [r3]
	tst.w	r0, #239
	beq	.LBB213_21
@ BB#27:                                @   in Loop: Header=BB213_23 Depth=1
	movs	r0, #6
	b	.LBB213_23
.LBB213_28:                             @   in Loop: Header=BB213_23 Depth=1
	movs	r0, #5
	b	.LBB213_23
.LBB213_29:                             @ %FLASH_WaitForLastOperation.exit7
	ldr	r2, [sp, #4]
	ldr.w	r0, [r12]
	bic	r0, r0, #1
	str.w	r0, [r12]
.LBB213_30:
	mov	r0, r2
	add	sp, #8
	bx	lr
.Ltmp213:
	.size	FLASH_ProgramWord, .Ltmp213-FLASH_ProgramWord

	.globl	FLASH_ProgramHalfWord
	.align	2
	.type	FLASH_ProgramHalfWord,%function
	.code	16                      @ @FLASH_ProgramHalfWord
	.thumb_func
FLASH_ProgramHalfWord:
@ BB#0:
	sub	sp, #8
	movw	r3, #15372
	movs	r2, #8
	movt	r3, #16386
	str	r2, [sp]
	ldr	r2, [r3]
	tst.w	r2, #65536
	beq	.LBB214_2
@ BB#1:
	movs	r2, #1
	b	.LBB214_8
.LBB214_2:
	ldr	r2, [r3]
	tst.w	r2, #16
	beq	.LBB214_4
@ BB#3:
	movs	r2, #5
	b	.LBB214_8
.LBB214_4:
	ldr	r2, [r3]
	tst.w	r2, #239
	beq	.LBB214_6
@ BB#5:
	movs	r2, #6
	b	.LBB214_8
.LBB214_6:
	ldr	r2, [r3]
	ubfx	r2, r2, #1, #1
	rsb.w	r2, r2, #8
	b	.LBB214_8
.LBB214_7:                              @   in Loop: Header=BB214_8 Depth=1
	movs	r2, #1
.LBB214_8:                              @ %FLASH_GetStatus.exit.i
                                        @ =>This Inner Loop Header: Depth=1
	str	r2, [sp]
	ldr	r2, [sp]
	cmp	r2, #1
	bne	.LBB214_14
@ BB#9:                                 @ %.lr.ph.i
                                        @   in Loop: Header=BB214_8 Depth=1
	ldr	r2, [r3]
	tst.w	r2, #65536
	bne	.LBB214_7
@ BB#10:                                @   in Loop: Header=BB214_8 Depth=1
	ldr	r2, [r3]
	tst.w	r2, #16
	bne	.LBB214_13
@ BB#11:                                @   in Loop: Header=BB214_8 Depth=1
	ldr	r2, [r3]
	tst.w	r2, #239
	beq	.LBB214_6
@ BB#12:                                @   in Loop: Header=BB214_8 Depth=1
	movs	r2, #6
	b	.LBB214_8
.LBB214_13:                             @   in Loop: Header=BB214_8 Depth=1
	movs	r2, #5
	b	.LBB214_8
.LBB214_14:                             @ %FLASH_WaitForLastOperation.exit
	ldr	r2, [sp]
	cmp	r2, #8
	bne	.LBB214_30
@ BB#15:
	movw	r12, #15376
	movt	r12, #16386
	ldr.w	r2, [r12]
	bic	r2, r2, #768
	str.w	r2, [r12]
	ldr.w	r2, [r12]
	orr	r2, r2, #256
	str.w	r2, [r12]
	ldr.w	r2, [r12]
	orr	r2, r2, #1
	str.w	r2, [r12]
	strh	r1, [r0]
	movs	r0, #8
	str	r0, [sp, #4]
	ldr	r0, [r3]
	tst.w	r0, #65536
	beq	.LBB214_17
@ BB#16:
	movs	r0, #1
	b	.LBB214_23
.LBB214_17:
	ldr	r0, [r3]
	tst.w	r0, #16
	beq	.LBB214_19
@ BB#18:
	movs	r0, #5
	b	.LBB214_23
.LBB214_19:
	ldr	r0, [r3]
	tst.w	r0, #239
	beq	.LBB214_21
@ BB#20:
	movs	r0, #6
	b	.LBB214_23
.LBB214_21:
	ldr	r0, [r3]
	ubfx	r0, r0, #1, #1
	rsb.w	r0, r0, #8
	b	.LBB214_23
.LBB214_22:                             @   in Loop: Header=BB214_23 Depth=1
	movs	r0, #1
.LBB214_23:                             @ %FLASH_GetStatus.exit.i3
                                        @ =>This Inner Loop Header: Depth=1
	str	r0, [sp, #4]
	ldr	r0, [sp, #4]
	cmp	r0, #1
	bne	.LBB214_29
@ BB#24:                                @ %.lr.ph.i4
                                        @   in Loop: Header=BB214_23 Depth=1
	ldr	r0, [r3]
	tst.w	r0, #65536
	bne	.LBB214_22
@ BB#25:                                @   in Loop: Header=BB214_23 Depth=1
	ldr	r0, [r3]
	tst.w	r0, #16
	bne	.LBB214_28
@ BB#26:                                @   in Loop: Header=BB214_23 Depth=1
	ldr	r0, [r3]
	tst.w	r0, #239
	beq	.LBB214_21
@ BB#27:                                @   in Loop: Header=BB214_23 Depth=1
	movs	r0, #6
	b	.LBB214_23
.LBB214_28:                             @   in Loop: Header=BB214_23 Depth=1
	movs	r0, #5
	b	.LBB214_23
.LBB214_29:                             @ %FLASH_WaitForLastOperation.exit7
	ldr	r2, [sp, #4]
	ldr.w	r0, [r12]
	bic	r0, r0, #1
	str.w	r0, [r12]
.LBB214_30:
	mov	r0, r2
	add	sp, #8
	bx	lr
.Ltmp214:
	.size	FLASH_ProgramHalfWord, .Ltmp214-FLASH_ProgramHalfWord

	.globl	FLASH_ProgramByte
	.align	2
	.type	FLASH_ProgramByte,%function
	.code	16                      @ @FLASH_ProgramByte
	.thumb_func
FLASH_ProgramByte:
@ BB#0:
	sub	sp, #8
	movw	r3, #15372
	movs	r2, #8
	movt	r3, #16386
	str	r2, [sp]
	ldr	r2, [r3]
	tst.w	r2, #65536
	beq	.LBB215_2
@ BB#1:
	movs	r2, #1
	b	.LBB215_8
.LBB215_2:
	ldr	r2, [r3]
	tst.w	r2, #16
	beq	.LBB215_4
@ BB#3:
	movs	r2, #5
	b	.LBB215_8
.LBB215_4:
	ldr	r2, [r3]
	tst.w	r2, #239
	beq	.LBB215_6
@ BB#5:
	movs	r2, #6
	b	.LBB215_8
.LBB215_6:
	ldr	r2, [r3]
	ubfx	r2, r2, #1, #1
	rsb.w	r2, r2, #8
	b	.LBB215_8
.LBB215_7:                              @   in Loop: Header=BB215_8 Depth=1
	movs	r2, #1
.LBB215_8:                              @ %FLASH_GetStatus.exit.i
                                        @ =>This Inner Loop Header: Depth=1
	str	r2, [sp]
	ldr	r2, [sp]
	cmp	r2, #1
	bne	.LBB215_14
@ BB#9:                                 @ %.lr.ph.i
                                        @   in Loop: Header=BB215_8 Depth=1
	ldr	r2, [r3]
	tst.w	r2, #65536
	bne	.LBB215_7
@ BB#10:                                @   in Loop: Header=BB215_8 Depth=1
	ldr	r2, [r3]
	tst.w	r2, #16
	bne	.LBB215_13
@ BB#11:                                @   in Loop: Header=BB215_8 Depth=1
	ldr	r2, [r3]
	tst.w	r2, #239
	beq	.LBB215_6
@ BB#12:                                @   in Loop: Header=BB215_8 Depth=1
	movs	r2, #6
	b	.LBB215_8
.LBB215_13:                             @   in Loop: Header=BB215_8 Depth=1
	movs	r2, #5
	b	.LBB215_8
.LBB215_14:                             @ %FLASH_WaitForLastOperation.exit
	ldr	r2, [sp]
	cmp	r2, #8
	bne	.LBB215_30
@ BB#15:
	movw	r12, #15376
	movt	r12, #16386
	ldr.w	r2, [r12]
	bic	r2, r2, #768
	str.w	r2, [r12]
	ldr.w	r2, [r12]
	str.w	r2, [r12]
	ldr.w	r2, [r12]
	orr	r2, r2, #1
	str.w	r2, [r12]
	strb	r1, [r0]
	movs	r0, #8
	str	r0, [sp, #4]
	ldr	r0, [r3]
	tst.w	r0, #65536
	beq	.LBB215_17
@ BB#16:
	movs	r0, #1
	b	.LBB215_23
.LBB215_17:
	ldr	r0, [r3]
	tst.w	r0, #16
	beq	.LBB215_19
@ BB#18:
	movs	r0, #5
	b	.LBB215_23
.LBB215_19:
	ldr	r0, [r3]
	tst.w	r0, #239
	beq	.LBB215_21
@ BB#20:
	movs	r0, #6
	b	.LBB215_23
.LBB215_21:
	ldr	r0, [r3]
	ubfx	r0, r0, #1, #1
	rsb.w	r0, r0, #8
	b	.LBB215_23
.LBB215_22:                             @   in Loop: Header=BB215_23 Depth=1
	movs	r0, #1
.LBB215_23:                             @ %FLASH_GetStatus.exit.i3
                                        @ =>This Inner Loop Header: Depth=1
	str	r0, [sp, #4]
	ldr	r0, [sp, #4]
	cmp	r0, #1
	bne	.LBB215_29
@ BB#24:                                @ %.lr.ph.i4
                                        @   in Loop: Header=BB215_23 Depth=1
	ldr	r0, [r3]
	tst.w	r0, #65536
	bne	.LBB215_22
@ BB#25:                                @   in Loop: Header=BB215_23 Depth=1
	ldr	r0, [r3]
	tst.w	r0, #16
	bne	.LBB215_28
@ BB#26:                                @   in Loop: Header=BB215_23 Depth=1
	ldr	r0, [r3]
	tst.w	r0, #239
	beq	.LBB215_21
@ BB#27:                                @   in Loop: Header=BB215_23 Depth=1
	movs	r0, #6
	b	.LBB215_23
.LBB215_28:                             @   in Loop: Header=BB215_23 Depth=1
	movs	r0, #5
	b	.LBB215_23
.LBB215_29:                             @ %FLASH_WaitForLastOperation.exit7
	ldr	r2, [sp, #4]
	ldr.w	r0, [r12]
	bic	r0, r0, #1
	str.w	r0, [r12]
.LBB215_30:
	mov	r0, r2
	add	sp, #8
	bx	lr
.Ltmp215:
	.size	FLASH_ProgramByte, .Ltmp215-FLASH_ProgramByte

	.globl	FLASH_OB_Unlock
	.align	2
	.type	FLASH_OB_Unlock,%function
	.code	16                      @ @FLASH_OB_Unlock
	.thumb_func
FLASH_OB_Unlock:
@ BB#0:
	movw	r0, #15380
	movt	r0, #16386
	ldr	r0, [r0]
	tst.w	r0, #1
	it	eq
	bxeq	lr
	movw	r0, #15368
	movw	r1, #10811
	movt	r0, #16386
	movt	r1, #2073
	str	r1, [r0]
	movw	r1, #28287
	movt	r1, #19549
	str	r1, [r0]
	bx	lr
.Ltmp216:
	.size	FLASH_OB_Unlock, .Ltmp216-FLASH_OB_Unlock

	.globl	FLASH_OB_Lock
	.align	2
	.type	FLASH_OB_Lock,%function
	.code	16                      @ @FLASH_OB_Lock
	.thumb_func
FLASH_OB_Lock:
@ BB#0:
	movw	r0, #15380
	movt	r0, #16386
	ldr	r1, [r0]
	orr	r1, r1, #1
	str	r1, [r0]
	bx	lr
.Ltmp217:
	.size	FLASH_OB_Lock, .Ltmp217-FLASH_OB_Lock

	.globl	FLASH_OB_WRPConfig
	.align	2
	.type	FLASH_OB_WRPConfig,%function
	.code	16                      @ @FLASH_OB_WRPConfig
	.thumb_func
FLASH_OB_WRPConfig:
@ BB#0:
	sub	sp, #8
	movs	r2, #8
	str	r2, [sp, #4]
	movw	r2, #15372
	movt	r2, #16386
	ldr	r3, [r2]
	tst.w	r3, #65536
	beq	.LBB218_2
@ BB#1:
	movs	r3, #1
	b	.LBB218_8
.LBB218_2:
	ldr	r3, [r2]
	tst.w	r3, #16
	beq	.LBB218_4
@ BB#3:
	movs	r3, #5
	b	.LBB218_8
.LBB218_4:
	ldr	r3, [r2]
	tst.w	r3, #239
	beq	.LBB218_6
@ BB#5:
	movs	r3, #6
	b	.LBB218_8
.LBB218_6:
	ldr	r3, [r2]
	ubfx	r3, r3, #1, #1
	rsb.w	r3, r3, #8
	b	.LBB218_8
.LBB218_7:                              @   in Loop: Header=BB218_8 Depth=1
	movs	r3, #1
.LBB218_8:                              @ %FLASH_GetStatus.exit.i
                                        @ =>This Inner Loop Header: Depth=1
	str	r3, [sp, #4]
	ldr	r3, [sp, #4]
	cmp	r3, #1
	bne	.LBB218_14
@ BB#9:                                 @ %.lr.ph.i
                                        @   in Loop: Header=BB218_8 Depth=1
	ldr	r3, [r2]
	tst.w	r3, #65536
	bne	.LBB218_7
@ BB#10:                                @   in Loop: Header=BB218_8 Depth=1
	ldr	r3, [r2]
	tst.w	r3, #16
	bne	.LBB218_13
@ BB#11:                                @   in Loop: Header=BB218_8 Depth=1
	ldr	r3, [r2]
	tst.w	r3, #239
	beq	.LBB218_6
@ BB#12:                                @   in Loop: Header=BB218_8 Depth=1
	movs	r3, #6
	b	.LBB218_8
.LBB218_13:                             @   in Loop: Header=BB218_8 Depth=1
	movs	r3, #5
	b	.LBB218_8
.LBB218_14:                             @ %FLASH_WaitForLastOperation.exit
	ldr	r2, [sp, #4]
	cmp	r2, #8
	bne	.LBB218_16
@ BB#15:
	cmp	r1, #0
	movw	r1, #15382
	movt	r1, #16386
	ldrh	r2, [r1]
	ite	eq
	orreq	r0, r2
	bicne.w	r0, r2, r0
	strh	r0, [r1]
.LBB218_16:
	add	sp, #8
	bx	lr
.Ltmp218:
	.size	FLASH_OB_WRPConfig, .Ltmp218-FLASH_OB_WRPConfig

	.globl	FLASH_OB_RDPConfig
	.align	2
	.type	FLASH_OB_RDPConfig,%function
	.code	16                      @ @FLASH_OB_RDPConfig
	.thumb_func
FLASH_OB_RDPConfig:
@ BB#0:
	sub	sp, #8
	movs	r1, #8
	str	r1, [sp, #4]
	movw	r1, #15372
	movt	r1, #16386
	ldr	r2, [r1]
	tst.w	r2, #65536
	beq	.LBB219_2
@ BB#1:
	movs	r2, #1
	b	.LBB219_8
.LBB219_2:
	ldr	r2, [r1]
	tst.w	r2, #16
	beq	.LBB219_4
@ BB#3:
	movs	r2, #5
	b	.LBB219_8
.LBB219_4:
	ldr	r2, [r1]
	tst.w	r2, #239
	beq	.LBB219_6
@ BB#5:
	movs	r2, #6
	b	.LBB219_8
.LBB219_6:
	ldr	r2, [r1]
	ubfx	r2, r2, #1, #1
	rsb.w	r2, r2, #8
	b	.LBB219_8
.LBB219_7:                              @   in Loop: Header=BB219_8 Depth=1
	movs	r2, #1
.LBB219_8:                              @ %FLASH_GetStatus.exit.i
                                        @ =>This Inner Loop Header: Depth=1
	str	r2, [sp, #4]
	ldr	r2, [sp, #4]
	cmp	r2, #1
	bne	.LBB219_14
@ BB#9:                                 @ %.lr.ph.i
                                        @   in Loop: Header=BB219_8 Depth=1
	ldr	r2, [r1]
	tst.w	r2, #65536
	bne	.LBB219_7
@ BB#10:                                @   in Loop: Header=BB219_8 Depth=1
	ldr	r2, [r1]
	tst.w	r2, #16
	bne	.LBB219_13
@ BB#11:                                @   in Loop: Header=BB219_8 Depth=1
	ldr	r2, [r1]
	tst.w	r2, #239
	beq	.LBB219_6
@ BB#12:                                @   in Loop: Header=BB219_8 Depth=1
	movs	r2, #6
	b	.LBB219_8
.LBB219_13:                             @   in Loop: Header=BB219_8 Depth=1
	movs	r2, #5
	b	.LBB219_8
.LBB219_14:                             @ %FLASH_WaitForLastOperation.exit
	ldr	r1, [sp, #4]
	cmp	r1, #8
	ittt	eq
	movweq	r1, #15381
	movteq	r1, #16386
	strbeq	r0, [r1]
	add	sp, #8
	bx	lr
.Ltmp219:
	.size	FLASH_OB_RDPConfig, .Ltmp219-FLASH_OB_RDPConfig

	.globl	FLASH_OB_UserConfig
	.align	2
	.type	FLASH_OB_UserConfig,%function
	.code	16                      @ @FLASH_OB_UserConfig
	.thumb_func
FLASH_OB_UserConfig:
@ BB#0:
	push.w	{r11, lr}
	sub	sp, #8
	movw	lr, #15372
	movs	r3, #8
	movt	lr, #16386
	str	r3, [sp, #4]
	ldr.w	r3, [lr]
	tst.w	r3, #65536
	beq	.LBB220_2
@ BB#1:
	mov.w	r12, #1
	b	.LBB220_7
.LBB220_2:
	ldr.w	r3, [lr]
	tst.w	r3, #16
	beq	.LBB220_4
@ BB#3:
	mov.w	r12, #5
	b	.LBB220_7
.LBB220_4:
	ldr.w	r3, [lr]
	tst.w	r3, #239
	beq	.LBB220_6
@ BB#5:
	mov.w	r12, #6
	b	.LBB220_7
.LBB220_6:
	ldr.w	r3, [lr]
	ubfx	r3, r3, #1, #1
	rsb.w	r12, r3, #8
.LBB220_7:                              @ %FLASH_GetStatus.exit.i
	str.w	r12, [sp, #4]
	b	.LBB220_9
.LBB220_8:                              @   in Loop: Header=BB220_9 Depth=1
	movs	r3, #1
	str	r3, [sp, #4]
.LBB220_9:                              @ %FLASH_GetStatus.exit.i
                                        @ =>This Inner Loop Header: Depth=1
	ldr	r3, [sp, #4]
	cmp	r3, #1
	bne	.LBB220_16
@ BB#10:                                @ %.lr.ph.i
                                        @   in Loop: Header=BB220_9 Depth=1
	ldr.w	r3, [lr]
	tst.w	r3, #65536
	bne	.LBB220_8
@ BB#11:                                @   in Loop: Header=BB220_9 Depth=1
	ldr.w	r3, [lr]
	tst.w	r3, #16
	bne	.LBB220_14
@ BB#12:                                @   in Loop: Header=BB220_9 Depth=1
	ldr.w	r3, [lr]
	tst.w	r3, #239
	bne	.LBB220_15
@ BB#13:                                @   in Loop: Header=BB220_9 Depth=1
	ldr.w	r3, [lr]
	ubfx	r3, r3, #1, #1
	rsb.w	r3, r3, #8
	str	r3, [sp, #4]
	b	.LBB220_9
.LBB220_14:                             @   in Loop: Header=BB220_9 Depth=1
	movs	r3, #5
	str	r3, [sp, #4]
	b	.LBB220_9
.LBB220_15:                             @   in Loop: Header=BB220_9 Depth=1
	movs	r3, #6
	str	r3, [sp, #4]
	b	.LBB220_9
.LBB220_16:                             @ %FLASH_WaitForLastOperation.exit
	ldr	r3, [sp, #4]
	cmp	r3, #8
	bne	.LBB220_18
@ BB#17:
	orrs	r0, r1
	movw	r1, #15380
	movt	r1, #16386
	orrs	r0, r2
	ldrb	r2, [r1]
	and	r2, r2, #15
	orrs	r0, r2
	strb	r0, [r1]
.LBB220_18:
	add	sp, #8
	pop.w	{r11, pc}
.Ltmp220:
	.size	FLASH_OB_UserConfig, .Ltmp220-FLASH_OB_UserConfig

	.globl	FLASH_OB_BORConfig
	.align	2
	.type	FLASH_OB_BORConfig,%function
	.code	16                      @ @FLASH_OB_BORConfig
	.thumb_func
FLASH_OB_BORConfig:
@ BB#0:
	movw	r1, #15380
	movt	r1, #16386
	ldrb	r2, [r1]
	and	r2, r2, #243
	strb	r2, [r1]
	ldrb	r2, [r1]
	orrs	r0, r2
	strb	r0, [r1]
	bx	lr
.Ltmp221:
	.size	FLASH_OB_BORConfig, .Ltmp221-FLASH_OB_BORConfig

	.globl	FLASH_OB_Launch
	.align	2
	.type	FLASH_OB_Launch,%function
	.code	16                      @ @FLASH_OB_Launch
	.thumb_func
FLASH_OB_Launch:
@ BB#0:
	sub	sp, #8
	movw	r0, #15380
	movt	r0, #16386
	ldrb	r1, [r0]
	orr	r1, r1, #2
	strb	r1, [r0]
	movs	r0, #8
	str	r0, [sp, #4]
	movw	r0, #15372
	movt	r0, #16386
	ldr	r1, [r0]
	tst.w	r1, #65536
	beq	.LBB222_2
@ BB#1:
	movs	r1, #1
	b	.LBB222_8
.LBB222_2:
	ldr	r1, [r0]
	tst.w	r1, #16
	beq	.LBB222_4
@ BB#3:
	movs	r1, #5
	b	.LBB222_8
.LBB222_4:
	ldr	r1, [r0]
	tst.w	r1, #239
	beq	.LBB222_6
@ BB#5:
	movs	r1, #6
	b	.LBB222_8
.LBB222_6:
	ldr	r1, [r0]
	ubfx	r1, r1, #1, #1
	rsb.w	r1, r1, #8
	b	.LBB222_8
.LBB222_7:                              @   in Loop: Header=BB222_8 Depth=1
	movs	r1, #1
.LBB222_8:                              @ %FLASH_GetStatus.exit.i
                                        @ =>This Inner Loop Header: Depth=1
	str	r1, [sp, #4]
	ldr	r1, [sp, #4]
	cmp	r1, #1
	ittt	ne
	ldrne	r0, [sp, #4]
	addne	sp, #8
	bxne	lr
	ldr	r1, [r0]
	tst.w	r1, #65536
	bne	.LBB222_7
@ BB#9:                                 @   in Loop: Header=BB222_8 Depth=1
	ldr	r1, [r0]
	tst.w	r1, #16
	bne	.LBB222_12
@ BB#10:                                @   in Loop: Header=BB222_8 Depth=1
	ldr	r1, [r0]
	tst.w	r1, #239
	beq	.LBB222_6
@ BB#11:                                @   in Loop: Header=BB222_8 Depth=1
	movs	r1, #6
	b	.LBB222_8
.LBB222_12:                             @   in Loop: Header=BB222_8 Depth=1
	movs	r1, #5
	b	.LBB222_8
.Ltmp222:
	.size	FLASH_OB_Launch, .Ltmp222-FLASH_OB_Launch

	.globl	FLASH_OB_GetUser
	.align	2
	.type	FLASH_OB_GetUser,%function
	.code	16                      @ @FLASH_OB_GetUser
	.thumb_func
FLASH_OB_GetUser:
@ BB#0:
	movw	r0, #15380
	movt	r0, #16386
	ldr	r0, [r0]
	ubfx	r0, r0, #5, #8
	bx	lr
.Ltmp223:
	.size	FLASH_OB_GetUser, .Ltmp223-FLASH_OB_GetUser

	.globl	FLASH_OB_GetWRP
	.align	2
	.type	FLASH_OB_GetWRP,%function
	.code	16                      @ @FLASH_OB_GetWRP
	.thumb_func
FLASH_OB_GetWRP:
@ BB#0:
	movw	r0, #15382
	movt	r0, #16386
	ldrh	r0, [r0]
	bx	lr
.Ltmp224:
	.size	FLASH_OB_GetWRP, .Ltmp224-FLASH_OB_GetWRP

	.globl	FLASH_OB_GetRDP
	.align	2
	.type	FLASH_OB_GetRDP,%function
	.code	16                      @ @FLASH_OB_GetRDP
	.thumb_func
FLASH_OB_GetRDP:
@ BB#0:
	movw	r0, #15381
	movt	r0, #16386
	ldrb	r1, [r0]
	movs	r0, #0
	cmp	r1, #170
	it	ne
	movne	r0, #1
	bx	lr
.Ltmp225:
	.size	FLASH_OB_GetRDP, .Ltmp225-FLASH_OB_GetRDP

	.globl	FLASH_OB_GetBOR
	.align	2
	.type	FLASH_OB_GetBOR,%function
	.code	16                      @ @FLASH_OB_GetBOR
	.thumb_func
FLASH_OB_GetBOR:
@ BB#0:
	movw	r0, #15380
	movt	r0, #16386
	ldrb	r0, [r0]
	and	r0, r0, #12
	bx	lr
.Ltmp226:
	.size	FLASH_OB_GetBOR, .Ltmp226-FLASH_OB_GetBOR

	.globl	FLASH_ITConfig
	.align	2
	.type	FLASH_ITConfig,%function
	.code	16                      @ @FLASH_ITConfig
	.thumb_func
FLASH_ITConfig:
@ BB#0:
	cmp	r1, #0
	movw	r1, #15376
	movt	r1, #16386
	ldr	r2, [r1]
	ite	eq
	biceq.w	r0, r2, r0
	orrne	r0, r2
	str	r0, [r1]
	bx	lr
.Ltmp227:
	.size	FLASH_ITConfig, .Ltmp227-FLASH_ITConfig

	.globl	FLASH_GetFlagStatus
	.align	2
	.type	FLASH_GetFlagStatus,%function
	.code	16                      @ @FLASH_GetFlagStatus
	.thumb_func
FLASH_GetFlagStatus:
@ BB#0:
	movw	r1, #15372
	movt	r1, #16386
	ldr	r1, [r1]
	ands	r0, r1
	it	ne
	movne	r0, #1
	bx	lr
.Ltmp228:
	.size	FLASH_GetFlagStatus, .Ltmp228-FLASH_GetFlagStatus

	.globl	FLASH_ClearFlag
	.align	2
	.type	FLASH_ClearFlag,%function
	.code	16                      @ @FLASH_ClearFlag
	.thumb_func
FLASH_ClearFlag:
@ BB#0:
	movw	r1, #15372
	movt	r1, #16386
	str	r0, [r1]
	bx	lr
.Ltmp229:
	.size	FLASH_ClearFlag, .Ltmp229-FLASH_ClearFlag

	.globl	FLASH_GetStatus
	.align	2
	.type	FLASH_GetStatus,%function
	.code	16                      @ @FLASH_GetStatus
	.thumb_func
FLASH_GetStatus:
@ BB#0:
	movw	r0, #15372
	movt	r0, #16386
	ldr	r1, [r0]
	tst.w	r1, #65536
	itt	ne
	movne	r0, #1
	bxne	lr
	ldr	r1, [r0]
	tst.w	r1, #16
	beq	.LBB230_2
@ BB#1:
	movs	r0, #5
	bx	lr
.LBB230_2:
	ldr	r1, [r0]
	tst.w	r1, #239
	itt	ne
	movne	r0, #6
	bxne	lr
	ldr	r0, [r0]
	ubfx	r0, r0, #1, #1
	rsb.w	r0, r0, #8
	bx	lr
.Ltmp230:
	.size	FLASH_GetStatus, .Ltmp230-FLASH_GetStatus

	.globl	FSMC_NORSRAMDeInit
	.align	2
	.type	FSMC_NORSRAMDeInit,%function
	.code	16                      @ @FSMC_NORSRAMDeInit
	.thumb_func
FSMC_NORSRAMDeInit:
@ BB#0:
	mov.w	r1, #-1610612736
	cmp	r0, #0
	beq	.LBB231_2
@ BB#1:
	movw	r2, #12498
	b	.LBB231_3
.LBB231_2:
	movw	r2, #12507
.LBB231_3:
	str.w	r2, [r1, r0, lsl #2]
	movs	r1, #4
	mvn	r2, #-268435456
	movt	r1, #40960
	str.w	r2, [r1, r0, lsl #2]
	movw	r1, #260
	movt	r1, #40960
	str.w	r2, [r1, r0, lsl #2]
	bx	lr
.Ltmp231:
	.size	FSMC_NORSRAMDeInit, .Ltmp231-FSMC_NORSRAMDeInit

	.globl	FSMC_NORSRAMInit
	.align	2
	.type	FSMC_NORSRAMInit,%function
	.code	16                      @ @FSMC_NORSRAMInit
	.thumb_func
FSMC_NORSRAMInit:
@ BB#0:
	push.w	{r4, r5, r6, r7, r11, lr}
	ldr	r2, [r0, #8]
	ldr	r3, [r0, #12]
	ldr	r1, [r0, #16]
	ldr.w	lr, [r0, #20]
	ldr	r4, [r0, #24]
	ldr	r5, [r0, #28]
	ldm.w	r0, {r7, r12}
	orr.w	r2, r2, r12
	orrs	r2, r3
	orrs	r1, r2
	orr.w	r1, r1, lr
	orrs	r1, r4
	orrs	r1, r5
	add.w	r5, r0, #32
	ldm	r5, {r2, r3, r5}
	ldr	r4, [r0, #44]
	ldr	r6, [r0, #48]
	orrs	r1, r2
	orrs	r1, r3
	orrs	r1, r5
	orrs	r1, r4
	orr.w	r2, r1, r6
	mov.w	r1, #-1610612736
	str.w	r2, [r1, r7, lsl #2]
	ldr	r2, [r0, #8]
	cmp	r2, #8
	itttt	eq
	ldreq	r2, [r0]
	ldreq.w	r3, [r1, r2, lsl #2]
	orreq	r3, r3, #64
	streq.w	r3, [r1, r2, lsl #2]
	ldr	r2, [r0, #52]
	ldr.w	r12, [r0]
	ldm.w	r2, {r3, r7}
	ldr	r6, [r2, #8]
	ldr	r5, [r2, #12]
	ldr	r4, [r2, #16]
	ldr	r1, [r2, #20]
	ldr	r2, [r2, #24]
	orr.w	r3, r3, r7, lsl #4
	orr.w	r3, r3, r6, lsl #8
	orr.w	r3, r3, r5, lsl #16
	orr.w	r3, r3, r4, lsl #20
	orr.w	r1, r3, r1, lsl #24
	orrs	r1, r2
	movs	r2, #4
	movt	r2, #40960
	str.w	r1, [r2, r12, lsl #2]
	ldr	r1, [r0, #44]
	cmp.w	r1, #16384
	bne	.LBB232_2
@ BB#1:
	ldr	r1, [r0]
	ldr	r0, [r0, #56]
	ldr	r2, [r0, #4]
	ldr	r7, [r0]
	ldr	r3, [r0, #8]
	ldr	r6, [r0, #16]
	ldr	r5, [r0, #20]
	ldr	r0, [r0, #24]
	orr.w	r2, r7, r2, lsl #4
	orr.w	r2, r2, r3, lsl #8
	orr.w	r2, r2, r6, lsl #20
	orr.w	r2, r2, r5, lsl #24
	orrs	r0, r2
	movw	r2, #260
	movt	r2, #40960
	str.w	r0, [r2, r1, lsl #2]
	pop.w	{r4, r5, r6, r7, r11, pc}
.LBB232_2:
	ldr	r0, [r0]
	movw	r1, #260
	mvn	r2, #-268435456
	movt	r1, #40960
	str.w	r2, [r1, r0, lsl #2]
	pop.w	{r4, r5, r6, r7, r11, pc}
.Ltmp232:
	.size	FSMC_NORSRAMInit, .Ltmp232-FSMC_NORSRAMInit

	.globl	FSMC_NORSRAMStructInit
	.align	2
	.type	FSMC_NORSRAMStructInit,%function
	.code	16                      @ @FSMC_NORSRAMStructInit
	.thumb_func
FSMC_NORSRAMStructInit:
@ BB#0:
	movs	r1, #0
	movs	r2, #2
	mov.w	r3, #8192
	add.w	r12, r0, #32
	str	r1, [r0]
	str	r2, [r0, #4]
	mov.w	r2, #4096
	str	r1, [r0, #8]
	str	r1, [r0, #12]
	str	r1, [r0, #16]
	str	r1, [r0, #20]
	str	r1, [r0, #24]
	str	r1, [r0, #28]
	stm.w	r12, {r1, r2, r3}
	str	r1, [r0, #44]
	str	r1, [r0, #48]
	movs	r3, #15
	mov.w	r12, #255
	ldr	r2, [r0, #52]
	str	r3, [r2]
	str	r3, [r2, #4]
	str.w	r12, [r2, #8]
	str	r3, [r2, #12]
	str	r3, [r2, #16]
	str	r3, [r2, #20]
	str	r1, [r2, #24]
	ldr	r0, [r0, #56]
	str	r3, [r0]
	str	r3, [r0, #4]
	str.w	r12, [r0, #8]
	str	r3, [r0, #12]
	str	r3, [r0, #16]
	str	r3, [r0, #20]
	str	r1, [r0, #24]
	bx	lr
.Ltmp233:
	.size	FSMC_NORSRAMStructInit, .Ltmp233-FSMC_NORSRAMStructInit

	.globl	FSMC_NORSRAMCmd
	.align	2
	.type	FSMC_NORSRAMCmd,%function
	.code	16                      @ @FSMC_NORSRAMCmd
	.thumb_func
FSMC_NORSRAMCmd:
@ BB#0:
	mov.w	r2, #-1610612736
	cmp	r1, #0
	ldr.w	r3, [r2, r0, lsl #2]
	ittt	ne
	orrne	r1, r3, #1
	strne.w	r1, [r2, r0, lsl #2]
	bxne	lr
	movw	r1, #65534
	movt	r1, #15
	ands	r1, r3
	str.w	r1, [r2, r0, lsl #2]
	bx	lr
.Ltmp234:
	.size	FSMC_NORSRAMCmd, .Ltmp234-FSMC_NORSRAMCmd

	.globl	FSMC_NANDDeInit
	.align	2
	.type	FSMC_NANDDeInit,%function
	.code	16                      @ @FSMC_NANDDeInit
	.thumb_func
FSMC_NANDDeInit:
@ BB#0:
	cmp	r0, #16
	bne	.LBB235_2
@ BB#1:
	movs	r0, #96
	movs	r1, #24
	movt	r0, #40960
	str	r1, [r0]
	movs	r0, #100
	movs	r1, #64
	movt	r0, #40960
	str	r1, [r0]
	movs	r0, #104
	mov.w	r1, #-50529028
	movt	r0, #40960
	str	r1, [r0]
	movs	r0, #108
	b	.LBB235_3
.LBB235_2:
	movs	r0, #128
	movs	r1, #24
	movt	r0, #40960
	str	r1, [r0]
	movs	r0, #132
	movs	r1, #64
	movt	r0, #40960
	str	r1, [r0]
	movs	r0, #136
	mov.w	r1, #-50529028
	movt	r0, #40960
	str	r1, [r0]
	movs	r0, #140
.LBB235_3:
	movt	r0, #40960
	str	r1, [r0]
	bx	lr
.Ltmp235:
	.size	FSMC_NANDDeInit, .Ltmp235-FSMC_NANDDeInit

	.globl	FSMC_NANDInit
	.align	2
	.type	FSMC_NANDInit,%function
	.code	16                      @ @FSMC_NANDInit
	.thumb_func
FSMC_NANDInit:
@ BB#0:
	push.w	{r4, r5, r6, r7, r8, r9, r11, lr}
	ldr	r1, [r0, #32]
	add.w	r6, r0, #12
	ldr.w	lr, [r0]
	ldr.w	r8, [r0, #4]
	ldr.w	r9, [r0, #8]
	ldr.w	r12, [r1]
	ldr	r3, [r1, #4]
	ldr	r2, [r1, #8]
	ldr	r1, [r1, #12]
	cmp.w	lr, #16
	orr.w	r3, r12, r3, lsl #8
	orr.w	r2, r3, r2, lsl #16
	ldm	r6, {r3, r4, r5, r6}
	ldr	r0, [r0, #28]
	orr.w	r12, r2, r1, lsl #24
	ldr	r7, [r0]
	ldr	r2, [r0, #4]
	ldr	r1, [r0, #8]
	ldr	r0, [r0, #12]
	orr.w	r2, r7, r2, lsl #8
	orr.w	r1, r2, r1, lsl #16
	orr.w	r0, r1, r0, lsl #24
	orr.w	r1, r8, r9
	orr.w	r1, r1, r3
	orr.w	r1, r1, r4
	orr.w	r1, r1, r5, lsl #9
	orr.w	r1, r1, r6, lsl #13
	orr	r2, r1, #8
	bne	.LBB236_2
@ BB#1:
	movs	r1, #96
	movt	r1, #40960
	str	r2, [r1]
	movs	r1, #104
	movt	r1, #40960
	str	r0, [r1]
	movs	r0, #108
	b	.LBB236_3
.LBB236_2:
	movs	r1, #128
	movt	r1, #40960
	str	r2, [r1]
	movs	r1, #136
	movt	r1, #40960
	str	r0, [r1]
	movs	r0, #140
.LBB236_3:
	movt	r0, #40960
	str.w	r12, [r0]
	pop.w	{r4, r5, r6, r7, r8, r9, r11, pc}
.Ltmp236:
	.size	FSMC_NANDInit, .Ltmp236-FSMC_NANDInit

	.globl	FSMC_NANDStructInit
	.align	2
	.type	FSMC_NANDStructInit,%function
	.code	16                      @ @FSMC_NANDStructInit
	.thumb_func
FSMC_NANDStructInit:
@ BB#0:
	movs	r1, #16
	movs	r2, #0
	stm.w	r0, {r1, r2}
	str	r2, [r0, #8]
	str	r2, [r0, #12]
	str	r2, [r0, #16]
	str	r2, [r0, #20]
	str	r2, [r0, #24]
	movs	r2, #252
	ldr	r1, [r0, #28]
	str	r2, [r1]
	str	r2, [r1, #4]
	str	r2, [r1, #8]
	str	r2, [r1, #12]
	ldr	r0, [r0, #32]
	str	r2, [r0]
	str	r2, [r0, #4]
	str	r2, [r0, #8]
	str	r2, [r0, #12]
	bx	lr
.Ltmp237:
	.size	FSMC_NANDStructInit, .Ltmp237-FSMC_NANDStructInit

	.globl	FSMC_NANDCmd
	.align	2
	.type	FSMC_NANDCmd,%function
	.code	16                      @ @FSMC_NANDCmd
	.thumb_func
FSMC_NANDCmd:
@ BB#0:
	cbz	r1, .LBB238_2
@ BB#1:
	cmp	r0, #16
	ite	eq
	moveq	r0, #96
	movne	r0, #128
	movt	r0, #40960
	ldr	r1, [r0]
	orr	r1, r1, #4
	str	r1, [r0]
	bx	lr
.LBB238_2:
	cmp	r0, #16
	movw	r2, #65531
	ite	ne
	movne	r0, #128
	moveq	r0, #96
	movt	r2, #15
	movt	r0, #40960
	ldr	r1, [r0]
	ands	r1, r2
	str	r1, [r0]
	bx	lr
.Ltmp238:
	.size	FSMC_NANDCmd, .Ltmp238-FSMC_NANDCmd

	.globl	FSMC_NANDECCCmd
	.align	2
	.type	FSMC_NANDECCCmd,%function
	.code	16                      @ @FSMC_NANDECCCmd
	.thumb_func
FSMC_NANDECCCmd:
@ BB#0:
	cbz	r1, .LBB239_2
@ BB#1:
	cmp	r0, #16
	ite	eq
	moveq	r0, #96
	movne	r0, #128
	movt	r0, #40960
	ldr	r1, [r0]
	orr	r1, r1, #64
	str	r1, [r0]
	bx	lr
.LBB239_2:
	cmp	r0, #16
	movw	r2, #65471
	ite	ne
	movne	r0, #128
	moveq	r0, #96
	movt	r2, #15
	movt	r0, #40960
	ldr	r1, [r0]
	ands	r1, r2
	str	r1, [r0]
	bx	lr
.Ltmp239:
	.size	FSMC_NANDECCCmd, .Ltmp239-FSMC_NANDECCCmd

	.globl	FSMC_GetECC
	.align	2
	.type	FSMC_GetECC,%function
	.code	16                      @ @FSMC_GetECC
	.thumb_func
FSMC_GetECC:
@ BB#0:
	movs	r1, #148
	cmp	r0, #16
	movt	r1, #40960
	itt	eq
	moveq	r1, #116
	movteq	r1, #40960
	ldr	r0, [r1]
	bx	lr
.Ltmp240:
	.size	FSMC_GetECC, .Ltmp240-FSMC_GetECC

	.globl	FSMC_PCCARDDeInit
	.align	2
	.type	FSMC_PCCARDDeInit,%function
	.code	16                      @ @FSMC_PCCARDDeInit
	.thumb_func
FSMC_PCCARDDeInit:
@ BB#0:
	movs	r0, #160
	movs	r1, #24
	movt	r0, #40960
	str	r1, [r0]
	movs	r0, #164
	movs	r1, #0
	movt	r0, #40960
	str	r1, [r0]
	movs	r0, #168
	mov.w	r1, #-50529028
	movt	r0, #40960
	str	r1, [r0]
	movs	r0, #172
	movt	r0, #40960
	str	r1, [r0]
	movs	r0, #176
	movt	r0, #40960
	str	r1, [r0]
	bx	lr
.Ltmp241:
	.size	FSMC_PCCARDDeInit, .Ltmp241-FSMC_PCCARDDeInit

	.globl	FSMC_PCCARDInit
	.align	2
	.type	FSMC_PCCARDInit,%function
	.code	16                      @ @FSMC_PCCARDInit
	.thumb_func
FSMC_PCCARDInit:
@ BB#0:
	ldm.w	r0, {r1, r2, r3}
	orr.w	r1, r1, r2, lsl #9
	movs	r2, #160
	orr.w	r1, r1, r3, lsl #13
	movt	r2, #40960
	orr	r1, r1, #16
	str	r1, [r2]
	ldr	r1, [r0, #12]
	ldr.w	r12, [r1]
	ldr	r3, [r1, #4]
	ldr	r2, [r1, #8]
	ldr	r1, [r1, #12]
	orr.w	r3, r12, r3, lsl #8
	orr.w	r2, r3, r2, lsl #16
	orr.w	r1, r2, r1, lsl #24
	movs	r2, #168
	movt	r2, #40960
	str	r1, [r2]
	ldr	r1, [r0, #16]
	ldr.w	r12, [r1]
	ldr	r3, [r1, #4]
	ldr	r2, [r1, #8]
	ldr	r1, [r1, #12]
	orr.w	r3, r12, r3, lsl #8
	orr.w	r2, r3, r2, lsl #16
	orr.w	r1, r2, r1, lsl #24
	movs	r2, #172
	movt	r2, #40960
	str	r1, [r2]
	ldr	r0, [r0, #20]
	ldm.w	r0, {r1, r2, r3}
	ldr	r0, [r0, #12]
	orr.w	r1, r1, r2, lsl #8
	orr.w	r1, r1, r3, lsl #16
	orr.w	r0, r1, r0, lsl #24
	movs	r1, #176
	movt	r1, #40960
	str	r0, [r1]
	bx	lr
.Ltmp242:
	.size	FSMC_PCCARDInit, .Ltmp242-FSMC_PCCARDInit

	.globl	FSMC_PCCARDStructInit
	.align	2
	.type	FSMC_PCCARDStructInit,%function
	.code	16                      @ @FSMC_PCCARDStructInit
	.thumb_func
FSMC_PCCARDStructInit:
@ BB#0:
	movs	r1, #0
	movs	r2, #252
	str	r1, [r0]
	str	r1, [r0, #4]
	str	r1, [r0, #8]
	ldr	r1, [r0, #12]
	str	r2, [r1]
	str	r2, [r1, #4]
	str	r2, [r1, #8]
	str	r2, [r1, #12]
	ldr	r1, [r0, #16]
	str	r2, [r1]
	str	r2, [r1, #4]
	str	r2, [r1, #8]
	str	r2, [r1, #12]
	ldr	r0, [r0, #20]
	str	r2, [r0]
	str	r2, [r0, #4]
	str	r2, [r0, #8]
	str	r2, [r0, #12]
	bx	lr
.Ltmp243:
	.size	FSMC_PCCARDStructInit, .Ltmp243-FSMC_PCCARDStructInit

	.globl	FSMC_PCCARDCmd
	.align	2
	.type	FSMC_PCCARDCmd,%function
	.code	16                      @ @FSMC_PCCARDCmd
	.thumb_func
FSMC_PCCARDCmd:
@ BB#0:
	movs	r1, #160
	cmp	r0, #0
	movt	r1, #40960
	ldr	r2, [r1]
	ittt	ne
	orrne	r0, r2, #4
	strne	r0, [r1]
	bxne	lr
	movw	r0, #65531
	movt	r0, #15
	ands	r0, r2
	str	r0, [r1]
	bx	lr
.Ltmp244:
	.size	FSMC_PCCARDCmd, .Ltmp244-FSMC_PCCARDCmd

	.globl	FSMC_ITConfig
	.align	2
	.type	FSMC_ITConfig,%function
	.code	16                      @ @FSMC_ITConfig
	.thumb_func
FSMC_ITConfig:
@ BB#0:
	cbz	r2, .LBB245_3
@ BB#1:
	cmp	r0, #16
	bne	.LBB245_5
@ BB#2:
	movs	r0, #100
	b	.LBB245_6
.LBB245_3:
	cmp	r0, #16
	bne	.LBB245_7
@ BB#4:
	movs	r0, #100
	movt	r0, #40960
	ldr	r2, [r0]
	bic.w	r1, r2, r1
	str	r1, [r0]
	bx	lr
.LBB245_5:
	cmp.w	r0, #256
	ite	ne
	movne	r0, #164
	moveq	r0, #132
.LBB245_6:
	movt	r0, #40960
	ldr	r2, [r0]
	orrs	r1, r2
	str	r1, [r0]
	bx	lr
.LBB245_7:
	cmp.w	r0, #256
	mvn.w	r1, r1
	ite	ne
	movne	r0, #164
	moveq	r0, #132
	movt	r0, #40960
	ldr	r2, [r0]
	ands	r1, r2
	str	r1, [r0]
	bx	lr
.Ltmp245:
	.size	FSMC_ITConfig, .Ltmp245-FSMC_ITConfig

	.globl	FSMC_GetFlagStatus
	.align	2
	.type	FSMC_GetFlagStatus,%function
	.code	16                      @ @FSMC_GetFlagStatus
	.thumb_func
FSMC_GetFlagStatus:
@ BB#0:
	cmp	r0, #16
	bne	.LBB246_2
@ BB#1:
	movs	r0, #100
	b	.LBB246_3
.LBB246_2:
	cmp.w	r0, #256
	ite	ne
	movne	r0, #164
	moveq	r0, #132
.LBB246_3:
	movt	r0, #40960
	ldr	r0, [r0]
	ands	r0, r1
	it	ne
	movne	r0, #1
	bx	lr
.Ltmp246:
	.size	FSMC_GetFlagStatus, .Ltmp246-FSMC_GetFlagStatus

	.globl	FSMC_ClearFlag
	.align	2
	.type	FSMC_ClearFlag,%function
	.code	16                      @ @FSMC_ClearFlag
	.thumb_func
FSMC_ClearFlag:
@ BB#0:
	cmp	r0, #16
	bne	.LBB247_2
@ BB#1:
	movs	r0, #100
	movt	r0, #40960
	ldr	r2, [r0]
	bic.w	r1, r2, r1
	str	r1, [r0]
	bx	lr
.LBB247_2:
	cmp.w	r0, #256
	mvn.w	r1, r1
	ite	ne
	movne	r0, #164
	moveq	r0, #132
	movt	r0, #40960
	ldr	r2, [r0]
	ands	r1, r2
	str	r1, [r0]
	bx	lr
.Ltmp247:
	.size	FSMC_ClearFlag, .Ltmp247-FSMC_ClearFlag

	.globl	FSMC_GetITStatus
	.align	2
	.type	FSMC_GetITStatus,%function
	.code	16                      @ @FSMC_GetITStatus
	.thumb_func
FSMC_GetITStatus:
@ BB#0:
	cmp	r0, #16
	bne	.LBB248_2
@ BB#1:
	movs	r0, #100
	b	.LBB248_3
.LBB248_2:
	cmp.w	r0, #256
	ite	ne
	movne	r0, #164
	moveq	r0, #132
.LBB248_3:
	movt	r0, #40960
	ldr	r0, [r0]
	and.w	r2, r0, r1, lsr #3
	cmp	r2, #0
	it	ne
	movne	r2, #1
	ands	r0, r1
	it	ne
	movne	r0, #1
	ands	r0, r2
	bx	lr
.Ltmp248:
	.size	FSMC_GetITStatus, .Ltmp248-FSMC_GetITStatus

	.globl	FSMC_ClearITPendingBit
	.align	2
	.type	FSMC_ClearITPendingBit,%function
	.code	16                      @ @FSMC_ClearITPendingBit
	.thumb_func
FSMC_ClearITPendingBit:
@ BB#0:
	cmp	r0, #16
	bne	.LBB249_2
@ BB#1:
	movs	r0, #100
	movt	r0, #40960
	ldr	r2, [r0]
	bic.w	r1, r2, r1, lsr #3
	str	r1, [r0]
	bx	lr
.LBB249_2:
	cmp.w	r0, #256
	mvn.w	r1, r1, lsr #3
	ite	ne
	movne	r0, #164
	moveq	r0, #132
	movt	r0, #40960
	ldr	r2, [r0]
	ands	r1, r2
	str	r1, [r0]
	bx	lr
.Ltmp249:
	.size	FSMC_ClearITPendingBit, .Ltmp249-FSMC_ClearITPendingBit

	.globl	GPIO_DeInit
	.align	2
	.type	GPIO_DeInit,%function
	.code	16                      @ @GPIO_DeInit
	.thumb_func
GPIO_DeInit:
@ BB#0:
	push	{r7, lr}
	movw	r1, #1023
	mov	r7, sp
	movt	r1, #16386
	cmp	r0, r1
	bgt	.LBB250_3
@ BB#1:
	movs	r1, #0
	movt	r1, #16386
	cmp	r0, r1
	bne.w	.LBB250_24
@ BB#2:
	movs	r0, #1
	movs	r1, #1
	bl	RCC_AHB1PeriphResetCmd
	movs	r0, #1
	b	.LBB250_23
.LBB250_3:
	movw	r1, #2047
	movt	r1, #16386
	cmp	r0, r1
	bgt	.LBB250_6
@ BB#4:
	movw	r1, #1024
	movt	r1, #16386
	cmp	r0, r1
	bne.w	.LBB250_24
@ BB#5:
	movs	r0, #2
	movs	r1, #1
	bl	RCC_AHB1PeriphResetCmd
	movs	r0, #2
	b	.LBB250_23
.LBB250_6:
	movw	r1, #3071
	movt	r1, #16386
	cmp	r0, r1
	bgt	.LBB250_9
@ BB#7:
	movw	r1, #2048
	movt	r1, #16386
	cmp	r0, r1
	bne	.LBB250_24
@ BB#8:
	movs	r0, #4
	movs	r1, #1
	bl	RCC_AHB1PeriphResetCmd
	movs	r0, #4
	b	.LBB250_23
.LBB250_9:
	movw	r1, #4095
	movt	r1, #16386
	cmp	r0, r1
	bgt	.LBB250_12
@ BB#10:
	movw	r1, #3072
	movt	r1, #16386
	cmp	r0, r1
	bne	.LBB250_24
@ BB#11:
	movs	r0, #8
	movs	r1, #1
	bl	RCC_AHB1PeriphResetCmd
	movs	r0, #8
	b	.LBB250_23
.LBB250_12:
	movw	r1, #5119
	movt	r1, #16386
	cmp	r0, r1
	bgt	.LBB250_15
@ BB#13:
	movw	r1, #4096
	movt	r1, #16386
	cmp	r0, r1
	bne	.LBB250_24
@ BB#14:
	movs	r0, #16
	movs	r1, #1
	bl	RCC_AHB1PeriphResetCmd
	movs	r0, #16
	b	.LBB250_23
.LBB250_15:
	movw	r1, #6143
	movt	r1, #16386
	cmp	r0, r1
	bgt	.LBB250_18
@ BB#16:
	movw	r1, #5120
	movt	r1, #16386
	cmp	r0, r1
	bne	.LBB250_24
@ BB#17:
	movs	r0, #32
	movs	r1, #1
	bl	RCC_AHB1PeriphResetCmd
	movs	r0, #32
	b	.LBB250_23
.LBB250_18:
	movw	r1, #6144
	movt	r1, #16386
	cmp	r0, r1
	beq	.LBB250_21
@ BB#19:
	movw	r1, #7168
	movt	r1, #16386
	cmp	r0, r1
	bne	.LBB250_22
@ BB#20:
	movs	r0, #128
	movs	r1, #1
	bl	RCC_AHB1PeriphResetCmd
	movs	r0, #128
	b	.LBB250_23
.LBB250_21:
	movs	r0, #64
	movs	r1, #1
	bl	RCC_AHB1PeriphResetCmd
	movs	r0, #64
	b	.LBB250_23
.LBB250_22:
	movw	r1, #8192
	movt	r1, #16386
	cmp	r0, r1
	it	ne
	popne	{r7, pc}
	mov.w	r0, #256
	movs	r1, #1
	bl	RCC_AHB1PeriphResetCmd
	mov.w	r0, #256
.LBB250_23:
	movs	r1, #0
	bl	RCC_AHB1PeriphResetCmd
.LBB250_24:
	pop	{r7, pc}
.Ltmp250:
	.size	GPIO_DeInit, .Ltmp250-GPIO_DeInit

	.globl	GPIO_Init
	.align	2
	.type	GPIO_Init,%function
	.code	16                      @ @GPIO_Init
	.thumb_func
GPIO_Init:
@ BB#0:
	push.w	{r4, r5, r6, r7, r8, lr}
	ldr.w	r8, [r1]
	movs	r3, #0
	mov.w	r12, #1
	mov.w	lr, #3
	movs	r4, #0
	b	.LBB251_2
.LBB251_1:                              @   in Loop: Header=BB251_2 Depth=1
	adds	r4, #1
	adds	r3, #2
	cmp	r4, #16
	it	eq
	popeq.w	{r4, r5, r6, r7, r8, pc}
.LBB251_2:                              @ =>This Inner Loop Header: Depth=1
	lsl.w	r5, r12, r4
	tst.w	r8, r5
	beq	.LBB251_1
@ BB#3:                                 @   in Loop: Header=BB251_2 Depth=1
	ldr	r7, [r0]
	lsl.w	r6, lr, r3
	bics	r7, r6
	mvns	r6, r6
	str	r7, [r0]
	ldr	r7, [r1, #4]
	ldr	r2, [r0]
	lsls	r7, r3
	orrs	r2, r7
	str	r2, [r0]
	ldr	r2, [r1, #4]
	subs	r2, #1
	cmp	r2, #1
	bhi	.LBB251_5
@ BB#4:                                 @   in Loop: Header=BB251_2 Depth=1
	ldr	r2, [r0, #8]
	ands	r2, r6
	str	r2, [r0, #8]
	ldr	r2, [r1, #8]
	ldr	r7, [r0, #8]
	lsls	r2, r3
	orrs	r2, r7
	str	r2, [r0, #8]
	ldr	r2, [r0, #4]
	bics	r2, r5
	str	r2, [r0, #4]
	ldrh	r2, [r1, #12]
	ldr	r5, [r0, #4]
	lsls	r2, r4
	uxth	r2, r2
	orrs	r2, r5
	str	r2, [r0, #4]
.LBB251_5:                              @   in Loop: Header=BB251_2 Depth=1
	ldr	r2, [r0, #12]
	ands	r2, r6
	str	r2, [r0, #12]
	ldr	r2, [r1, #16]
	ldr	r5, [r0, #12]
	lsls	r2, r3
	orrs	r2, r5
	str	r2, [r0, #12]
	b	.LBB251_1
.Ltmp251:
	.size	GPIO_Init, .Ltmp251-GPIO_Init

	.globl	GPIO_StructInit
	.align	2
	.type	GPIO_StructInit,%function
	.code	16                      @ @GPIO_StructInit
	.thumb_func
GPIO_StructInit:
@ BB#0:
	movw	r1, #65535
	movs	r2, #0
	stm.w	r0, {r1, r2}
	str	r2, [r0, #8]
	str	r2, [r0, #12]
	str	r2, [r0, #16]
	bx	lr
.Ltmp252:
	.size	GPIO_StructInit, .Ltmp252-GPIO_StructInit

	.globl	GPIO_PinLockConfig
	.align	2
	.type	GPIO_PinLockConfig,%function
	.code	16                      @ @GPIO_PinLockConfig
	.thumb_func
GPIO_PinLockConfig:
@ BB#0:
	sub	sp, #8
	mov.w	r2, #65536
	str	r2, [sp, #4]
	ldr	r2, [sp, #4]
	orrs	r2, r1
	str	r2, [sp, #4]
	ldr	r2, [sp, #4]
	str	r2, [r0, #28]
	str	r1, [r0, #28]
	ldr	r1, [sp, #4]
	str	r1, [r0, #28]
	ldr	r1, [r0, #28]
	str	r1, [sp, #4]
	ldr	r0, [r0, #28]
	str	r0, [sp, #4]
	add	sp, #8
	bx	lr
.Ltmp253:
	.size	GPIO_PinLockConfig, .Ltmp253-GPIO_PinLockConfig

	.globl	GPIO_ReadInputDataBit
	.align	2
	.type	GPIO_ReadInputDataBit,%function
	.code	16                      @ @GPIO_ReadInputDataBit
	.thumb_func
GPIO_ReadInputDataBit:
@ BB#0:
	ldr	r0, [r0, #16]
	ands	r0, r1
	it	ne
	movne	r0, #1
	bx	lr
.Ltmp254:
	.size	GPIO_ReadInputDataBit, .Ltmp254-GPIO_ReadInputDataBit

	.globl	GPIO_ReadInputData
	.align	2
	.type	GPIO_ReadInputData,%function
	.code	16                      @ @GPIO_ReadInputData
	.thumb_func
GPIO_ReadInputData:
@ BB#0:
	ldr	r0, [r0, #16]
	uxth	r0, r0
	bx	lr
.Ltmp255:
	.size	GPIO_ReadInputData, .Ltmp255-GPIO_ReadInputData

	.globl	GPIO_ReadOutputDataBit
	.align	2
	.type	GPIO_ReadOutputDataBit,%function
	.code	16                      @ @GPIO_ReadOutputDataBit
	.thumb_func
GPIO_ReadOutputDataBit:
@ BB#0:
	ldr	r0, [r0, #20]
	ands	r0, r1
	it	ne
	movne	r0, #1
	bx	lr
.Ltmp256:
	.size	GPIO_ReadOutputDataBit, .Ltmp256-GPIO_ReadOutputDataBit

	.globl	GPIO_ReadOutputData
	.align	2
	.type	GPIO_ReadOutputData,%function
	.code	16                      @ @GPIO_ReadOutputData
	.thumb_func
GPIO_ReadOutputData:
@ BB#0:
	ldr	r0, [r0, #20]
	uxth	r0, r0
	bx	lr
.Ltmp257:
	.size	GPIO_ReadOutputData, .Ltmp257-GPIO_ReadOutputData

	.globl	GPIO_SetBits
	.align	2
	.type	GPIO_SetBits,%function
	.code	16                      @ @GPIO_SetBits
	.thumb_func
GPIO_SetBits:
@ BB#0:
	strh	r1, [r0, #24]
	bx	lr
.Ltmp258:
	.size	GPIO_SetBits, .Ltmp258-GPIO_SetBits

	.globl	GPIO_ResetBits
	.align	2
	.type	GPIO_ResetBits,%function
	.code	16                      @ @GPIO_ResetBits
	.thumb_func
GPIO_ResetBits:
@ BB#0:
	strh	r1, [r0, #26]
	bx	lr
.Ltmp259:
	.size	GPIO_ResetBits, .Ltmp259-GPIO_ResetBits

	.globl	GPIO_WriteBit
	.align	2
	.type	GPIO_WriteBit,%function
	.code	16                      @ @GPIO_WriteBit
	.thumb_func
GPIO_WriteBit:
@ BB#0:
	cmp	r2, #0
	ite	eq
	strheq	r1, [r0, #26]
	strhne	r1, [r0, #24]
	bx	lr
.Ltmp260:
	.size	GPIO_WriteBit, .Ltmp260-GPIO_WriteBit

	.globl	GPIO_Write
	.align	2
	.type	GPIO_Write,%function
	.code	16                      @ @GPIO_Write
	.thumb_func
GPIO_Write:
@ BB#0:
	str	r1, [r0, #20]
	bx	lr
.Ltmp261:
	.size	GPIO_Write, .Ltmp261-GPIO_Write

	.globl	GPIO_ToggleBits
	.align	2
	.type	GPIO_ToggleBits,%function
	.code	16                      @ @GPIO_ToggleBits
	.thumb_func
GPIO_ToggleBits:
@ BB#0:
	ldr	r2, [r0, #20]
	eors	r1, r2
	str	r1, [r0, #20]
	bx	lr
.Ltmp262:
	.size	GPIO_ToggleBits, .Ltmp262-GPIO_ToggleBits

	.globl	GPIO_PinAFConfig
	.align	2
	.type	GPIO_PinAFConfig,%function
	.code	16                      @ @GPIO_PinAFConfig
	.thumb_func
GPIO_PinAFConfig:
@ BB#0:
	push.w	{r11, lr}
	movs	r3, #28
	and.w	r12, r3, r1, lsl #2
	movs	r3, #15
	lsl.w	lr, r3, r12
	movw	r3, #32764
	and.w	r1, r3, r1, lsr #1
	add	r0, r1
	ldr	r1, [r0, #32]
	bic.w	r1, r1, lr
	str	r1, [r0, #32]
	lsl.w	r1, r2, r12
	ldr	r2, [r0, #32]
	orrs	r1, r2
	str	r1, [r0, #32]
	pop.w	{r11, pc}
.Ltmp263:
	.size	GPIO_PinAFConfig, .Ltmp263-GPIO_PinAFConfig

	.globl	HASH_DeInit
	.align	2
	.type	HASH_DeInit,%function
	.code	16                      @ @HASH_DeInit
	.thumb_func
HASH_DeInit:
@ BB#0:
	push	{r7, lr}
	movs	r0, #32
	movs	r1, #1
	mov	r7, sp
	bl	RCC_AHB2PeriphResetCmd
	movs	r0, #32
	movs	r1, #0
	bl	RCC_AHB2PeriphResetCmd
	pop	{r7, pc}
.Ltmp264:
	.size	HASH_DeInit, .Ltmp264-HASH_DeInit

	.globl	HASH_Init
	.align	2
	.type	HASH_Init,%function
	.code	16                      @ @HASH_Init
	.thumb_func
HASH_Init:
@ BB#0:
	movw	r1, #1024
	movt	r1, #20486
	ldr	r2, [r1]
	bic	r2, r2, #240
	str	r2, [r1]
	ldr.w	r12, [r0]
	ldr	r2, [r0, #8]
	ldr	r3, [r0, #4]
	orr.w	r2, r2, r12
	orrs	r2, r3
	ldr	r3, [r1]
	orrs	r2, r3
	str	r2, [r1]
	ldr	r2, [r0, #4]
	cmp	r2, #64
	bne	.LBB265_2
@ BB#1:
	ldr	r2, [r1]
	bic	r2, r2, #65536
	str	r2, [r1]
	ldr	r0, [r0, #12]
	ldr	r2, [r1]
	orrs	r0, r2
	str	r0, [r1]
.LBB265_2:
	ldr	r0, [r1]
	orr	r0, r0, #4
	str	r0, [r1]
	bx	lr
.Ltmp265:
	.size	HASH_Init, .Ltmp265-HASH_Init

	.globl	HASH_StructInit
	.align	2
	.type	HASH_StructInit,%function
	.code	16                      @ @HASH_StructInit
	.thumb_func
HASH_StructInit:
@ BB#0:
	movs	r1, #0
	str	r1, [r0]
	str	r1, [r0, #4]
	str	r1, [r0, #8]
	str	r1, [r0, #12]
	bx	lr
.Ltmp266:
	.size	HASH_StructInit, .Ltmp266-HASH_StructInit

	.globl	HASH_Reset
	.align	2
	.type	HASH_Reset,%function
	.code	16                      @ @HASH_Reset
	.thumb_func
HASH_Reset:
@ BB#0:
	movw	r0, #1024
	movt	r0, #20486
	ldr	r1, [r0]
	orr	r1, r1, #4
	str	r1, [r0]
	bx	lr
.Ltmp267:
	.size	HASH_Reset, .Ltmp267-HASH_Reset

	.globl	HASH_SetLastWordValidBitsNbr
	.align	2
	.type	HASH_SetLastWordValidBitsNbr,%function
	.code	16                      @ @HASH_SetLastWordValidBitsNbr
	.thumb_func
HASH_SetLastWordValidBitsNbr:
@ BB#0:
	movw	r1, #1032
	movt	r1, #20486
	ldr	r2, [r1]
	bic	r2, r2, #31
	str	r2, [r1]
	ldr	r2, [r1]
	orrs	r0, r2
	str	r0, [r1]
	bx	lr
.Ltmp268:
	.size	HASH_SetLastWordValidBitsNbr, .Ltmp268-HASH_SetLastWordValidBitsNbr

	.globl	HASH_DataIn
	.align	2
	.type	HASH_DataIn,%function
	.code	16                      @ @HASH_DataIn
	.thumb_func
HASH_DataIn:
@ BB#0:
	movw	r1, #1028
	movt	r1, #20486
	str	r0, [r1]
	bx	lr
.Ltmp269:
	.size	HASH_DataIn, .Ltmp269-HASH_DataIn

	.globl	HASH_GetInFIFOWordsNbr
	.align	2
	.type	HASH_GetInFIFOWordsNbr,%function
	.code	16                      @ @HASH_GetInFIFOWordsNbr
	.thumb_func
HASH_GetInFIFOWordsNbr:
@ BB#0:
	movw	r0, #1024
	movt	r0, #20486
	ldr	r0, [r0]
	ubfx	r0, r0, #8, #4
	bx	lr
.Ltmp270:
	.size	HASH_GetInFIFOWordsNbr, .Ltmp270-HASH_GetInFIFOWordsNbr

	.globl	HASH_GetDigest
	.align	2
	.type	HASH_GetDigest,%function
	.code	16                      @ @HASH_GetDigest
	.thumb_func
HASH_GetDigest:
@ BB#0:
	movw	r1, #1036
	movt	r1, #20486
	ldr	r1, [r1]
	str	r1, [r0]
	movw	r1, #1040
	movt	r1, #20486
	ldr	r1, [r1]
	str	r1, [r0, #4]
	movw	r1, #1044
	movt	r1, #20486
	ldr	r1, [r1]
	str	r1, [r0, #8]
	movw	r1, #1048
	movt	r1, #20486
	ldr	r1, [r1]
	str	r1, [r0, #12]
	movw	r1, #1052
	movt	r1, #20486
	ldr	r1, [r1]
	str	r1, [r0, #16]
	bx	lr
.Ltmp271:
	.size	HASH_GetDigest, .Ltmp271-HASH_GetDigest

	.globl	HASH_StartDigest
	.align	2
	.type	HASH_StartDigest,%function
	.code	16                      @ @HASH_StartDigest
	.thumb_func
HASH_StartDigest:
@ BB#0:
	movw	r0, #1032
	movt	r0, #20486
	ldr	r1, [r0]
	orr	r1, r1, #256
	str	r1, [r0]
	bx	lr
.Ltmp272:
	.size	HASH_StartDigest, .Ltmp272-HASH_StartDigest

	.globl	HASH_SaveContext
	.align	2
	.type	HASH_SaveContext,%function
	.code	16                      @ @HASH_SaveContext
	.thumb_func
HASH_SaveContext:
@ BB#0:
	movw	r1, #1056
	movw	r2, #1272
	movt	r1, #20486
	movt	r2, #20486
	ldr	r1, [r1]
	str	r1, [r0]
	movw	r1, #1032
	movt	r1, #20486
	ldr	r1, [r1]
	str	r1, [r0, #4]
	movw	r1, #1024
	movt	r1, #20486
	ldr	r1, [r1]
	str	r1, [r0, #8]
	adds	r0, #12
	movs	r1, #0
.LBB273_1:                              @ =>This Inner Loop Header: Depth=1
	ldr.w	r3, [r2, r1, lsl #2]
	str.w	r3, [r0, r1, lsl #2]
	adds	r1, #1
	cmp	r1, #51
	bne	.LBB273_1
@ BB#2:
	bx	lr
.Ltmp273:
	.size	HASH_SaveContext, .Ltmp273-HASH_SaveContext

	.globl	HASH_RestoreContext
	.align	2
	.type	HASH_RestoreContext,%function
	.code	16                      @ @HASH_RestoreContext
	.thumb_func
HASH_RestoreContext:
@ BB#0:
	ldr	r1, [r0]
	movw	r2, #1056
	movt	r2, #20486
	str	r1, [r2]
	movw	r2, #1032
	ldr	r1, [r0, #4]
	movt	r2, #20486
	str	r1, [r2]
	movw	r2, #1024
	ldr	r1, [r0, #8]
	movt	r2, #20486
	adds	r0, #12
	str	r1, [r2]
	ldr	r1, [r2]
	orr	r1, r1, #4
	str	r1, [r2]
	movw	r2, #1272
	movs	r1, #0
	movt	r2, #20486
.LBB274_1:                              @ =>This Inner Loop Header: Depth=1
	ldr.w	r3, [r0, r1, lsl #2]
	str.w	r3, [r2, r1, lsl #2]
	adds	r1, #1
	cmp	r1, #51
	bne	.LBB274_1
@ BB#2:
	bx	lr
.Ltmp274:
	.size	HASH_RestoreContext, .Ltmp274-HASH_RestoreContext

	.globl	HASH_DMACmd
	.align	2
	.type	HASH_DMACmd,%function
	.code	16                      @ @HASH_DMACmd
	.thumb_func
HASH_DMACmd:
@ BB#0:
	movw	r1, #1024
	cmp	r0, #0
	movt	r1, #20486
	ldr	r2, [r1]
	ite	eq
	biceq	r0, r2, #8
	orrne	r0, r2, #8
	str	r0, [r1]
	bx	lr
.Ltmp275:
	.size	HASH_DMACmd, .Ltmp275-HASH_DMACmd

	.globl	HASH_ITConfig
	.align	2
	.type	HASH_ITConfig,%function
	.code	16                      @ @HASH_ITConfig
	.thumb_func
HASH_ITConfig:
@ BB#0:
	cbz	r1, .LBB276_2
@ BB#1:
	movw	r1, #1056
	movt	r1, #20486
	ldr	r2, [r1]
	orrs	r0, r2
	str	r0, [r1]
	bx	lr
.LBB276_2:
	movw	r1, #1056
	eor	r0, r0, #255
	movt	r1, #20486
	ldr	r2, [r1]
	ands	r0, r2
	str	r0, [r1]
	bx	lr
.Ltmp276:
	.size	HASH_ITConfig, .Ltmp276-HASH_ITConfig

	.globl	HASH_GetFlagStatus
	.align	2
	.type	HASH_GetFlagStatus,%function
	.code	16                      @ @HASH_GetFlagStatus
	.thumb_func
HASH_GetFlagStatus:
@ BB#0:
	movw	r1, #1024
	tst.w	r0, #4096
	movt	r1, #20486
	itt	eq
	movweq	r1, #1060
	movteq	r1, #20486
	ldr	r1, [r1]
	ands	r0, r1
	it	ne
	movne	r0, #1
	bx	lr
.Ltmp277:
	.size	HASH_GetFlagStatus, .Ltmp277-HASH_GetFlagStatus

	.globl	HASH_ClearFlag
	.align	2
	.type	HASH_ClearFlag,%function
	.code	16                      @ @HASH_ClearFlag
	.thumb_func
HASH_ClearFlag:
@ BB#0:
	movw	r1, #1060
	mvns	r0, r0
	movt	r1, #20486
	str	r0, [r1]
	bx	lr
.Ltmp278:
	.size	HASH_ClearFlag, .Ltmp278-HASH_ClearFlag

	.globl	HASH_GetITStatus
	.align	2
	.type	HASH_GetITStatus,%function
	.code	16                      @ @HASH_GetITStatus
	.thumb_func
HASH_GetITStatus:
@ BB#0:
	movw	r1, #1060
	movt	r1, #20486
	ldr	r1, [r1]
	ands	r0, r1
	movw	r1, #1056
	movt	r1, #20486
	ldr	r1, [r1]
	ands	r0, r1
	it	ne
	movne	r0, #1
	bx	lr
.Ltmp279:
	.size	HASH_GetITStatus, .Ltmp279-HASH_GetITStatus

	.globl	HASH_ClearITPendingBit
	.align	2
	.type	HASH_ClearITPendingBit,%function
	.code	16                      @ @HASH_ClearITPendingBit
	.thumb_func
HASH_ClearITPendingBit:
@ BB#0:
	movw	r1, #1060
	eor	r0, r0, #255
	movt	r1, #20486
	str	r0, [r1]
	bx	lr
.Ltmp280:
	.size	HASH_ClearITPendingBit, .Ltmp280-HASH_ClearITPendingBit

	.globl	HASH_MD5
	.align	2
	.type	HASH_MD5,%function
	.code	16                      @ @HASH_MD5
	.thumb_func
HASH_MD5:
@ BB#0:
	push.w	{r4, r5, r6, r7, r8, lr}
	add	r7, sp, #12
	sub	sp, #48
	mov	r6, r0
	mov	r5, r1
	movs	r0, #24
	movs	r4, #0
	mov	r8, r2
	and.w	r0, r0, r5, lsl #3
	strh.w	r4, [sp, #8]
	str	r4, [sp, #4]
	strh.w	r0, [sp, #8]
	bl	HASH_DeInit
	movs	r0, #128
	str	r0, [sp, #32]
	movs	r0, #32
	str	r4, [sp, #36]
	str	r0, [sp, #40]
	add	r0, sp, #32
	bl	HASH_Init
	ldrh.w	r0, [sp, #8]
	bl	HASH_SetLastWordValidBitsNbr
	cbz	r5, .LBB281_3
@ BB#1:                                 @ %.lr.ph
	movs	r4, #0
.LBB281_2:                              @ =>This Inner Loop Header: Depth=1
	ldr	r0, [r6, r4]
	bl	HASH_DataIn
	adds	r4, #4
	cmp	r4, r5
	blo	.LBB281_2
.LBB281_3:                              @ %._crit_edge
	bl	HASH_StartDigest
.LBB281_4:                              @ =>This Inner Loop Header: Depth=1
	movs	r0, #8
	bl	HASH_GetFlagStatus
	ldr	r1, [sp, #4]
	adds	r1, #1
	str	r1, [sp, #4]
	ldr	r1, [sp, #4]
	cmp.w	r1, #65536
	it	ne
	cmpne	r0, #0
	bne	.LBB281_4
@ BB#5:                                 @ %.critedge
	cmp	r0, #0
	ittt	ne
	movne	r0, #0
	addne	sp, #48
	popne.w	{r4, r5, r6, r7, r8, pc}
	add	r0, sp, #12
	bl	HASH_GetDigest
	ldr	r0, [sp, #12]
	@APP
	rev r0, r0
	@NO_APP
	str.w	r0, [r8]
	ldr	r0, [sp, #16]
	@APP
	rev r0, r0
	@NO_APP
	str.w	r0, [r8, #4]
	ldr	r0, [sp, #20]
	@APP
	rev r0, r0
	@NO_APP
	str.w	r0, [r8, #8]
	ldr	r0, [sp, #24]
	@APP
	rev r0, r0
	@NO_APP
	str.w	r0, [r8, #12]
	movs	r0, #1
	add	sp, #48
	pop.w	{r4, r5, r6, r7, r8, pc}
.Ltmp281:
	.size	HASH_MD5, .Ltmp281-HASH_MD5

	.globl	HMAC_MD5
	.align	2
	.type	HMAC_MD5,%function
	.code	16                      @ @HMAC_MD5
	.thumb_func
HMAC_MD5:
@ BB#0:
	push.w	{r4, r5, r6, r7, r8, r9, r10, r11, lr}
	add	r7, sp, #12
	sub	sp, #52
	mov	r5, r0
	mov	r10, r3
	mov	r4, r1
	movs	r0, #24
	movs	r6, #0
	mov	r8, r2
	and.w	r1, r0, r10, lsl #3
	and.w	r0, r0, r4, lsl #3
	strh.w	r6, [sp, #12]
	strh.w	r6, [sp, #8]
	str	r6, [sp, #4]
	strh.w	r1, [sp, #12]
	strh.w	r0, [sp, #8]
	bl	HASH_DeInit
	movs	r0, #128
	cmp	r4, #64
	str	r0, [sp, #36]
	mov.w	r0, #64
	str	r0, [sp, #40]
	mov.w	r0, #32
	str	r0, [sp, #44]
	mov.w	r0, #0
	it	hi
	movhi.w	r0, #65536
	str	r0, [sp, #48]
	add	r0, sp, #36
	bl	HASH_Init
	ldrh.w	r0, [sp, #8]
	bl	HASH_SetLastWordValidBitsNbr
	cbz	r4, .LBB282_2
.LBB282_1:                              @ %.lr.ph20
                                        @ =>This Inner Loop Header: Depth=1
	ldr	r0, [r5, r6]
	bl	HASH_DataIn
	adds	r6, #4
	cmp	r6, r4
	blo	.LBB282_1
.LBB282_2:                              @ %._crit_edge21
	ldr.w	r9, [r7, #24]
	bl	HASH_StartDigest
.LBB282_3:                              @ =>This Inner Loop Header: Depth=1
	movs	r0, #8
	bl	HASH_GetFlagStatus
	ldr	r1, [sp, #4]
	adds	r1, #1
	str	r1, [sp, #4]
	ldr	r1, [sp, #4]
	cmp.w	r1, #65536
	it	ne
	cmpne	r0, #0
	bne	.LBB282_3
@ BB#4:                                 @ %.critedge
	cmp	r0, #0
	bne	.LBB282_17
@ BB#5:
	ldrh.w	r0, [sp, #12]
	bl	HASH_SetLastWordValidBitsNbr
	mov.w	r11, #0
	cmp.w	r10, #0
	beq	.LBB282_8
@ BB#6:
	movs	r6, #0
.LBB282_7:                              @ %.lr.ph15
                                        @ =>This Inner Loop Header: Depth=1
	ldr.w	r0, [r8, r6]
	bl	HASH_DataIn
	adds	r6, #4
	cmp	r6, r10
	blo	.LBB282_7
.LBB282_8:                              @ %._crit_edge16
	bl	HASH_StartDigest
	str.w	r11, [sp, #4]
.LBB282_9:                              @ =>This Inner Loop Header: Depth=1
	movs	r0, #8
	bl	HASH_GetFlagStatus
	ldr	r1, [sp, #4]
	adds	r1, #1
	str	r1, [sp, #4]
	ldr	r1, [sp, #4]
	cmp.w	r1, #65536
	it	ne
	cmpne	r0, #0
	bne	.LBB282_9
@ BB#10:                                @ %.critedge1
	cbnz	r0, .LBB282_17
@ BB#11:
	ldrh.w	r0, [sp, #8]
	bl	HASH_SetLastWordValidBitsNbr
	mov.w	r8, #0
	cbz	r4, .LBB282_14
@ BB#12:
	movs	r6, #0
.LBB282_13:                             @ %.lr.ph
                                        @ =>This Inner Loop Header: Depth=1
	ldr	r0, [r5, r6]
	bl	HASH_DataIn
	adds	r6, #4
	cmp	r6, r4
	blo	.LBB282_13
.LBB282_14:                             @ %._crit_edge
	bl	HASH_StartDigest
	str.w	r8, [sp, #4]
.LBB282_15:                             @ =>This Inner Loop Header: Depth=1
	movs	r0, #8
	bl	HASH_GetFlagStatus
	ldr	r1, [sp, #4]
	adds	r1, #1
	str	r1, [sp, #4]
	ldr	r1, [sp, #4]
	cmp.w	r1, #65536
	it	ne
	cmpne	r0, #0
	bne	.LBB282_15
@ BB#16:                                @ %.critedge2
	cmp	r0, #0
	beq	.LBB282_18
.LBB282_17:
	movs	r0, #0
	add	sp, #52
	pop.w	{r4, r5, r6, r7, r8, r9, r10, r11, pc}
.LBB282_18:
	add	r0, sp, #16
	bl	HASH_GetDigest
	ldr	r0, [sp, #16]
	@APP
	rev r0, r0
	@NO_APP
	str.w	r0, [r9]
	ldr	r0, [sp, #20]
	@APP
	rev r0, r0
	@NO_APP
	str.w	r0, [r9, #4]
	ldr	r0, [sp, #24]
	@APP
	rev r0, r0
	@NO_APP
	str.w	r0, [r9, #8]
	ldr	r0, [sp, #28]
	@APP
	rev r0, r0
	@NO_APP
	str.w	r0, [r9, #12]
	movs	r0, #1
	add	sp, #52
	pop.w	{r4, r5, r6, r7, r8, r9, r10, r11, pc}
.Ltmp282:
	.size	HMAC_MD5, .Ltmp282-HMAC_MD5

	.globl	HASH_SHA1
	.align	2
	.type	HASH_SHA1,%function
	.code	16                      @ @HASH_SHA1
	.thumb_func
HASH_SHA1:
@ BB#0:
	push.w	{r4, r5, r6, r7, r8, lr}
	add	r7, sp, #12
	sub	sp, #48
	mov	r6, r0
	mov	r5, r1
	movs	r0, #24
	movs	r4, #0
	mov	r8, r2
	and.w	r0, r0, r5, lsl #3
	strh.w	r4, [sp, #8]
	str	r4, [sp, #4]
	strh.w	r0, [sp, #8]
	bl	HASH_DeInit
	movs	r0, #32
	str	r4, [sp, #32]
	str	r4, [sp, #36]
	str	r0, [sp, #40]
	add	r0, sp, #32
	bl	HASH_Init
	ldrh.w	r0, [sp, #8]
	bl	HASH_SetLastWordValidBitsNbr
	cbz	r5, .LBB283_3
@ BB#1:                                 @ %.lr.ph
	movs	r4, #0
.LBB283_2:                              @ =>This Inner Loop Header: Depth=1
	ldr	r0, [r6, r4]
	bl	HASH_DataIn
	adds	r4, #4
	cmp	r4, r5
	blo	.LBB283_2
.LBB283_3:                              @ %._crit_edge
	bl	HASH_StartDigest
.LBB283_4:                              @ =>This Inner Loop Header: Depth=1
	movs	r0, #8
	bl	HASH_GetFlagStatus
	ldr	r1, [sp, #4]
	adds	r1, #1
	str	r1, [sp, #4]
	ldr	r1, [sp, #4]
	cmp.w	r1, #65536
	it	ne
	cmpne	r0, #0
	bne	.LBB283_4
@ BB#5:                                 @ %.critedge
	cmp	r0, #0
	ittt	ne
	movne	r0, #0
	addne	sp, #48
	popne.w	{r4, r5, r6, r7, r8, pc}
	add	r0, sp, #12
	bl	HASH_GetDigest
	ldr	r0, [sp, #12]
	@APP
	rev r0, r0
	@NO_APP
	str.w	r0, [r8]
	ldr	r0, [sp, #16]
	@APP
	rev r0, r0
	@NO_APP
	str.w	r0, [r8, #4]
	ldr	r0, [sp, #20]
	@APP
	rev r0, r0
	@NO_APP
	str.w	r0, [r8, #8]
	ldr	r0, [sp, #24]
	@APP
	rev r0, r0
	@NO_APP
	str.w	r0, [r8, #12]
	ldr	r0, [sp, #28]
	@APP
	rev r0, r0
	@NO_APP
	str.w	r0, [r8, #16]
	movs	r0, #1
	add	sp, #48
	pop.w	{r4, r5, r6, r7, r8, pc}
.Ltmp283:
	.size	HASH_SHA1, .Ltmp283-HASH_SHA1

	.globl	HMAC_SHA1
	.align	2
	.type	HMAC_SHA1,%function
	.code	16                      @ @HMAC_SHA1
	.thumb_func
HMAC_SHA1:
@ BB#0:
	push.w	{r4, r5, r6, r7, r8, r9, r10, r11, lr}
	add	r7, sp, #12
	sub	sp, #52
	mov	r5, r0
	mov	r10, r3
	mov	r4, r1
	movs	r0, #24
	movs	r6, #0
	mov	r8, r2
	and.w	r1, r0, r10, lsl #3
	and.w	r0, r0, r4, lsl #3
	strh.w	r6, [sp, #12]
	strh.w	r6, [sp, #8]
	str	r6, [sp, #4]
	strh.w	r1, [sp, #12]
	strh.w	r0, [sp, #8]
	bl	HASH_DeInit
	movs	r0, #64
	str	r6, [sp, #36]
	cmp	r4, #64
	str	r0, [sp, #40]
	mov.w	r0, #32
	str	r0, [sp, #44]
	mov.w	r0, #0
	it	hi
	movhi.w	r0, #65536
	str	r0, [sp, #48]
	add	r0, sp, #36
	bl	HASH_Init
	ldrh.w	r0, [sp, #8]
	bl	HASH_SetLastWordValidBitsNbr
	cbz	r4, .LBB284_2
.LBB284_1:                              @ %.lr.ph20
                                        @ =>This Inner Loop Header: Depth=1
	ldr	r0, [r5, r6]
	bl	HASH_DataIn
	adds	r6, #4
	cmp	r6, r4
	blo	.LBB284_1
.LBB284_2:                              @ %._crit_edge21
	ldr.w	r9, [r7, #24]
	bl	HASH_StartDigest
.LBB284_3:                              @ =>This Inner Loop Header: Depth=1
	movs	r0, #8
	bl	HASH_GetFlagStatus
	ldr	r1, [sp, #4]
	adds	r1, #1
	str	r1, [sp, #4]
	ldr	r1, [sp, #4]
	cmp.w	r1, #65536
	it	ne
	cmpne	r0, #0
	bne	.LBB284_3
@ BB#4:                                 @ %.critedge
	cmp	r0, #0
	bne	.LBB284_17
@ BB#5:
	ldrh.w	r0, [sp, #12]
	bl	HASH_SetLastWordValidBitsNbr
	mov.w	r11, #0
	cmp.w	r10, #0
	beq	.LBB284_8
@ BB#6:
	movs	r6, #0
.LBB284_7:                              @ %.lr.ph15
                                        @ =>This Inner Loop Header: Depth=1
	ldr.w	r0, [r8, r6]
	bl	HASH_DataIn
	adds	r6, #4
	cmp	r6, r10
	blo	.LBB284_7
.LBB284_8:                              @ %._crit_edge16
	bl	HASH_StartDigest
	str.w	r11, [sp, #4]
.LBB284_9:                              @ =>This Inner Loop Header: Depth=1
	movs	r0, #8
	bl	HASH_GetFlagStatus
	ldr	r1, [sp, #4]
	adds	r1, #1
	str	r1, [sp, #4]
	ldr	r1, [sp, #4]
	cmp.w	r1, #65536
	it	ne
	cmpne	r0, #0
	bne	.LBB284_9
@ BB#10:                                @ %.critedge1
	cbnz	r0, .LBB284_17
@ BB#11:
	ldrh.w	r0, [sp, #8]
	bl	HASH_SetLastWordValidBitsNbr
	mov.w	r8, #0
	cbz	r4, .LBB284_14
@ BB#12:
	movs	r6, #0
.LBB284_13:                             @ %.lr.ph
                                        @ =>This Inner Loop Header: Depth=1
	ldr	r0, [r5, r6]
	bl	HASH_DataIn
	adds	r6, #4
	cmp	r6, r4
	blo	.LBB284_13
.LBB284_14:                             @ %._crit_edge
	bl	HASH_StartDigest
	str.w	r8, [sp, #4]
.LBB284_15:                             @ =>This Inner Loop Header: Depth=1
	movs	r0, #8
	bl	HASH_GetFlagStatus
	ldr	r1, [sp, #4]
	adds	r1, #1
	str	r1, [sp, #4]
	ldr	r1, [sp, #4]
	cmp.w	r1, #65536
	it	ne
	cmpne	r0, #0
	bne	.LBB284_15
@ BB#16:                                @ %.critedge2
	cmp	r0, #0
	beq	.LBB284_18
.LBB284_17:
	movs	r0, #0
	add	sp, #52
	pop.w	{r4, r5, r6, r7, r8, r9, r10, r11, pc}
.LBB284_18:
	add	r0, sp, #16
	bl	HASH_GetDigest
	ldr	r0, [sp, #16]
	@APP
	rev r0, r0
	@NO_APP
	str.w	r0, [r9]
	ldr	r0, [sp, #20]
	@APP
	rev r0, r0
	@NO_APP
	str.w	r0, [r9, #4]
	ldr	r0, [sp, #24]
	@APP
	rev r0, r0
	@NO_APP
	str.w	r0, [r9, #8]
	ldr	r0, [sp, #28]
	@APP
	rev r0, r0
	@NO_APP
	str.w	r0, [r9, #12]
	ldr	r0, [sp, #32]
	@APP
	rev r0, r0
	@NO_APP
	str.w	r0, [r9, #16]
	movs	r0, #1
	add	sp, #52
	pop.w	{r4, r5, r6, r7, r8, r9, r10, r11, pc}
.Ltmp284:
	.size	HMAC_SHA1, .Ltmp284-HMAC_SHA1

	.globl	I2C_DeInit
	.align	2
	.type	I2C_DeInit,%function
	.code	16                      @ @I2C_DeInit
	.thumb_func
I2C_DeInit:
@ BB#0:
	push	{r7, lr}
	movw	r1, #23552
	mov	r7, sp
	movt	r1, #16384
	cmp	r0, r1
	beq	.LBB285_3
@ BB#1:
	movw	r1, #22528
	movt	r1, #16384
	cmp	r0, r1
	bne	.LBB285_4
@ BB#2:
	mov.w	r0, #4194304
	movs	r1, #1
	bl	RCC_APB1PeriphResetCmd
	mov.w	r0, #4194304
	b	.LBB285_5
.LBB285_3:
	mov.w	r0, #8388608
	movs	r1, #1
	bl	RCC_APB1PeriphResetCmd
	mov.w	r0, #8388608
	b	.LBB285_5
.LBB285_4:
	movw	r1, #21504
	movt	r1, #16384
	cmp	r0, r1
	it	ne
	popne	{r7, pc}
	mov.w	r0, #2097152
	movs	r1, #1
	bl	RCC_APB1PeriphResetCmd
	mov.w	r0, #2097152
.LBB285_5:
	movs	r1, #0
	bl	RCC_APB1PeriphResetCmd
	pop	{r7, pc}
.Ltmp285:
	.size	I2C_DeInit, .Ltmp285-I2C_DeInit

	.globl	I2C_Init
	.align	2
	.type	I2C_Init,%function
	.code	16                      @ @I2C_Init
	.thumb_func
I2C_Init:
@ BB#0:
	push.w	{r4, r5, r6, r7, r11, lr}
	add	r7, sp, #12
	sub	sp, #16
	mov	r4, r0
	mov	r0, sp
	mov	r5, r1
	ldrh	r6, [r4, #4]
	bl	RCC_GetClocksFreq
	ldr	r1, [sp, #8]
	movw	r0, #56963
	movw	r3, #34464
	movt	r0, #17179
	movt	r3, #1
	umull	r0, r2, r1, r0
	bic	r0, r6, #63
	orr.w	r0, r0, r2, lsr #18
	strh	r0, [r4, #4]
	ldrh	r0, [r4]
	bic	r0, r0, #1
	strh	r0, [r4]
	lsrs	r0, r2, #18
	ldr	r2, [r5]
	cmp	r2, r3
	bhi	.LBB286_2
@ BB#1:
	adds	r0, #1
	strh	r0, [r4, #32]
	lsls	r0, r2, #1
	udiv	r0, r1, r0
	movw	r1, #65532
	ands	r1, r0
	uxth	r0, r0
	cmp	r1, #4
	it	lo
	movlo	r0, #4
	b	.LBB286_6
.LBB286_2:
	ldrh	r3, [r5, #6]
	movw	r6, #49151
	cmp	r3, r6
	bne	.LBB286_4
@ BB#3:
	add.w	r2, r2, r2, lsl #1
	udiv	r1, r1, r2
	b	.LBB286_5
.LBB286_4:
	movs	r3, #25
	muls	r2, r3, r2
	udiv	r1, r1, r2
	orr	r1, r1, #16384
.LBB286_5:
	movw	r2, #4095
	tst	r1, r2
	ittt	eq
	movweq	r2, #65534
	andeq	r1, r2
	orreq	r1, r1, #1
	mov.w	r2, #300
	muls	r0, r2, r0
	movw	r2, #19923
	movt	r2, #4194
	umull	r0, r2, r0, r2
	movs	r0, #1
	add.w	r0, r0, r2, lsr #6
	strh	r0, [r4, #32]
	orr	r0, r1, #32768
.LBB286_6:
	strh	r0, [r4, #28]
	movw	r1, #64501
	ldrh	r0, [r4]
	orr	r0, r0, #1
	strh	r0, [r4]
	ldrh	r0, [r4]
	ldrh	r2, [r5, #10]
	ands	r0, r1
	ldrh	r1, [r5, #4]
	orrs	r1, r2
	orrs	r0, r1
	strh	r0, [r4]
	ldrh	r0, [r5, #12]
	ldrh	r1, [r5, #8]
	orrs	r0, r1
	strh	r0, [r4, #8]
	add	sp, #16
	pop.w	{r4, r5, r6, r7, r11, pc}
.Ltmp286:
	.size	I2C_Init, .Ltmp286-I2C_Init

	.globl	I2C_StructInit
	.align	2
	.type	I2C_StructInit,%function
	.code	16                      @ @I2C_StructInit
	.thumb_func
I2C_StructInit:
@ BB#0:
	movw	r1, #5000
	str	r1, [r0]
	movw	r1, #49151
	strh	r1, [r0, #6]
	movs	r1, #0
	strh	r1, [r0, #4]
	strh	r1, [r0, #10]
	strh	r1, [r0, #8]
	mov.w	r1, #16384
	strh	r1, [r0, #12]
	bx	lr
.Ltmp287:
	.size	I2C_StructInit, .Ltmp287-I2C_StructInit

	.globl	I2C_Cmd
	.align	2
	.type	I2C_Cmd,%function
	.code	16                      @ @I2C_Cmd
	.thumb_func
I2C_Cmd:
@ BB#0:
	ldrh	r2, [r0]
	cmp	r1, #0
	ite	eq
	biceq	r1, r2, #1
	orrne	r1, r2, #1
	strh	r1, [r0]
	bx	lr
.Ltmp288:
	.size	I2C_Cmd, .Ltmp288-I2C_Cmd

	.globl	I2C_GenerateSTART
	.align	2
	.type	I2C_GenerateSTART,%function
	.code	16                      @ @I2C_GenerateSTART
	.thumb_func
I2C_GenerateSTART:
@ BB#0:
	ldrh	r2, [r0]
	cmp	r1, #0
	ite	eq
	biceq	r1, r2, #256
	orrne	r1, r2, #256
	strh	r1, [r0]
	bx	lr
.Ltmp289:
	.size	I2C_GenerateSTART, .Ltmp289-I2C_GenerateSTART

	.globl	I2C_GenerateSTOP
	.align	2
	.type	I2C_GenerateSTOP,%function
	.code	16                      @ @I2C_GenerateSTOP
	.thumb_func
I2C_GenerateSTOP:
@ BB#0:
	ldrh	r2, [r0]
	cmp	r1, #0
	ite	eq
	biceq	r1, r2, #512
	orrne	r1, r2, #512
	strh	r1, [r0]
	bx	lr
.Ltmp290:
	.size	I2C_GenerateSTOP, .Ltmp290-I2C_GenerateSTOP

	.globl	I2C_Send7bitAddress
	.align	2
	.type	I2C_Send7bitAddress,%function
	.code	16                      @ @I2C_Send7bitAddress
	.thumb_func
I2C_Send7bitAddress:
@ BB#0:
	orr	r3, r1, #1
	cmp	r2, #0
	it	eq
	andeq	r3, r1, #254
	strh	r3, [r0, #16]
	bx	lr
.Ltmp291:
	.size	I2C_Send7bitAddress, .Ltmp291-I2C_Send7bitAddress

	.globl	I2C_AcknowledgeConfig
	.align	2
	.type	I2C_AcknowledgeConfig,%function
	.code	16                      @ @I2C_AcknowledgeConfig
	.thumb_func
I2C_AcknowledgeConfig:
@ BB#0:
	ldrh	r2, [r0]
	cmp	r1, #0
	ite	eq
	biceq	r1, r2, #1024
	orrne	r1, r2, #1024
	strh	r1, [r0]
	bx	lr
.Ltmp292:
	.size	I2C_AcknowledgeConfig, .Ltmp292-I2C_AcknowledgeConfig

	.globl	I2C_OwnAddress2Config
	.align	2
	.type	I2C_OwnAddress2Config,%function
	.code	16                      @ @I2C_OwnAddress2Config
	.thumb_func
I2C_OwnAddress2Config:
@ BB#0:
	ldrh	r2, [r0, #12]
	and	r1, r1, #254
	bic	r2, r2, #254
	orrs	r1, r2
	strh	r1, [r0, #12]
	bx	lr
.Ltmp293:
	.size	I2C_OwnAddress2Config, .Ltmp293-I2C_OwnAddress2Config

	.globl	I2C_DualAddressCmd
	.align	2
	.type	I2C_DualAddressCmd,%function
	.code	16                      @ @I2C_DualAddressCmd
	.thumb_func
I2C_DualAddressCmd:
@ BB#0:
	ldrh	r2, [r0, #12]
	cmp	r1, #0
	ite	eq
	biceq	r1, r2, #1
	orrne	r1, r2, #1
	strh	r1, [r0, #12]
	bx	lr
.Ltmp294:
	.size	I2C_DualAddressCmd, .Ltmp294-I2C_DualAddressCmd

	.globl	I2C_GeneralCallCmd
	.align	2
	.type	I2C_GeneralCallCmd,%function
	.code	16                      @ @I2C_GeneralCallCmd
	.thumb_func
I2C_GeneralCallCmd:
@ BB#0:
	ldrh	r2, [r0]
	cmp	r1, #0
	ite	eq
	biceq	r1, r2, #64
	orrne	r1, r2, #64
	strh	r1, [r0]
	bx	lr
.Ltmp295:
	.size	I2C_GeneralCallCmd, .Ltmp295-I2C_GeneralCallCmd

	.globl	I2C_SoftwareResetCmd
	.align	2
	.type	I2C_SoftwareResetCmd,%function
	.code	16                      @ @I2C_SoftwareResetCmd
	.thumb_func
I2C_SoftwareResetCmd:
@ BB#0:
	ldrh	r2, [r0]
	cmp	r1, #0
	ittt	eq
	bfceq	r2, #15, #17
	strheq	r2, [r0]
	bxeq	lr
	orr	r1, r2, #32768
	strh	r1, [r0]
	bx	lr
.Ltmp296:
	.size	I2C_SoftwareResetCmd, .Ltmp296-I2C_SoftwareResetCmd

	.globl	I2C_StretchClockCmd
	.align	2
	.type	I2C_StretchClockCmd,%function
	.code	16                      @ @I2C_StretchClockCmd
	.thumb_func
I2C_StretchClockCmd:
@ BB#0:
	ldrh	r2, [r0]
	cmp	r1, #0
	ite	ne
	bicne	r1, r2, #128
	orreq	r1, r2, #128
	strh	r1, [r0]
	bx	lr
.Ltmp297:
	.size	I2C_StretchClockCmd, .Ltmp297-I2C_StretchClockCmd

	.globl	I2C_FastModeDutyCycleConfig
	.align	2
	.type	I2C_FastModeDutyCycleConfig,%function
	.code	16                      @ @I2C_FastModeDutyCycleConfig
	.thumb_func
I2C_FastModeDutyCycleConfig:
@ BB#0:
	ldrh	r2, [r0, #28]
	cmp.w	r1, #16384
	ite	eq
	orreq	r1, r2, #16384
	bicne	r1, r2, #16384
	strh	r1, [r0, #28]
	bx	lr
.Ltmp298:
	.size	I2C_FastModeDutyCycleConfig, .Ltmp298-I2C_FastModeDutyCycleConfig

	.globl	I2C_NACKPositionConfig
	.align	2
	.type	I2C_NACKPositionConfig,%function
	.code	16                      @ @I2C_NACKPositionConfig
	.thumb_func
I2C_NACKPositionConfig:
@ BB#0:
	ldrh	r2, [r0]
	cmp.w	r1, #2048
	ite	ne
	bicne	r1, r2, #2048
	orreq	r1, r2, #2048
	strh	r1, [r0]
	bx	lr
.Ltmp299:
	.size	I2C_NACKPositionConfig, .Ltmp299-I2C_NACKPositionConfig

	.globl	I2C_SMBusAlertConfig
	.align	2
	.type	I2C_SMBusAlertConfig,%function
	.code	16                      @ @I2C_SMBusAlertConfig
	.thumb_func
I2C_SMBusAlertConfig:
@ BB#0:
	ldrh	r2, [r0]
	cmp.w	r1, #8192
	ite	ne
	bicne	r1, r2, #8192
	orreq	r1, r2, #8192
	strh	r1, [r0]
	bx	lr
.Ltmp300:
	.size	I2C_SMBusAlertConfig, .Ltmp300-I2C_SMBusAlertConfig

	.globl	I2C_ARPCmd
	.align	2
	.type	I2C_ARPCmd,%function
	.code	16                      @ @I2C_ARPCmd
	.thumb_func
I2C_ARPCmd:
@ BB#0:
	ldrh	r2, [r0]
	cmp	r1, #0
	ite	eq
	biceq	r1, r2, #16
	orrne	r1, r2, #16
	strh	r1, [r0]
	bx	lr
.Ltmp301:
	.size	I2C_ARPCmd, .Ltmp301-I2C_ARPCmd

	.globl	I2C_SendData
	.align	2
	.type	I2C_SendData,%function
	.code	16                      @ @I2C_SendData
	.thumb_func
I2C_SendData:
@ BB#0:
	strh	r1, [r0, #16]
	bx	lr
.Ltmp302:
	.size	I2C_SendData, .Ltmp302-I2C_SendData

	.globl	I2C_ReceiveData
	.align	2
	.type	I2C_ReceiveData,%function
	.code	16                      @ @I2C_ReceiveData
	.thumb_func
I2C_ReceiveData:
@ BB#0:
	ldrh	r0, [r0, #16]
	uxtb	r0, r0
	bx	lr
.Ltmp303:
	.size	I2C_ReceiveData, .Ltmp303-I2C_ReceiveData

	.globl	I2C_TransmitPEC
	.align	2
	.type	I2C_TransmitPEC,%function
	.code	16                      @ @I2C_TransmitPEC
	.thumb_func
I2C_TransmitPEC:
@ BB#0:
	ldrh	r2, [r0]
	cmp	r1, #0
	ite	eq
	biceq	r1, r2, #4096
	orrne	r1, r2, #4096
	strh	r1, [r0]
	bx	lr
.Ltmp304:
	.size	I2C_TransmitPEC, .Ltmp304-I2C_TransmitPEC

	.globl	I2C_PECPositionConfig
	.align	2
	.type	I2C_PECPositionConfig,%function
	.code	16                      @ @I2C_PECPositionConfig
	.thumb_func
I2C_PECPositionConfig:
@ BB#0:
	ldrh	r2, [r0]
	cmp.w	r1, #2048
	ite	ne
	bicne	r1, r2, #2048
	orreq	r1, r2, #2048
	strh	r1, [r0]
	bx	lr
.Ltmp305:
	.size	I2C_PECPositionConfig, .Ltmp305-I2C_PECPositionConfig

	.globl	I2C_CalculatePEC
	.align	2
	.type	I2C_CalculatePEC,%function
	.code	16                      @ @I2C_CalculatePEC
	.thumb_func
I2C_CalculatePEC:
@ BB#0:
	ldrh	r2, [r0]
	cmp	r1, #0
	ite	eq
	biceq	r1, r2, #32
	orrne	r1, r2, #32
	strh	r1, [r0]
	bx	lr
.Ltmp306:
	.size	I2C_CalculatePEC, .Ltmp306-I2C_CalculatePEC

	.globl	I2C_GetPEC
	.align	2
	.type	I2C_GetPEC,%function
	.code	16                      @ @I2C_GetPEC
	.thumb_func
I2C_GetPEC:
@ BB#0:
	ldrh	r0, [r0, #24]
	lsrs	r0, r0, #8
	bx	lr
.Ltmp307:
	.size	I2C_GetPEC, .Ltmp307-I2C_GetPEC

	.globl	I2C_DMACmd
	.align	2
	.type	I2C_DMACmd,%function
	.code	16                      @ @I2C_DMACmd
	.thumb_func
I2C_DMACmd:
@ BB#0:
	ldrh	r2, [r0, #4]
	cmp	r1, #0
	ite	eq
	biceq	r1, r2, #2048
	orrne	r1, r2, #2048
	strh	r1, [r0, #4]
	bx	lr
.Ltmp308:
	.size	I2C_DMACmd, .Ltmp308-I2C_DMACmd

	.globl	I2C_DMALastTransferCmd
	.align	2
	.type	I2C_DMALastTransferCmd,%function
	.code	16                      @ @I2C_DMALastTransferCmd
	.thumb_func
I2C_DMALastTransferCmd:
@ BB#0:
	ldrh	r2, [r0, #4]
	cmp	r1, #0
	ite	eq
	biceq	r1, r2, #4096
	orrne	r1, r2, #4096
	strh	r1, [r0, #4]
	bx	lr
.Ltmp309:
	.size	I2C_DMALastTransferCmd, .Ltmp309-I2C_DMALastTransferCmd

	.globl	I2C_ReadRegister
	.align	2
	.type	I2C_ReadRegister,%function
	.code	16                      @ @I2C_ReadRegister
	.thumb_func
I2C_ReadRegister:
@ BB#0:
	sub	sp, #8
	movs	r2, #0
	str	r2, [sp, #4]
	str	r0, [sp, #4]
	ldr	r0, [sp, #4]
	add	r0, r1
	str	r0, [sp, #4]
	ldr	r0, [sp, #4]
	ldrh	r0, [r0]
	add	sp, #8
	bx	lr
.Ltmp310:
	.size	I2C_ReadRegister, .Ltmp310-I2C_ReadRegister

	.globl	I2C_ITConfig
	.align	2
	.type	I2C_ITConfig,%function
	.code	16                      @ @I2C_ITConfig
	.thumb_func
I2C_ITConfig:
@ BB#0:
	cmp	r2, #0
	ldrh	r2, [r0, #4]
	ite	eq
	biceq.w	r1, r2, r1
	orrne	r1, r2
	strh	r1, [r0, #4]
	bx	lr
.Ltmp311:
	.size	I2C_ITConfig, .Ltmp311-I2C_ITConfig

	.globl	I2C_CheckEvent
	.align	2
	.type	I2C_CheckEvent,%function
	.code	16                      @ @I2C_CheckEvent
	.thumb_func
I2C_CheckEvent:
@ BB#0:
	ldrh	r2, [r0, #20]
	ldrh	r0, [r0, #24]
	bfi	r2, r0, #16, #8
	movs	r0, #0
	ands	r2, r1
	cmp	r2, r1
	it	eq
	moveq	r0, #1
	bx	lr
.Ltmp312:
	.size	I2C_CheckEvent, .Ltmp312-I2C_CheckEvent

	.globl	I2C_GetLastEvent
	.align	2
	.type	I2C_GetLastEvent,%function
	.code	16                      @ @I2C_GetLastEvent
	.thumb_func
I2C_GetLastEvent:
@ BB#0:
	ldrh	r1, [r0, #20]
	ldrh	r0, [r0, #24]
	bfi	r1, r0, #16, #8
	mov	r0, r1
	bx	lr
.Ltmp313:
	.size	I2C_GetLastEvent, .Ltmp313-I2C_GetLastEvent

	.globl	I2C_GetFlagStatus
	.align	2
	.type	I2C_GetFlagStatus,%function
	.code	16                      @ @I2C_GetFlagStatus
	.thumb_func
I2C_GetFlagStatus:
@ BB#0:
	sub	sp, #8
	movs	r2, #0
	str	r2, [sp, #4]
	str	r2, [sp]
	str	r0, [sp]
	lsrs	r0, r1, #28
	str	r0, [sp, #4]
	bic	r0, r1, #-16777216
	ldr	r1, [sp, #4]
	cbz	r1, .LBB314_2
@ BB#1:
	ldr	r1, [sp]
	adds	r1, #20
	str	r1, [sp]
	b	.LBB314_3
.LBB314_2:
	ldr	r1, [sp]
	lsrs	r0, r0, #16
	adds	r1, #24
	str	r1, [sp]
.LBB314_3:
	ldr	r1, [sp]
	ldr	r1, [r1]
	ands	r0, r1
	it	ne
	movne	r0, #1
	add	sp, #8
	bx	lr
.Ltmp314:
	.size	I2C_GetFlagStatus, .Ltmp314-I2C_GetFlagStatus

	.globl	I2C_ClearFlag
	.align	2
	.type	I2C_ClearFlag,%function
	.code	16                      @ @I2C_ClearFlag
	.thumb_func
I2C_ClearFlag:
@ BB#0:
	mvns	r1, r1
	strh	r1, [r0, #20]
	bx	lr
.Ltmp315:
	.size	I2C_ClearFlag, .Ltmp315-I2C_ClearFlag

	.globl	I2C_GetITStatus
	.align	2
	.type	I2C_GetITStatus,%function
	.code	16                      @ @I2C_GetITStatus
	.thumb_func
I2C_GetITStatus:
@ BB#0:
	ldrh	r2, [r0, #4]
	and.w	r2, r2, r1, lsr #16
	ands	r2, r2, #1792
	it	ne
	movne	r2, #1
	ldrh	r0, [r0, #20]
	ands	r0, r1
	it	ne
	movne	r0, #1
	ands	r0, r2
	bx	lr
.Ltmp316:
	.size	I2C_GetITStatus, .Ltmp316-I2C_GetITStatus

	.globl	I2C_ClearITPendingBit
	.align	2
	.type	I2C_ClearITPendingBit,%function
	.code	16                      @ @I2C_ClearITPendingBit
	.thumb_func
I2C_ClearITPendingBit:
@ BB#0:
	mvns	r1, r1
	strh	r1, [r0, #20]
	bx	lr
.Ltmp317:
	.size	I2C_ClearITPendingBit, .Ltmp317-I2C_ClearITPendingBit

	.globl	IWDG_WriteAccessCmd
	.align	2
	.type	IWDG_WriteAccessCmd,%function
	.code	16                      @ @IWDG_WriteAccessCmd
	.thumb_func
IWDG_WriteAccessCmd:
@ BB#0:
	movw	r1, #12288
	movt	r1, #16384
	str	r0, [r1]
	bx	lr
.Ltmp318:
	.size	IWDG_WriteAccessCmd, .Ltmp318-IWDG_WriteAccessCmd

	.globl	IWDG_SetPrescaler
	.align	2
	.type	IWDG_SetPrescaler,%function
	.code	16                      @ @IWDG_SetPrescaler
	.thumb_func
IWDG_SetPrescaler:
@ BB#0:
	movw	r1, #12292
	movt	r1, #16384
	str	r0, [r1]
	bx	lr
.Ltmp319:
	.size	IWDG_SetPrescaler, .Ltmp319-IWDG_SetPrescaler

	.globl	IWDG_SetReload
	.align	2
	.type	IWDG_SetReload,%function
	.code	16                      @ @IWDG_SetReload
	.thumb_func
IWDG_SetReload:
@ BB#0:
	movw	r1, #12296
	movt	r1, #16384
	str	r0, [r1]
	bx	lr
.Ltmp320:
	.size	IWDG_SetReload, .Ltmp320-IWDG_SetReload

	.globl	IWDG_ReloadCounter
	.align	2
	.type	IWDG_ReloadCounter,%function
	.code	16                      @ @IWDG_ReloadCounter
	.thumb_func
IWDG_ReloadCounter:
@ BB#0:
	movw	r0, #12288
	movw	r1, #43690
	movt	r0, #16384
	str	r1, [r0]
	bx	lr
.Ltmp321:
	.size	IWDG_ReloadCounter, .Ltmp321-IWDG_ReloadCounter

	.globl	IWDG_Enable
	.align	2
	.type	IWDG_Enable,%function
	.code	16                      @ @IWDG_Enable
	.thumb_func
IWDG_Enable:
@ BB#0:
	movw	r0, #12288
	movw	r1, #52428
	movt	r0, #16384
	str	r1, [r0]
	bx	lr
.Ltmp322:
	.size	IWDG_Enable, .Ltmp322-IWDG_Enable

	.globl	IWDG_GetFlagStatus
	.align	2
	.type	IWDG_GetFlagStatus,%function
	.code	16                      @ @IWDG_GetFlagStatus
	.thumb_func
IWDG_GetFlagStatus:
@ BB#0:
	movw	r1, #12300
	movt	r1, #16384
	ldr	r1, [r1]
	ands	r0, r1
	it	ne
	movne	r0, #1
	bx	lr
.Ltmp323:
	.size	IWDG_GetFlagStatus, .Ltmp323-IWDG_GetFlagStatus

	.globl	PWR_DeInit
	.align	2
	.type	PWR_DeInit,%function
	.code	16                      @ @PWR_DeInit
	.thumb_func
PWR_DeInit:
@ BB#0:
	push	{r7, lr}
	mov.w	r0, #268435456
	movs	r1, #1
	mov	r7, sp
	bl	RCC_APB1PeriphResetCmd
	mov.w	r0, #268435456
	movs	r1, #0
	bl	RCC_APB1PeriphResetCmd
	pop	{r7, pc}
.Ltmp324:
	.size	PWR_DeInit, .Ltmp324-PWR_DeInit

	.globl	PWR_BackupAccessCmd
	.align	2
	.type	PWR_BackupAccessCmd,%function
	.code	16                      @ @PWR_BackupAccessCmd
	.thumb_func
PWR_BackupAccessCmd:
@ BB#0:
	movs	r1, #32
	movt	r1, #16910
	str	r0, [r1]
	bx	lr
.Ltmp325:
	.size	PWR_BackupAccessCmd, .Ltmp325-PWR_BackupAccessCmd

	.globl	PWR_PVDLevelConfig
	.align	2
	.type	PWR_PVDLevelConfig,%function
	.code	16                      @ @PWR_PVDLevelConfig
	.thumb_func
PWR_PVDLevelConfig:
@ BB#0:
	movw	r1, #28672
	movt	r1, #16384
	ldr	r2, [r1]
	bic	r2, r2, #224
	orrs	r0, r2
	str	r0, [r1]
	bx	lr
.Ltmp326:
	.size	PWR_PVDLevelConfig, .Ltmp326-PWR_PVDLevelConfig

	.globl	PWR_PVDCmd
	.align	2
	.type	PWR_PVDCmd,%function
	.code	16                      @ @PWR_PVDCmd
	.thumb_func
PWR_PVDCmd:
@ BB#0:
	movs	r1, #16
	movt	r1, #16910
	str	r0, [r1]
	bx	lr
.Ltmp327:
	.size	PWR_PVDCmd, .Ltmp327-PWR_PVDCmd

	.globl	PWR_WakeUpPinCmd
	.align	2
	.type	PWR_WakeUpPinCmd,%function
	.code	16                      @ @PWR_WakeUpPinCmd
	.thumb_func
PWR_WakeUpPinCmd:
@ BB#0:
	movs	r1, #160
	movt	r1, #16910
	str	r0, [r1]
	bx	lr
.Ltmp328:
	.size	PWR_WakeUpPinCmd, .Ltmp328-PWR_WakeUpPinCmd

	.globl	PWR_BackupRegulatorCmd
	.align	2
	.type	PWR_BackupRegulatorCmd,%function
	.code	16                      @ @PWR_BackupRegulatorCmd
	.thumb_func
PWR_BackupRegulatorCmd:
@ BB#0:
	movs	r1, #164
	movt	r1, #16910
	str	r0, [r1]
	bx	lr
.Ltmp329:
	.size	PWR_BackupRegulatorCmd, .Ltmp329-PWR_BackupRegulatorCmd

	.globl	PWR_MainRegulatorModeConfig
	.align	2
	.type	PWR_MainRegulatorModeConfig,%function
	.code	16                      @ @PWR_MainRegulatorModeConfig
	.thumb_func
PWR_MainRegulatorModeConfig:
@ BB#0:
	movw	r1, #28672
	cmp	r0, #0
	movt	r1, #16384
	ldr	r2, [r1]
	ite	ne
	orrne	r0, r2, #16384
	biceq	r0, r2, #16384
	str	r0, [r1]
	bx	lr
.Ltmp330:
	.size	PWR_MainRegulatorModeConfig, .Ltmp330-PWR_MainRegulatorModeConfig

	.globl	PWR_FlashPowerDownCmd
	.align	2
	.type	PWR_FlashPowerDownCmd,%function
	.code	16                      @ @PWR_FlashPowerDownCmd
	.thumb_func
PWR_FlashPowerDownCmd:
@ BB#0:
	movs	r1, #36
	movt	r1, #16910
	str	r0, [r1]
	bx	lr
.Ltmp331:
	.size	PWR_FlashPowerDownCmd, .Ltmp331-PWR_FlashPowerDownCmd

	.globl	PWR_EnterSTOPMode
	.align	2
	.type	PWR_EnterSTOPMode,%function
	.code	16                      @ @PWR_EnterSTOPMode
	.thumb_func
PWR_EnterSTOPMode:
@ BB#0:
	movw	r2, #28672
	cmp	r1, #1
	movt	r2, #16384
	ldr	r3, [r2]
	bic	r3, r3, #3
	orr.w	r0, r0, r3
	str	r0, [r2]
	movw	r0, #60688
	movt	r0, #57344
	ldr	r2, [r0]
	orr	r2, r2, #4
	str	r2, [r0]
	bne	.LBB332_2
@ BB#1:
	@APP
	wfi
	@NO_APP
	b	.LBB332_3
.LBB332_2:
	@APP
	wfe
	@NO_APP
.LBB332_3:
	ldr	r1, [r0]
	bic	r1, r1, #4
	str	r1, [r0]
	bx	lr
.Ltmp332:
	.size	PWR_EnterSTOPMode, .Ltmp332-PWR_EnterSTOPMode

	.globl	PWR_EnterSTANDBYMode
	.align	2
	.type	PWR_EnterSTANDBYMode,%function
	.code	16                      @ @PWR_EnterSTANDBYMode
	.thumb_func
PWR_EnterSTANDBYMode:
@ BB#0:
	movw	r0, #28672
	movt	r0, #16384
	ldr	r1, [r0]
	orr	r1, r1, #4
	str	r1, [r0]
	ldr	r1, [r0]
	orr	r1, r1, #2
	str	r1, [r0]
	movw	r0, #60688
	movt	r0, #57344
	ldr	r1, [r0]
	orr	r1, r1, #4
	str	r1, [r0]
	@APP
	wfi
	@NO_APP
	bx	lr
.Ltmp333:
	.size	PWR_EnterSTANDBYMode, .Ltmp333-PWR_EnterSTANDBYMode

	.globl	PWR_GetFlagStatus
	.align	2
	.type	PWR_GetFlagStatus,%function
	.code	16                      @ @PWR_GetFlagStatus
	.thumb_func
PWR_GetFlagStatus:
@ BB#0:
	movw	r1, #28676
	movt	r1, #16384
	ldr	r1, [r1]
	ands	r0, r1
	it	ne
	movne	r0, #1
	bx	lr
.Ltmp334:
	.size	PWR_GetFlagStatus, .Ltmp334-PWR_GetFlagStatus

	.globl	PWR_ClearFlag
	.align	2
	.type	PWR_ClearFlag,%function
	.code	16                      @ @PWR_ClearFlag
	.thumb_func
PWR_ClearFlag:
@ BB#0:
	movw	r1, #28672
	movt	r1, #16384
	ldr	r2, [r1]
	orr.w	r0, r2, r0, lsl #2
	str	r0, [r1]
	bx	lr
.Ltmp335:
	.size	PWR_ClearFlag, .Ltmp335-PWR_ClearFlag

	.globl	RCC_DeInit
	.align	2
	.type	RCC_DeInit,%function
	.code	16                      @ @RCC_DeInit
	.thumb_func
RCC_DeInit:
@ BB#0:
	movw	r0, #14336
	movs	r2, #0
	movw	r3, #65535
	movt	r0, #16386
	movt	r3, #65270
	ldr	r1, [r0]
	orr	r1, r1, #1
	str	r1, [r0]
	movw	r1, #14344
	movt	r1, #16386
	str	r2, [r1]
	ldr	r1, [r0]
	ands	r1, r3
	movw	r3, #12304
	str	r1, [r0]
	movw	r1, #14340
	movt	r3, #9216
	movt	r1, #16386
	str	r3, [r1]
	ldr	r1, [r0]
	bic	r1, r1, #262144
	str	r1, [r0]
	movw	r0, #14348
	movt	r0, #16386
	str	r2, [r0]
	bx	lr
.Ltmp336:
	.size	RCC_DeInit, .Ltmp336-RCC_DeInit

	.globl	RCC_HSEConfig
	.align	2
	.type	RCC_HSEConfig,%function
	.code	16                      @ @RCC_HSEConfig
	.thumb_func
RCC_HSEConfig:
@ BB#0:
	movw	r1, #14338
	movs	r2, #0
	movt	r1, #16386
	strb	r2, [r1]
	strb	r0, [r1]
	bx	lr
.Ltmp337:
	.size	RCC_HSEConfig, .Ltmp337-RCC_HSEConfig

	.globl	RCC_WaitForHSEStartUp
	.align	2
	.type	RCC_WaitForHSEStartUp,%function
	.code	16                      @ @RCC_WaitForHSEStartUp
	.thumb_func
RCC_WaitForHSEStartUp:
@ BB#0:
	sub	sp, #8
	movs	r0, #0
	str	r0, [sp, #4]
	movw	r0, #14336
	movt	r0, #16386
.LBB338_1:                              @ =>This Inner Loop Header: Depth=1
	ldr	r1, [r0]
	ldr	r2, [sp, #4]
	adds	r2, #1
	str	r2, [sp, #4]
	ldr	r2, [sp, #4]
	cmp.w	r2, #1280
	beq	.LBB338_3
@ BB#2:                                 @   in Loop: Header=BB338_1 Depth=1
	ands	r1, r1, #131072
	beq	.LBB338_1
.LBB338_3:                              @ %.critedge
	ldr	r0, [r0]
	ubfx	r0, r0, #17, #1
	add	sp, #8
	bx	lr
.Ltmp338:
	.size	RCC_WaitForHSEStartUp, .Ltmp338-RCC_WaitForHSEStartUp

	.globl	RCC_GetFlagStatus
	.align	2
	.type	RCC_GetFlagStatus,%function
	.code	16                      @ @RCC_GetFlagStatus
	.thumb_func
RCC_GetFlagStatus:
@ BB#0:
	movs	r1, #1
	cmp.w	r1, r0, lsr #5
	bne	.LBB339_2
@ BB#1:
	movw	r2, #14336
	b	.LBB339_3
.LBB339_2:
	lsrs	r2, r0, #5
	cmp	r2, #2
	ite	ne
	movwne	r2, #14452
	movweq	r2, #14448
.LBB339_3:
	and	r0, r0, #31
	movt	r2, #16386
	lsl.w	r0, r1, r0
	ldr	r1, [r2]
	ands	r0, r1
	it	ne
	movne	r0, #1
	bx	lr
.Ltmp339:
	.size	RCC_GetFlagStatus, .Ltmp339-RCC_GetFlagStatus

	.globl	RCC_AdjustHSICalibrationValue
	.align	2
	.type	RCC_AdjustHSICalibrationValue,%function
	.code	16                      @ @RCC_AdjustHSICalibrationValue
	.thumb_func
RCC_AdjustHSICalibrationValue:
@ BB#0:
	movw	r1, #14336
	movt	r1, #16386
	ldr	r2, [r1]
	bic	r2, r2, #248
	orr.w	r0, r2, r0, lsl #3
	str	r0, [r1]
	bx	lr
.Ltmp340:
	.size	RCC_AdjustHSICalibrationValue, .Ltmp340-RCC_AdjustHSICalibrationValue

	.globl	RCC_HSICmd
	.align	2
	.type	RCC_HSICmd,%function
	.code	16                      @ @RCC_HSICmd
	.thumb_func
RCC_HSICmd:
@ BB#0:
	movs	r1, #0
	movt	r1, #16967
	str	r0, [r1]
	bx	lr
.Ltmp341:
	.size	RCC_HSICmd, .Ltmp341-RCC_HSICmd

	.globl	RCC_LSEConfig
	.align	2
	.type	RCC_LSEConfig,%function
	.code	16                      @ @RCC_LSEConfig
	.thumb_func
RCC_LSEConfig:
@ BB#0:
	movw	r1, #14448
	movs	r2, #0
	cmp	r0, #4
	movt	r1, #16386
	strb	r2, [r1]
	strb	r2, [r1]
	bne	.LBB342_2
@ BB#1:
	movs	r0, #5
	b	.LBB342_3
.LBB342_2:
	cmp	r0, #1
	it	ne
	bxne	lr
	movs	r0, #1
.LBB342_3:
	strb	r0, [r1]
	bx	lr
.Ltmp342:
	.size	RCC_LSEConfig, .Ltmp342-RCC_LSEConfig

	.globl	RCC_LSICmd
	.align	2
	.type	RCC_LSICmd,%function
	.code	16                      @ @RCC_LSICmd
	.thumb_func
RCC_LSICmd:
@ BB#0:
	movw	r1, #3712
	movt	r1, #16967
	str	r0, [r1]
	bx	lr
.Ltmp343:
	.size	RCC_LSICmd, .Ltmp343-RCC_LSICmd

	.globl	RCC_PLLConfig
	.align	2
	.type	RCC_PLLConfig,%function
	.code	16                      @ @RCC_PLLConfig
	.thumb_func
RCC_PLLConfig:
@ BB#0:
	orrs	r0, r1
	ldr	r1, [sp]
	orr.w	r0, r0, r2, lsl #6
	orr.w	r0, r0, r1, lsl #24
	movs	r1, #0
	movt	r1, #65535
	and.w	r1, r1, r3, lsl #15
	sub.w	r1, r1, #65536
	orrs	r0, r1
	movw	r1, #14340
	movt	r1, #16386
	str	r0, [r1]
	bx	lr
.Ltmp344:
	.size	RCC_PLLConfig, .Ltmp344-RCC_PLLConfig

	.globl	RCC_PLLCmd
	.align	2
	.type	RCC_PLLCmd,%function
	.code	16                      @ @RCC_PLLCmd
	.thumb_func
RCC_PLLCmd:
@ BB#0:
	movs	r1, #96
	movt	r1, #16967
	str	r0, [r1]
	bx	lr
.Ltmp345:
	.size	RCC_PLLCmd, .Ltmp345-RCC_PLLCmd

	.globl	RCC_PLLI2SConfig
	.align	2
	.type	RCC_PLLI2SConfig,%function
	.code	16                      @ @RCC_PLLI2SConfig
	.thumb_func
RCC_PLLI2SConfig:
@ BB#0:
	lsls	r1, r1, #28
	orr.w	r0, r1, r0, lsl #6
	movw	r1, #14468
	movt	r1, #16386
	str	r0, [r1]
	bx	lr
.Ltmp346:
	.size	RCC_PLLI2SConfig, .Ltmp346-RCC_PLLI2SConfig

	.globl	RCC_PLLI2SCmd
	.align	2
	.type	RCC_PLLI2SCmd,%function
	.code	16                      @ @RCC_PLLI2SCmd
	.thumb_func
RCC_PLLI2SCmd:
@ BB#0:
	movs	r1, #104
	movt	r1, #16967
	str	r0, [r1]
	bx	lr
.Ltmp347:
	.size	RCC_PLLI2SCmd, .Ltmp347-RCC_PLLI2SCmd

	.globl	RCC_ClockSecuritySystemCmd
	.align	2
	.type	RCC_ClockSecuritySystemCmd,%function
	.code	16                      @ @RCC_ClockSecuritySystemCmd
	.thumb_func
RCC_ClockSecuritySystemCmd:
@ BB#0:
	movs	r1, #76
	movt	r1, #16967
	str	r0, [r1]
	bx	lr
.Ltmp348:
	.size	RCC_ClockSecuritySystemCmd, .Ltmp348-RCC_ClockSecuritySystemCmd

	.globl	RCC_MCO1Config
	.align	2
	.type	RCC_MCO1Config,%function
	.code	16                      @ @RCC_MCO1Config
	.thumb_func
RCC_MCO1Config:
@ BB#0:
	orrs	r0, r1
	movw	r1, #14344
	movt	r1, #16386
	ldr	r2, [r1]
	bic	r2, r2, #123731968
	orrs	r0, r2
	str	r0, [r1]
	bx	lr
.Ltmp349:
	.size	RCC_MCO1Config, .Ltmp349-RCC_MCO1Config

	.globl	RCC_MCO2Config
	.align	2
	.type	RCC_MCO2Config,%function
	.code	16                      @ @RCC_MCO2Config
	.thumb_func
RCC_MCO2Config:
@ BB#0:
	orrs	r0, r1
	movw	r1, #14344
	movt	r1, #16386
	ldr	r2, [r1]
	bic	r2, r2, #-134217728
	orrs	r0, r2
	str	r0, [r1]
	bx	lr
.Ltmp350:
	.size	RCC_MCO2Config, .Ltmp350-RCC_MCO2Config

	.globl	RCC_SYSCLKConfig
	.align	2
	.type	RCC_SYSCLKConfig,%function
	.code	16                      @ @RCC_SYSCLKConfig
	.thumb_func
RCC_SYSCLKConfig:
@ BB#0:
	movw	r1, #14344
	movt	r1, #16386
	ldr	r2, [r1]
	bic	r2, r2, #3
	orrs	r0, r2
	str	r0, [r1]
	bx	lr
.Ltmp351:
	.size	RCC_SYSCLKConfig, .Ltmp351-RCC_SYSCLKConfig

	.globl	RCC_GetSYSCLKSource
	.align	2
	.type	RCC_GetSYSCLKSource,%function
	.code	16                      @ @RCC_GetSYSCLKSource
	.thumb_func
RCC_GetSYSCLKSource:
@ BB#0:
	movw	r0, #14344
	movt	r0, #16386
	ldr	r0, [r0]
	and	r0, r0, #12
	bx	lr
.Ltmp352:
	.size	RCC_GetSYSCLKSource, .Ltmp352-RCC_GetSYSCLKSource

	.globl	RCC_HCLKConfig
	.align	2
	.type	RCC_HCLKConfig,%function
	.code	16                      @ @RCC_HCLKConfig
	.thumb_func
RCC_HCLKConfig:
@ BB#0:
	movw	r1, #14344
	movt	r1, #16386
	ldr	r2, [r1]
	bic	r2, r2, #240
	orrs	r0, r2
	str	r0, [r1]
	bx	lr
.Ltmp353:
	.size	RCC_HCLKConfig, .Ltmp353-RCC_HCLKConfig

	.globl	RCC_PCLK1Config
	.align	2
	.type	RCC_PCLK1Config,%function
	.code	16                      @ @RCC_PCLK1Config
	.thumb_func
RCC_PCLK1Config:
@ BB#0:
	movw	r1, #14344
	movt	r1, #16386
	ldr	r2, [r1]
	bic	r2, r2, #7168
	orrs	r0, r2
	str	r0, [r1]
	bx	lr
.Ltmp354:
	.size	RCC_PCLK1Config, .Ltmp354-RCC_PCLK1Config

	.globl	RCC_PCLK2Config
	.align	2
	.type	RCC_PCLK2Config,%function
	.code	16                      @ @RCC_PCLK2Config
	.thumb_func
RCC_PCLK2Config:
@ BB#0:
	movw	r1, #14344
	movt	r1, #16386
	ldr	r2, [r1]
	bic	r2, r2, #57344
	orr.w	r0, r2, r0, lsl #3
	str	r0, [r1]
	bx	lr
.Ltmp355:
	.size	RCC_PCLK2Config, .Ltmp355-RCC_PCLK2Config

	.globl	RCC_GetClocksFreq
	.align	2
	.type	RCC_GetClocksFreq,%function
	.code	16                      @ @RCC_GetClocksFreq
	.thumb_func
RCC_GetClocksFreq:
@ BB#0:
	push	{r4, lr}
	movw	r4, #14344
	movt	r4, #16386
	ldr	r2, [r4]
	and	r2, r2, #12
	cmp	r2, #8
	beq	.LBB356_3
@ BB#1:
	cmp	r2, #4
	bne	.LBB356_5
@ BB#2:
	movw	r2, #4608
	movt	r2, #122
	b	.LBB356_8
.LBB356_3:
	movw	r12, #14340
	movt	r12, #16386
	ldr.w	r2, [r12]
	ldr.w	r3, [r12]
	and	r3, r3, #63
	tst.w	r2, #4194304
	beq	.LBB356_6
@ BB#4:
	movw	r2, #4608
	movt	r2, #122
	b	.LBB356_7
.LBB356_5:
	cmp	r2, #0
	movw	r2, #9216
	movt	r2, #244
	b	.LBB356_8
.LBB356_6:
	movw	r2, #9216
	movt	r2, #244
.LBB356_7:
	udiv	r2, r2, r3
	ldr.w	r3, [r12]
	ubfx	r3, r3, #6, #9
	mul	lr, r3, r2
	ldr.w	r2, [r12]
	movs	r3, #2
	ubfx	r2, r2, #16, #2
	add.w	r2, r3, r2, lsl #1
	udiv	r2, lr, r2
.LBB356_8:
	str	r2, [r0]
	movw	r3, :lower16:APBAHBPrescTable
	ldr	r2, [r4]
	movt	r3, :upper16:APBAHBPrescTable
	ubfx	r2, r2, #4, #4
	ldrb	r2, [r3, r2]
	ldr	r1, [r0]
	lsrs	r1, r2
	str	r1, [r0, #4]
	ldr	r2, [r4]
	ubfx	r2, r2, #10, #3
	ldrb	r2, [r3, r2]
	lsrs	r1, r2
	str	r1, [r0, #8]
	ldr	r1, [r4]
	ubfx	r1, r1, #13, #3
	ldrb	r1, [r3, r1]
	ldr	r2, [r0, #4]
	lsr.w	r1, r2, r1
	str	r1, [r0, #12]
	pop	{r4, pc}
.Ltmp356:
	.size	RCC_GetClocksFreq, .Ltmp356-RCC_GetClocksFreq

	.globl	RCC_RTCCLKConfig
	.align	2
	.type	RCC_RTCCLKConfig,%function
	.code	16                      @ @RCC_RTCCLKConfig
	.thumb_func
RCC_RTCCLKConfig:
@ BB#0:
	and	r1, r0, #768
	cmp.w	r1, #768
	bne	.LBB357_2
@ BB#1:
	movw	r2, #14344
	movw	r1, #64767
	movt	r2, #16386
	movt	r1, #4095
	ldr	r3, [r2]
	ands	r1, r0
	bic	r3, r3, #2031616
	orrs	r1, r3
	str	r1, [r2]
.LBB357_2:
	movw	r1, #14448
	bfc	r0, #12, #20
	movt	r1, #16386
	ldr	r2, [r1]
	orrs	r0, r2
	str	r0, [r1]
	bx	lr
.Ltmp357:
	.size	RCC_RTCCLKConfig, .Ltmp357-RCC_RTCCLKConfig

	.globl	RCC_RTCCLKCmd
	.align	2
	.type	RCC_RTCCLKCmd,%function
	.code	16                      @ @RCC_RTCCLKCmd
	.thumb_func
RCC_RTCCLKCmd:
@ BB#0:
	movw	r1, #3644
	movt	r1, #16967
	str	r0, [r1]
	bx	lr
.Ltmp358:
	.size	RCC_RTCCLKCmd, .Ltmp358-RCC_RTCCLKCmd

	.globl	RCC_BackupResetCmd
	.align	2
	.type	RCC_BackupResetCmd,%function
	.code	16                      @ @RCC_BackupResetCmd
	.thumb_func
RCC_BackupResetCmd:
@ BB#0:
	movw	r1, #3648
	movt	r1, #16967
	str	r0, [r1]
	bx	lr
.Ltmp359:
	.size	RCC_BackupResetCmd, .Ltmp359-RCC_BackupResetCmd

	.globl	RCC_I2SCLKConfig
	.align	2
	.type	RCC_I2SCLKConfig,%function
	.code	16                      @ @RCC_I2SCLKConfig
	.thumb_func
RCC_I2SCLKConfig:
@ BB#0:
	movw	r1, #348
	movt	r1, #16967
	str	r0, [r1]
	bx	lr
.Ltmp360:
	.size	RCC_I2SCLKConfig, .Ltmp360-RCC_I2SCLKConfig

	.globl	RCC_AHB1PeriphClockCmd
	.align	2
	.type	RCC_AHB1PeriphClockCmd,%function
	.code	16                      @ @RCC_AHB1PeriphClockCmd
	.thumb_func
RCC_AHB1PeriphClockCmd:
@ BB#0:
	cmp	r1, #0
	movw	r1, #14384
	movt	r1, #16386
	ldr	r2, [r1]
	ite	eq
	biceq.w	r0, r2, r0
	orrne	r0, r2
	str	r0, [r1]
	bx	lr
.Ltmp361:
	.size	RCC_AHB1PeriphClockCmd, .Ltmp361-RCC_AHB1PeriphClockCmd

	.globl	RCC_AHB2PeriphClockCmd
	.align	2
	.type	RCC_AHB2PeriphClockCmd,%function
	.code	16                      @ @RCC_AHB2PeriphClockCmd
	.thumb_func
RCC_AHB2PeriphClockCmd:
@ BB#0:
	cmp	r1, #0
	movw	r1, #14388
	movt	r1, #16386
	ldr	r2, [r1]
	ite	eq
	biceq.w	r0, r2, r0
	orrne	r0, r2
	str	r0, [r1]
	bx	lr
.Ltmp362:
	.size	RCC_AHB2PeriphClockCmd, .Ltmp362-RCC_AHB2PeriphClockCmd

	.globl	RCC_AHB3PeriphClockCmd
	.align	2
	.type	RCC_AHB3PeriphClockCmd,%function
	.code	16                      @ @RCC_AHB3PeriphClockCmd
	.thumb_func
RCC_AHB3PeriphClockCmd:
@ BB#0:
	cmp	r1, #0
	movw	r1, #14392
	movt	r1, #16386
	ldr	r2, [r1]
	ite	eq
	biceq.w	r0, r2, r0
	orrne	r0, r2
	str	r0, [r1]
	bx	lr
.Ltmp363:
	.size	RCC_AHB3PeriphClockCmd, .Ltmp363-RCC_AHB3PeriphClockCmd

	.globl	RCC_APB1PeriphClockCmd
	.align	2
	.type	RCC_APB1PeriphClockCmd,%function
	.code	16                      @ @RCC_APB1PeriphClockCmd
	.thumb_func
RCC_APB1PeriphClockCmd:
@ BB#0:
	cmp	r1, #0
	movw	r1, #14400
	movt	r1, #16386
	ldr	r2, [r1]
	ite	eq
	biceq.w	r0, r2, r0
	orrne	r0, r2
	str	r0, [r1]
	bx	lr
.Ltmp364:
	.size	RCC_APB1PeriphClockCmd, .Ltmp364-RCC_APB1PeriphClockCmd

	.globl	RCC_APB2PeriphClockCmd
	.align	2
	.type	RCC_APB2PeriphClockCmd,%function
	.code	16                      @ @RCC_APB2PeriphClockCmd
	.thumb_func
RCC_APB2PeriphClockCmd:
@ BB#0:
	cmp	r1, #0
	movw	r1, #14404
	movt	r1, #16386
	ldr	r2, [r1]
	ite	eq
	biceq.w	r0, r2, r0
	orrne	r0, r2
	str	r0, [r1]
	bx	lr
.Ltmp365:
	.size	RCC_APB2PeriphClockCmd, .Ltmp365-RCC_APB2PeriphClockCmd

	.globl	RCC_AHB1PeriphResetCmd
	.align	2
	.type	RCC_AHB1PeriphResetCmd,%function
	.code	16                      @ @RCC_AHB1PeriphResetCmd
	.thumb_func
RCC_AHB1PeriphResetCmd:
@ BB#0:
	cmp	r1, #0
	movw	r1, #14352
	movt	r1, #16386
	ldr	r2, [r1]
	ite	eq
	biceq.w	r0, r2, r0
	orrne	r0, r2
	str	r0, [r1]
	bx	lr
.Ltmp366:
	.size	RCC_AHB1PeriphResetCmd, .Ltmp366-RCC_AHB1PeriphResetCmd

	.globl	RCC_AHB2PeriphResetCmd
	.align	2
	.type	RCC_AHB2PeriphResetCmd,%function
	.code	16                      @ @RCC_AHB2PeriphResetCmd
	.thumb_func
RCC_AHB2PeriphResetCmd:
@ BB#0:
	cmp	r1, #0
	movw	r1, #14356
	movt	r1, #16386
	ldr	r2, [r1]
	ite	eq
	biceq.w	r0, r2, r0
	orrne	r0, r2
	str	r0, [r1]
	bx	lr
.Ltmp367:
	.size	RCC_AHB2PeriphResetCmd, .Ltmp367-RCC_AHB2PeriphResetCmd

	.globl	RCC_AHB3PeriphResetCmd
	.align	2
	.type	RCC_AHB3PeriphResetCmd,%function
	.code	16                      @ @RCC_AHB3PeriphResetCmd
	.thumb_func
RCC_AHB3PeriphResetCmd:
@ BB#0:
	cmp	r1, #0
	movw	r1, #14360
	movt	r1, #16386
	ldr	r2, [r1]
	ite	eq
	biceq.w	r0, r2, r0
	orrne	r0, r2
	str	r0, [r1]
	bx	lr
.Ltmp368:
	.size	RCC_AHB3PeriphResetCmd, .Ltmp368-RCC_AHB3PeriphResetCmd

	.globl	RCC_APB1PeriphResetCmd
	.align	2
	.type	RCC_APB1PeriphResetCmd,%function
	.code	16                      @ @RCC_APB1PeriphResetCmd
	.thumb_func
RCC_APB1PeriphResetCmd:
@ BB#0:
	cmp	r1, #0
	movw	r1, #14368
	movt	r1, #16386
	ldr	r2, [r1]
	ite	eq
	biceq.w	r0, r2, r0
	orrne	r0, r2
	str	r0, [r1]
	bx	lr
.Ltmp369:
	.size	RCC_APB1PeriphResetCmd, .Ltmp369-RCC_APB1PeriphResetCmd

	.globl	RCC_APB2PeriphResetCmd
	.align	2
	.type	RCC_APB2PeriphResetCmd,%function
	.code	16                      @ @RCC_APB2PeriphResetCmd
	.thumb_func
RCC_APB2PeriphResetCmd:
@ BB#0:
	cmp	r1, #0
	movw	r1, #14372
	movt	r1, #16386
	ldr	r2, [r1]
	ite	eq
	biceq.w	r0, r2, r0
	orrne	r0, r2
	str	r0, [r1]
	bx	lr
.Ltmp370:
	.size	RCC_APB2PeriphResetCmd, .Ltmp370-RCC_APB2PeriphResetCmd

	.globl	RCC_AHB1PeriphClockLPModeCmd
	.align	2
	.type	RCC_AHB1PeriphClockLPModeCmd,%function
	.code	16                      @ @RCC_AHB1PeriphClockLPModeCmd
	.thumb_func
RCC_AHB1PeriphClockLPModeCmd:
@ BB#0:
	cmp	r1, #0
	movw	r1, #14416
	movt	r1, #16386
	ldr	r2, [r1]
	ite	eq
	biceq.w	r0, r2, r0
	orrne	r0, r2
	str	r0, [r1]
	bx	lr
.Ltmp371:
	.size	RCC_AHB1PeriphClockLPModeCmd, .Ltmp371-RCC_AHB1PeriphClockLPModeCmd

	.globl	RCC_AHB2PeriphClockLPModeCmd
	.align	2
	.type	RCC_AHB2PeriphClockLPModeCmd,%function
	.code	16                      @ @RCC_AHB2PeriphClockLPModeCmd
	.thumb_func
RCC_AHB2PeriphClockLPModeCmd:
@ BB#0:
	cmp	r1, #0
	movw	r1, #14420
	movt	r1, #16386
	ldr	r2, [r1]
	ite	eq
	biceq.w	r0, r2, r0
	orrne	r0, r2
	str	r0, [r1]
	bx	lr
.Ltmp372:
	.size	RCC_AHB2PeriphClockLPModeCmd, .Ltmp372-RCC_AHB2PeriphClockLPModeCmd

	.globl	RCC_AHB3PeriphClockLPModeCmd
	.align	2
	.type	RCC_AHB3PeriphClockLPModeCmd,%function
	.code	16                      @ @RCC_AHB3PeriphClockLPModeCmd
	.thumb_func
RCC_AHB3PeriphClockLPModeCmd:
@ BB#0:
	cmp	r1, #0
	movw	r1, #14424
	movt	r1, #16386
	ldr	r2, [r1]
	ite	eq
	biceq.w	r0, r2, r0
	orrne	r0, r2
	str	r0, [r1]
	bx	lr
.Ltmp373:
	.size	RCC_AHB3PeriphClockLPModeCmd, .Ltmp373-RCC_AHB3PeriphClockLPModeCmd

	.globl	RCC_APB1PeriphClockLPModeCmd
	.align	2
	.type	RCC_APB1PeriphClockLPModeCmd,%function
	.code	16                      @ @RCC_APB1PeriphClockLPModeCmd
	.thumb_func
RCC_APB1PeriphClockLPModeCmd:
@ BB#0:
	cmp	r1, #0
	movw	r1, #14432
	movt	r1, #16386
	ldr	r2, [r1]
	ite	eq
	biceq.w	r0, r2, r0
	orrne	r0, r2
	str	r0, [r1]
	bx	lr
.Ltmp374:
	.size	RCC_APB1PeriphClockLPModeCmd, .Ltmp374-RCC_APB1PeriphClockLPModeCmd

	.globl	RCC_APB2PeriphClockLPModeCmd
	.align	2
	.type	RCC_APB2PeriphClockLPModeCmd,%function
	.code	16                      @ @RCC_APB2PeriphClockLPModeCmd
	.thumb_func
RCC_APB2PeriphClockLPModeCmd:
@ BB#0:
	cmp	r1, #0
	movw	r1, #14436
	movt	r1, #16386
	ldr	r2, [r1]
	ite	eq
	biceq.w	r0, r2, r0
	orrne	r0, r2
	str	r0, [r1]
	bx	lr
.Ltmp375:
	.size	RCC_APB2PeriphClockLPModeCmd, .Ltmp375-RCC_APB2PeriphClockLPModeCmd

	.globl	RCC_ITConfig
	.align	2
	.type	RCC_ITConfig,%function
	.code	16                      @ @RCC_ITConfig
	.thumb_func
RCC_ITConfig:
@ BB#0:
	cmp	r1, #0
	movw	r1, #14349
	movt	r1, #16386
	ldrb	r2, [r1]
	ite	eq
	biceq.w	r0, r2, r0
	orrne	r0, r2
	strb	r0, [r1]
	bx	lr
.Ltmp376:
	.size	RCC_ITConfig, .Ltmp376-RCC_ITConfig

	.globl	RCC_ClearFlag
	.align	2
	.type	RCC_ClearFlag,%function
	.code	16                      @ @RCC_ClearFlag
	.thumb_func
RCC_ClearFlag:
@ BB#0:
	movw	r0, #14452
	movt	r0, #16386
	ldr	r1, [r0]
	orr	r1, r1, #16777216
	str	r1, [r0]
	bx	lr
.Ltmp377:
	.size	RCC_ClearFlag, .Ltmp377-RCC_ClearFlag

	.globl	RCC_GetITStatus
	.align	2
	.type	RCC_GetITStatus,%function
	.code	16                      @ @RCC_GetITStatus
	.thumb_func
RCC_GetITStatus:
@ BB#0:
	movw	r1, #14348
	movt	r1, #16386
	ldr	r1, [r1]
	ands	r0, r1
	it	ne
	movne	r0, #1
	bx	lr
.Ltmp378:
	.size	RCC_GetITStatus, .Ltmp378-RCC_GetITStatus

	.globl	RCC_ClearITPendingBit
	.align	2
	.type	RCC_ClearITPendingBit,%function
	.code	16                      @ @RCC_ClearITPendingBit
	.thumb_func
RCC_ClearITPendingBit:
@ BB#0:
	movw	r1, #14350
	movt	r1, #16386
	strb	r0, [r1]
	bx	lr
.Ltmp379:
	.size	RCC_ClearITPendingBit, .Ltmp379-RCC_ClearITPendingBit

	.globl	RNG_DeInit
	.align	2
	.type	RNG_DeInit,%function
	.code	16                      @ @RNG_DeInit
	.thumb_func
RNG_DeInit:
@ BB#0:
	push	{r7, lr}
	movs	r0, #64
	movs	r1, #1
	mov	r7, sp
	bl	RCC_AHB2PeriphResetCmd
	movs	r0, #64
	movs	r1, #0
	bl	RCC_AHB2PeriphResetCmd
	pop	{r7, pc}
.Ltmp380:
	.size	RNG_DeInit, .Ltmp380-RNG_DeInit

	.globl	RNG_Cmd
	.align	2
	.type	RNG_Cmd,%function
	.code	16                      @ @RNG_Cmd
	.thumb_func
RNG_Cmd:
@ BB#0:
	movw	r1, #2048
	cmp	r0, #0
	movt	r1, #20486
	ldr	r2, [r1]
	ite	eq
	biceq	r0, r2, #4
	orrne	r0, r2, #4
	str	r0, [r1]
	bx	lr
.Ltmp381:
	.size	RNG_Cmd, .Ltmp381-RNG_Cmd

	.globl	RNG_GetRandomNumber
	.align	2
	.type	RNG_GetRandomNumber,%function
	.code	16                      @ @RNG_GetRandomNumber
	.thumb_func
RNG_GetRandomNumber:
@ BB#0:
	movw	r0, #2056
	movt	r0, #20486
	ldr	r0, [r0]
	bx	lr
.Ltmp382:
	.size	RNG_GetRandomNumber, .Ltmp382-RNG_GetRandomNumber

	.globl	RNG_ITConfig
	.align	2
	.type	RNG_ITConfig,%function
	.code	16                      @ @RNG_ITConfig
	.thumb_func
RNG_ITConfig:
@ BB#0:
	movw	r1, #2048
	cmp	r0, #0
	movt	r1, #20486
	ldr	r2, [r1]
	ite	eq
	biceq	r0, r2, #8
	orrne	r0, r2, #8
	str	r0, [r1]
	bx	lr
.Ltmp383:
	.size	RNG_ITConfig, .Ltmp383-RNG_ITConfig

	.globl	RNG_GetFlagStatus
	.align	2
	.type	RNG_GetFlagStatus,%function
	.code	16                      @ @RNG_GetFlagStatus
	.thumb_func
RNG_GetFlagStatus:
@ BB#0:
	movw	r1, #2052
	movt	r1, #20486
	ldr	r1, [r1]
	ands	r0, r1
	it	ne
	movne	r0, #1
	bx	lr
.Ltmp384:
	.size	RNG_GetFlagStatus, .Ltmp384-RNG_GetFlagStatus

	.globl	RNG_ClearFlag
	.align	2
	.type	RNG_ClearFlag,%function
	.code	16                      @ @RNG_ClearFlag
	.thumb_func
RNG_ClearFlag:
@ BB#0:
	movw	r1, #2052
	mvn.w	r0, r0, lsl #4
	movt	r1, #20486
	str	r0, [r1]
	bx	lr
.Ltmp385:
	.size	RNG_ClearFlag, .Ltmp385-RNG_ClearFlag

	.globl	RNG_GetITStatus
	.align	2
	.type	RNG_GetITStatus,%function
	.code	16                      @ @RNG_GetITStatus
	.thumb_func
RNG_GetITStatus:
@ BB#0:
	movw	r1, #2052
	movt	r1, #20486
	ldr	r1, [r1]
	ands	r0, r1
	it	ne
	movne	r0, #1
	bx	lr
.Ltmp386:
	.size	RNG_GetITStatus, .Ltmp386-RNG_GetITStatus

	.globl	RNG_ClearITPendingBit
	.align	2
	.type	RNG_ClearITPendingBit,%function
	.code	16                      @ @RNG_ClearITPendingBit
	.thumb_func
RNG_ClearITPendingBit:
@ BB#0:
	movw	r1, #2052
	eor	r0, r0, #255
	movt	r1, #20486
	str	r0, [r1]
	bx	lr
.Ltmp387:
	.size	RNG_ClearITPendingBit, .Ltmp387-RNG_ClearITPendingBit

	.globl	RTC_DeInit
	.align	2
	.type	RTC_DeInit,%function
	.code	16                      @ @RTC_DeInit
	.thumb_func
RTC_DeInit:
@ BB#0:
	sub	sp, #16
	movw	r12, #10276
	movs	r0, #0
	movs	r2, #202
	movt	r12, #16384
	str	r0, [sp, #4]
	str.w	r2, [r12]
	movs	r2, #83
	str.w	r2, [r12]
	movw	r2, #10252
	str	r0, [sp, #8]
	movt	r2, #16384
	ldr	r3, [r2]
	tst.w	r3, #64
	bne	.LBB388_5
@ BB#1:
	mov.w	r3, #-1
	str	r3, [r2]
.LBB388_2:                              @ =>This Inner Loop Header: Depth=1
	ldr	r3, [r2]
	ldr	r1, [sp, #8]
	adds	r1, #1
	str	r1, [sp, #8]
	ldr	r1, [sp, #8]
	cmp.w	r1, #65536
	beq	.LBB388_4
@ BB#3:                                 @   in Loop: Header=BB388_2 Depth=1
	ands	r1, r3, #64
	beq	.LBB388_2
.LBB388_4:                              @ %RTC_EnterInitMode.exit
	ldr	r1, [r2]
	tst.w	r1, #64
	beq	.LBB388_13
.LBB388_5:                              @ %RTC_EnterInitMode.exit.thread
	movw	r1, #10240
	movw	r3, #10248
	movt	r1, #16384
	movt	r3, #16384
	str	r0, [r1]
	movw	r0, #10244
	movw	r1, #8449
	movt	r0, #16384
	str	r1, [r0]
	ldr	r0, [r3]
	and	r0, r0, #7
	str	r0, [r3]
.LBB388_6:                              @ =>This Inner Loop Header: Depth=1
	ldr	r0, [r2]
	ldr	r1, [sp, #4]
	adds	r1, #1
	str	r1, [sp, #4]
	ldr	r1, [sp, #4]
	cmp.w	r1, #65536
	beq	.LBB388_8
@ BB#7:                                 @   in Loop: Header=BB388_6 Depth=1
	ands	r0, r0, #4
	beq	.LBB388_6
.LBB388_8:                              @ %.critedge
	ldr	r1, [r2]
	movs	r0, #0
	tst.w	r1, #4
	beq	.LBB388_14
@ BB#9:
	ldr	r1, [r3]
	str	r0, [r3]
	movw	r3, #65535
	movw	r1, #10260
	movt	r1, #16384
	str	r3, [r1]
	movw	r1, #10256
	movs	r3, #255
	movt	r1, #16384
	movt	r3, #127
	str	r3, [r1]
	movw	r1, #10264
	movt	r1, #16384
	str	r0, [r1]
	movw	r1, #10268
	movt	r1, #16384
	str	r0, [r1]
	movw	r1, #10272
	movt	r1, #16384
	str	r0, [r1]
	movw	r1, #10304
	str	r0, [r2]
	movt	r1, #16384
	str	r0, [r1]
	str	r0, [sp, #12]
	movs	r0, #202
	str.w	r0, [r12]
	movs	r0, #83
	str.w	r0, [r12]
	ldr	r0, [r2]
	bic	r0, r0, #160
	str	r0, [r2]
.LBB388_10:                             @ =>This Inner Loop Header: Depth=1
	ldr	r0, [r2]
	ldr	r1, [sp, #12]
	adds	r1, #1
	str	r1, [sp, #12]
	ldr	r1, [sp, #12]
	cmp.w	r1, #131072
	beq	.LBB388_12
@ BB#11:                                @   in Loop: Header=BB388_10 Depth=1
	ands	r0, r0, #32
	beq	.LBB388_10
.LBB388_12:                             @ %RTC_WaitForSynchro.exit
	ldr	r0, [r2]
	movs	r1, #255
	str.w	r1, [r12]
	ubfx	r0, r0, #5, #1
	b	.LBB388_14
.LBB388_13:
	movs	r0, #0
.LBB388_14:
	movs	r1, #255
	str.w	r1, [r12]
	add	sp, #16
	bx	lr
.Ltmp388:
	.size	RTC_DeInit, .Ltmp388-RTC_DeInit

	.globl	RTC_EnterInitMode
	.align	2
	.type	RTC_EnterInitMode,%function
	.code	16                      @ @RTC_EnterInitMode
	.thumb_func
RTC_EnterInitMode:
@ BB#0:
	sub	sp, #8
	movs	r0, #0
	str	r0, [sp, #4]
	movw	r0, #10252
	movt	r0, #16384
	ldr	r1, [r0]
	tst.w	r1, #64
	ittt	ne
	movne	r0, #1
	addne	sp, #8
	bxne	lr
	mov.w	r1, #-1
	str	r1, [r0]
.LBB389_1:                              @ =>This Inner Loop Header: Depth=1
	ldr	r1, [r0]
	ldr	r2, [sp, #4]
	adds	r2, #1
	str	r2, [sp, #4]
	ldr	r2, [sp, #4]
	cmp.w	r2, #65536
	beq	.LBB389_3
@ BB#2:                                 @   in Loop: Header=BB389_1 Depth=1
	ands	r1, r1, #64
	beq	.LBB389_1
.LBB389_3:                              @ %.critedge
	ldr	r0, [r0]
	ubfx	r0, r0, #6, #1
	add	sp, #8
	bx	lr
.Ltmp389:
	.size	RTC_EnterInitMode, .Ltmp389-RTC_EnterInitMode

	.globl	RTC_WaitForSynchro
	.align	2
	.type	RTC_WaitForSynchro,%function
	.code	16                      @ @RTC_WaitForSynchro
	.thumb_func
RTC_WaitForSynchro:
@ BB#0:
	sub	sp, #8
	movs	r0, #0
	movs	r1, #202
	str	r0, [sp, #4]
	movw	r0, #10276
	movt	r0, #16384
	str	r1, [r0]
	movs	r1, #83
	str	r1, [r0]
	movw	r1, #10252
	movt	r1, #16384
	ldr	r2, [r1]
	bic	r2, r2, #160
	str	r2, [r1]
.LBB390_1:                              @ =>This Inner Loop Header: Depth=1
	ldr	r2, [r1]
	ldr	r3, [sp, #4]
	adds	r3, #1
	str	r3, [sp, #4]
	ldr	r3, [sp, #4]
	cmp.w	r3, #131072
	beq	.LBB390_3
@ BB#2:                                 @   in Loop: Header=BB390_1 Depth=1
	ands	r2, r2, #32
	beq	.LBB390_1
.LBB390_3:                              @ %.critedge
	ldr	r1, [r1]
	movs	r2, #255
	str	r2, [r0]
	ubfx	r0, r1, #5, #1
	add	sp, #8
	bx	lr
.Ltmp390:
	.size	RTC_WaitForSynchro, .Ltmp390-RTC_WaitForSynchro

	.globl	RTC_Init
	.align	2
	.type	RTC_Init,%function
	.code	16                      @ @RTC_Init
	.thumb_func
RTC_Init:
@ BB#0:
	push.w	{r11, lr}
	sub	sp, #8
	movw	r12, #10276
	movs	r2, #202
	movt	r12, #16384
	str.w	r2, [r12]
	movs	r2, #83
	str.w	r2, [r12]
	movs	r2, #0
	str	r2, [sp, #4]
	movw	r2, #10252
	movt	r2, #16384
	ldr	r3, [r2]
	tst.w	r3, #64
	bne	.LBB391_5
@ BB#1:
	mov.w	r3, #-1
	str	r3, [r2]
.LBB391_2:                              @ =>This Inner Loop Header: Depth=1
	ldr	r3, [r2]
	ldr	r1, [sp, #4]
	adds	r1, #1
	str	r1, [sp, #4]
	ldr	r1, [sp, #4]
	cmp.w	r1, #65536
	beq	.LBB391_4
@ BB#3:                                 @   in Loop: Header=BB391_2 Depth=1
	ands	r1, r3, #64
	beq	.LBB391_2
.LBB391_4:                              @ %RTC_EnterInitMode.exit
	ldr	r1, [r2]
	tst.w	r1, #64
	beq	.LBB391_7
.LBB391_5:                              @ %RTC_EnterInitMode.exit.thread
	movw	r1, #10248
	movt	r1, #16384
	ldr	r3, [r1]
	bic	r3, r3, #64
	str	r3, [r1]
	ldr.w	lr, [r0]
	ldr	r3, [r1]
	orr.w	r3, r3, lr
	str	r3, [r1]
	movw	r3, #10256
	ldr	r1, [r0, #8]
	movt	r3, #16384
	str	r1, [r3]
	ldr	r0, [r0, #4]
	ldr	r1, [r3]
	orr.w	r0, r1, r0, lsl #16
	str	r0, [r3]
	ldr	r0, [r2]
	bic	r0, r0, #128
	str	r0, [r2]
	movs	r0, #1
.LBB391_6:
	movs	r1, #255
	str.w	r1, [r12]
	add	sp, #8
	pop.w	{r11, pc}
.LBB391_7:
	movs	r0, #0
	b	.LBB391_6
.Ltmp391:
	.size	RTC_Init, .Ltmp391-RTC_Init

	.globl	RTC_ExitInitMode
	.align	2
	.type	RTC_ExitInitMode,%function
	.code	16                      @ @RTC_ExitInitMode
	.thumb_func
RTC_ExitInitMode:
@ BB#0:
	movw	r0, #10252
	movt	r0, #16384
	ldr	r1, [r0]
	bic	r1, r1, #128
	str	r1, [r0]
	bx	lr
.Ltmp392:
	.size	RTC_ExitInitMode, .Ltmp392-RTC_ExitInitMode

	.globl	RTC_StructInit
	.align	2
	.type	RTC_StructInit,%function
	.code	16                      @ @RTC_StructInit
	.thumb_func
RTC_StructInit:
@ BB#0:
	movs	r1, #0
	movs	r2, #127
	movs	r3, #255
	stm.w	r0, {r1, r2, r3}
	bx	lr
.Ltmp393:
	.size	RTC_StructInit, .Ltmp393-RTC_StructInit

	.globl	RTC_WriteProtectionCmd
	.align	2
	.type	RTC_WriteProtectionCmd,%function
	.code	16                      @ @RTC_WriteProtectionCmd
	.thumb_func
RTC_WriteProtectionCmd:
@ BB#0:
	cmp	r0, #0
	itttt	ne
	movwne	r0, #10276
	movtne	r0, #16384
	movne	r1, #255
	strne	r1, [r0]
	it	ne
	bxne	lr
	movw	r0, #10276
	movs	r1, #202
	movt	r0, #16384
	str	r1, [r0]
	movs	r1, #83
	str	r1, [r0]
	bx	lr
.Ltmp394:
	.size	RTC_WriteProtectionCmd, .Ltmp394-RTC_WriteProtectionCmd

	.globl	RTC_RefClockCmd
	.align	2
	.type	RTC_RefClockCmd,%function
	.code	16                      @ @RTC_RefClockCmd
	.thumb_func
RTC_RefClockCmd:
@ BB#0:
	sub	sp, #8
	movw	r12, #10276
	movs	r1, #202
	movw	r2, #10252
	movt	r12, #16384
	movt	r2, #16384
	str.w	r1, [r12]
	movs	r1, #83
	str.w	r1, [r12]
	movs	r1, #0
	str	r1, [sp, #4]
	ldr	r1, [r2]
	tst.w	r1, #64
	bne	.LBB395_5
@ BB#1:
	mov.w	r1, #-1
	str	r1, [r2]
.LBB395_2:                              @ =>This Inner Loop Header: Depth=1
	ldr	r3, [r2]
	ldr	r1, [sp, #4]
	adds	r1, #1
	str	r1, [sp, #4]
	ldr	r1, [sp, #4]
	cmp.w	r1, #65536
	beq	.LBB395_4
@ BB#3:                                 @   in Loop: Header=BB395_2 Depth=1
	ands	r1, r3, #64
	beq	.LBB395_2
.LBB395_4:                              @ %RTC_EnterInitMode.exit
	ldr	r1, [r2]
	tst.w	r1, #64
	beq	.LBB395_7
.LBB395_5:                              @ %RTC_EnterInitMode.exit.thread
	movw	r3, #10248
	cmp	r0, #0
	movt	r3, #16384
	ldr	r1, [r3]
	ite	eq
	biceq	r0, r1, #16
	orrne	r0, r1, #16
	str	r0, [r3]
	ldr	r0, [r2]
	bic	r0, r0, #128
	str	r0, [r2]
	movs	r0, #1
.LBB395_6:
	movs	r1, #255
	str.w	r1, [r12]
	add	sp, #8
	bx	lr
.LBB395_7:
	movs	r0, #0
	b	.LBB395_6
.Ltmp395:
	.size	RTC_RefClockCmd, .Ltmp395-RTC_RefClockCmd

	.globl	RTC_BypassShadowCmd
	.align	2
	.type	RTC_BypassShadowCmd,%function
	.code	16                      @ @RTC_BypassShadowCmd
	.thumb_func
RTC_BypassShadowCmd:
@ BB#0:
	movw	r1, #10276
	movs	r2, #202
	cmp	r0, #0
	movt	r1, #16384
	str	r2, [r1]
	mov.w	r2, #83
	str	r2, [r1]
	movw	r2, #10248
	movt	r2, #16384
	ldr	r3, [r2]
	ite	eq
	andeq	r0, r3, #223
	orrne	r0, r3, #32
	str	r0, [r2]
	movs	r0, #255
	str	r0, [r1]
	bx	lr
.Ltmp396:
	.size	RTC_BypassShadowCmd, .Ltmp396-RTC_BypassShadowCmd

	.globl	RTC_SetTime
	.align	2
	.type	RTC_SetTime,%function
	.code	16                      @ @RTC_SetTime
	.thumb_func
RTC_SetTime:
@ BB#0:
	push.w	{r4, r5, r11, lr}
	sub	sp, #8
	movw	r2, #10248
	cmp	r0, #0
	movt	r2, #16384
	ldr	r2, [r2]
	and	r2, r2, #64
	beq	.LBB397_3
@ BB#1:
	cmp	r2, #0
	beq	.LBB397_10
@ BB#2:                                 @ %._crit_edge
	ldrb	r0, [r1, #3]
	b	.LBB397_11
.LBB397_3:
	cmp	r2, #0
	mov.w	lr, #0
	itt	eq
	moveq	r0, #0
	strbeq	r0, [r1, #3]
	ldrb.w	r12, [r1]
	cmp.w	r12, #10
	blo	.LBB397_5
.LBB397_4:                              @ %.lr.ph.i9
                                        @ =>This Inner Loop Header: Depth=1
	add.w	r0, r12, #246
	add.w	lr, lr, #1
	uxtb.w	r12, r0
	cmp.w	r12, #9
	bhi	.LBB397_4
.LBB397_5:                              @ %RTC_ByteToBcd2.exit12
	ldrb	r5, [r1, #1]
	movs	r0, #0
	cmp	r5, #10
	blo	.LBB397_7
.LBB397_6:                              @ %.lr.ph.i4
                                        @ =>This Inner Loop Header: Depth=1
	add.w	r2, r5, #246
	adds	r0, #1
	uxtb	r5, r2
	cmp	r5, #9
	bhi	.LBB397_6
.LBB397_7:                              @ %RTC_ByteToBcd2.exit7
	ldrb	r4, [r1, #2]
	movs	r2, #0
	cmp	r4, #10
	blo	.LBB397_9
.LBB397_8:                              @ %.lr.ph.i
                                        @ =>This Inner Loop Header: Depth=1
	adds	r4, #246
	adds	r2, #1
	uxtb	r4, r4
	cmp	r4, #9
	bhi	.LBB397_8
.LBB397_9:                              @ %RTC_ByteToBcd2.exit
	lsl.w	r3, lr, #4
	lsls	r0, r0, #4
	ldrb	r1, [r1, #3]
	lsls	r2, r2, #4
	uxtb	r3, r3
	uxtb	r0, r0
	uxtb	r2, r2
	orr.w	r3, r3, r12
	orrs	r0, r5
	lsls	r3, r3, #16
	lsls	r0, r0, #8
	orrs	r0, r3
	orrs	r0, r4
	orrs	r0, r2
	orr.w	r2, r0, r1, lsl #16
	b	.LBB397_12
.LBB397_10:                             @ %.thread13
	movs	r0, #0
	strb	r0, [r1, #3]
.LBB397_11:
	ldrb	r3, [r1, #1]
	ldrb	r2, [r1]
	ldrb	r1, [r1, #2]
	lsls	r3, r3, #8
	orr.w	r2, r3, r2, lsl #16
	orrs	r1, r2
	orr.w	r2, r1, r0, lsl #16
.LBB397_12:
	movw	r1, #10276
	movw	r0, #10252
	mov.w	r12, #202
	mov.w	lr, #83
	movs	r4, #0
	movt	r1, #16384
	movt	r0, #16384
	str.w	r12, [r1]
	str.w	lr, [r1]
	str	r4, [sp, #4]
	ldr	r3, [r0]
	tst.w	r3, #64
	bne	.LBB397_17
@ BB#13:
	mov.w	r3, #-1
	str	r3, [r0]
.LBB397_14:                             @ =>This Inner Loop Header: Depth=1
	ldr	r3, [r0]
	ldr	r5, [sp, #4]
	adds	r5, #1
	str	r5, [sp, #4]
	ldr	r5, [sp, #4]
	cmp.w	r5, #65536
	beq	.LBB397_16
@ BB#15:                                @   in Loop: Header=BB397_14 Depth=1
	ands	r3, r3, #64
	beq	.LBB397_14
.LBB397_16:                             @ %RTC_EnterInitMode.exit
	ldr	r3, [r0]
	tst.w	r3, #64
	beq	.LBB397_22
.LBB397_17:                             @ %RTC_EnterInitMode.exit.thread
	movw	r3, #32639
	movt	r3, #127
	ands	r2, r3
	movw	r3, #10240
	movt	r3, #16384
	str	r2, [r3]
	ldr	r2, [r0]
	bic	r2, r2, #128
	str	r2, [r0]
	str	r4, [sp]
	str.w	r12, [r1]
	str.w	lr, [r1]
	ldr	r2, [r0]
	bic	r2, r2, #160
	str	r2, [r0]
.LBB397_18:                             @ =>This Inner Loop Header: Depth=1
	ldr	r2, [r0]
	ldr	r3, [sp]
	adds	r3, #1
	str	r3, [sp]
	ldr	r3, [sp]
	cmp.w	r3, #131072
	beq	.LBB397_20
@ BB#19:                                @   in Loop: Header=BB397_18 Depth=1
	ands	r2, r2, #32
	beq	.LBB397_18
.LBB397_20:                             @ %RTC_WaitForSynchro.exit
	ldr	r0, [r0]
	movs	r2, #255
	str	r2, [r1]
	ubfx	r0, r0, #5, #1
.LBB397_21:
	movs	r2, #255
	str	r2, [r1]
	add	sp, #8
	pop.w	{r4, r5, r11, pc}
.LBB397_22:
	movs	r0, #0
	b	.LBB397_21
.Ltmp397:
	.size	RTC_SetTime, .Ltmp397-RTC_SetTime

	.globl	RTC_TimeStructInit
	.align	2
	.type	RTC_TimeStructInit,%function
	.code	16                      @ @RTC_TimeStructInit
	.thumb_func
RTC_TimeStructInit:
@ BB#0:
	movs	r1, #0
	strb	r1, [r0, #3]
	strb	r1, [r0, #2]
	strb	r1, [r0, #1]
	strb	r1, [r0]
	bx	lr
.Ltmp398:
	.size	RTC_TimeStructInit, .Ltmp398-RTC_TimeStructInit

	.globl	RTC_GetTime
	.align	2
	.type	RTC_GetTime,%function
	.code	16                      @ @RTC_GetTime
	.thumb_func
RTC_GetTime:
@ BB#0:
	push	{r4, lr}
	movw	r2, #10240
	movs	r4, #64
	cmp	r0, #0
	movt	r2, #16384
	ldr	r2, [r2]
	ubfx	r3, r2, #16, #6
	and.w	r4, r4, r2, lsr #16
	and	r12, r2, #127
	strb	r3, [r1]
	ubfx	lr, r2, #8, #7
	strb.w	lr, [r1, #1]
	strb.w	r12, [r1, #2]
	strb	r4, [r1, #3]
	it	ne
	popne	{r4, pc}
	lsrs	r4, r2, #16
	lsrs	r3, r3, #4
	lsrs	r0, r2, #8
	and	r4, r4, #15
	add.w	r3, r3, r3, lsl #2
	and	r0, r0, #15
	add.w	r3, r4, r3, lsl #1
	strb	r3, [r1]
	lsr.w	r3, lr, #4
	add.w	r3, r3, r3, lsl #2
	add.w	r0, r0, r3, lsl #1
	strb	r0, [r1, #1]
	and	r0, r2, #15
	lsr.w	r2, r12, #4
	add.w	r2, r2, r2, lsl #2
	add.w	r0, r0, r2, lsl #1
	strb	r0, [r1, #2]
	pop	{r4, pc}
.Ltmp399:
	.size	RTC_GetTime, .Ltmp399-RTC_GetTime

	.globl	RTC_GetSubSecond
	.align	2
	.type	RTC_GetSubSecond,%function
	.code	16                      @ @RTC_GetSubSecond
	.thumb_func
RTC_GetSubSecond:
@ BB#0:
	movw	r0, #10280
	movw	r1, #10244
	movt	r0, #16384
	movt	r1, #16384
	ldr	r0, [r0]
	ldr	r1, [r1]
	bx	lr
.Ltmp400:
	.size	RTC_GetSubSecond, .Ltmp400-RTC_GetSubSecond

	.globl	RTC_SetDate
	.align	2
	.type	RTC_SetDate,%function
	.code	16                      @ @RTC_SetDate
	.thumb_func
RTC_SetDate:
@ BB#0:
	push.w	{r4, r5, r11, lr}
	sub	sp, #8
	cmp	r0, #0
	beq	.LBB401_2
@ BB#1:
	ldrb	r2, [r1, #1]
	ldrb	r0, [r1]
	ldrb	r3, [r1, #2]
	ldrb	r1, [r1, #3]
	lsls	r2, r2, #8
	orr.w	r1, r2, r1, lsl #16
	orrs	r1, r3
	orr.w	r2, r1, r0, lsl #13
	b	.LBB401_9
.LBB401_2:
	ldrb	r0, [r1, #1]
	mov.w	lr, #0
	tst.w	r0, #16
	ittt	ne
	andne	r0, r0, #239
	addne	r0, #10
	strbne	r0, [r1, #1]
	ldrb.w	r12, [r1, #3]
	cmp.w	r12, #10
	blo	.LBB401_4
.LBB401_3:                              @ %.lr.ph.i9
                                        @ =>This Inner Loop Header: Depth=1
	add.w	r2, r12, #246
	add.w	lr, lr, #1
	uxtb.w	r12, r2
	cmp.w	r12, #9
	bhi	.LBB401_3
.LBB401_4:                              @ %RTC_ByteToBcd2.exit12
	uxtb	r5, r0
	movs	r0, #0
	cmp	r5, #10
	blo	.LBB401_6
.LBB401_5:                              @ %.lr.ph.i4
                                        @ =>This Inner Loop Header: Depth=1
	add.w	r2, r5, #246
	adds	r0, #1
	uxtb	r5, r2
	cmp	r5, #9
	bhi	.LBB401_5
.LBB401_6:                              @ %RTC_ByteToBcd2.exit7
	ldrb	r4, [r1, #2]
	movs	r2, #0
	cmp	r4, #10
	blo	.LBB401_8
.LBB401_7:                              @ %.lr.ph.i
                                        @ =>This Inner Loop Header: Depth=1
	adds	r4, #246
	adds	r2, #1
	uxtb	r4, r4
	cmp	r4, #9
	bhi	.LBB401_7
.LBB401_8:                              @ %RTC_ByteToBcd2.exit
	lsl.w	r3, lr, #4
	lsls	r0, r0, #4
	ldrb	r1, [r1]
	lsls	r2, r2, #4
	uxtb	r3, r3
	uxtb	r0, r0
	uxtb	r2, r2
	orr.w	r3, r3, r12
	orrs	r0, r5
	lsls	r3, r3, #16
	lsls	r0, r0, #8
	orrs	r0, r3
	orrs	r0, r4
	orrs	r0, r2
	orr.w	r2, r0, r1, lsl #13
.LBB401_9:
	movw	r1, #10276
	movw	r0, #10252
	mov.w	r12, #202
	mov.w	lr, #83
	movs	r4, #0
	movt	r1, #16384
	movt	r0, #16384
	str.w	r12, [r1]
	str.w	lr, [r1]
	str	r4, [sp, #4]
	ldr	r3, [r0]
	tst.w	r3, #64
	bne	.LBB401_14
@ BB#10:
	mov.w	r3, #-1
	str	r3, [r0]
.LBB401_11:                             @ =>This Inner Loop Header: Depth=1
	ldr	r3, [r0]
	ldr	r5, [sp, #4]
	adds	r5, #1
	str	r5, [sp, #4]
	ldr	r5, [sp, #4]
	cmp.w	r5, #65536
	beq	.LBB401_13
@ BB#12:                                @   in Loop: Header=BB401_11 Depth=1
	ands	r3, r3, #64
	beq	.LBB401_11
.LBB401_13:                             @ %RTC_EnterInitMode.exit
	ldr	r3, [r0]
	tst.w	r3, #64
	beq	.LBB401_19
.LBB401_14:                             @ %RTC_EnterInitMode.exit.thread
	movw	r3, #65343
	movt	r3, #255
	ands	r2, r3
	movw	r3, #10244
	movt	r3, #16384
	str	r2, [r3]
	ldr	r2, [r0]
	bic	r2, r2, #128
	str	r2, [r0]
	str	r4, [sp]
	str.w	r12, [r1]
	str.w	lr, [r1]
	ldr	r2, [r0]
	bic	r2, r2, #160
	str	r2, [r0]
.LBB401_15:                             @ =>This Inner Loop Header: Depth=1
	ldr	r2, [r0]
	ldr	r3, [sp]
	adds	r3, #1
	str	r3, [sp]
	ldr	r3, [sp]
	cmp.w	r3, #131072
	beq	.LBB401_17
@ BB#16:                                @   in Loop: Header=BB401_15 Depth=1
	ands	r2, r2, #32
	beq	.LBB401_15
.LBB401_17:                             @ %RTC_WaitForSynchro.exit
	ldr	r0, [r0]
	movs	r2, #255
	str	r2, [r1]
	ubfx	r0, r0, #5, #1
.LBB401_18:
	movs	r2, #255
	str	r2, [r1]
	add	sp, #8
	pop.w	{r4, r5, r11, pc}
.LBB401_19:
	movs	r0, #0
	b	.LBB401_18
.Ltmp401:
	.size	RTC_SetDate, .Ltmp401-RTC_SetDate

	.globl	RTC_DateStructInit
	.align	2
	.type	RTC_DateStructInit,%function
	.code	16                      @ @RTC_DateStructInit
	.thumb_func
RTC_DateStructInit:
@ BB#0:
	movs	r1, #0
	strb	r1, [r0, #3]
	movs	r1, #1
	strb	r1, [r0, #2]
	strb	r1, [r0, #1]
	strb	r1, [r0]
	bx	lr
.Ltmp402:
	.size	RTC_DateStructInit, .Ltmp402-RTC_DateStructInit

	.globl	RTC_GetDate
	.align	2
	.type	RTC_GetDate,%function
	.code	16                      @ @RTC_GetDate
	.thumb_func
RTC_GetDate:
@ BB#0:
	push	{r4, lr}
	movw	r2, #10244
	cmp	r0, #0
	movt	r2, #16384
	ldr	r2, [r2]
	lsr.w	r3, r2, #16
	and	r12, r2, #63
	strb	r3, [r1, #3]
	ubfx	lr, r2, #8, #5
	strb.w	lr, [r1, #1]
	strb.w	r12, [r1, #2]
	ubfx	r4, r2, #13, #3
	strb	r4, [r1]
	it	ne
	popne	{r4, pc}
	ubfx	r4, r2, #20, #4
	and	r3, r3, #15
	lsrs	r0, r2, #8
	add.w	r4, r4, r4, lsl #2
	and	r0, r0, #15
	add.w	r3, r3, r4, lsl #1
	strb	r3, [r1, #3]
	movs	r3, #0
	sub.w	r3, r3, lr, lsr #4
	and	r3, r3, #10
	add	r0, r3
	strb	r0, [r1, #1]
	and	r0, r2, #15
	lsr.w	r2, r12, #4
	add.w	r2, r2, r2, lsl #2
	add.w	r0, r0, r2, lsl #1
	strb	r0, [r1, #2]
	pop	{r4, pc}
.Ltmp403:
	.size	RTC_GetDate, .Ltmp403-RTC_GetDate

	.globl	RTC_SetAlarm
	.align	2
	.type	RTC_SetAlarm,%function
	.code	16                      @ @RTC_SetAlarm
	.thumb_func
RTC_SetAlarm:
@ BB#0:
	push.w	{r4, r5, r6, r7, r8, r9, r11, lr}
	movw	r3, #10248
	cmp	r0, #0
	movt	r3, #16384
	ldr	r3, [r3]
	and	r3, r3, #64
	beq	.LBB404_3
@ BB#1:
	cmp	r3, #0
	beq	.LBB404_12
@ BB#2:                                 @ %..thread17_crit_edge
	ldrb	r0, [r2, #3]
	b	.LBB404_13
.LBB404_3:
	cmp	r3, #0
	mov.w	lr, #0
	itt	eq
	moveq	r0, #0
	strbeq	r0, [r2, #3]
	ldrb.w	r12, [r2]
	cmp.w	r12, #10
	blo	.LBB404_5
.LBB404_4:                              @ %.lr.ph.i12
                                        @ =>This Inner Loop Header: Depth=1
	add.w	r0, r12, #246
	add.w	lr, lr, #1
	uxtb.w	r12, r0
	cmp.w	r12, #9
	bhi	.LBB404_4
.LBB404_5:                              @ %RTC_ByteToBcd2.exit15
	ldrb.w	r9, [r2, #1]
	movs	r3, #0
	cmp.w	r9, #10
	blo	.LBB404_7
.LBB404_6:                              @ %.lr.ph.i7
                                        @ =>This Inner Loop Header: Depth=1
	add.w	r0, r9, #246
	adds	r3, #1
	uxtb.w	r9, r0
	cmp.w	r9, #9
	bhi	.LBB404_6
.LBB404_7:                              @ %RTC_ByteToBcd2.exit10
	ldrb	r4, [r2, #2]
	movs	r5, #0
	cmp	r4, #10
	blo	.LBB404_9
.LBB404_8:                              @ %.lr.ph.i2
                                        @ =>This Inner Loop Header: Depth=1
	adds	r4, #246
	adds	r5, #1
	uxtb	r4, r4
	cmp	r4, #9
	bhi	.LBB404_8
.LBB404_9:                              @ %RTC_ByteToBcd2.exit5
	ldrb	r6, [r2, #12]
	ldrb.w	r8, [r2, #3]
	movs	r7, #0
	cmp	r6, #10
	blo	.LBB404_11
.LBB404_10:                             @ %.lr.ph.i
                                        @ =>This Inner Loop Header: Depth=1
	adds	r6, #246
	adds	r7, #1
	uxtb	r6, r6
	cmp	r6, #9
	bhi	.LBB404_10
.LBB404_11:                             @ %RTC_ByteToBcd2.exit
	lsl.w	r0, lr, #4
	lsls	r3, r3, #4
	lsls	r5, r5, #4
	orr.w	r7, r6, r7, lsl #4
	uxtb	r0, r0
	uxtb	r3, r3
	uxtb	r5, r5
	orr.w	r0, r0, r12
	orr.w	r3, r3, r9
	lsl.w	r12, r0, #16
	lsls	r3, r3, #8
	lsl.w	r0, r8, #16
	orr.w	r3, r3, r12
	orrs	r3, r4
	orrs	r3, r5
	orrs	r0, r3
	ldr	r3, [r2, #4]
	ldr	r2, [r2, #8]
	orrs	r0, r2
	orrs	r0, r3
	orr.w	r0, r0, r7, lsl #24
	b	.LBB404_14
.LBB404_12:                             @ %.thread16
	movs	r0, #0
	strb	r0, [r2, #3]
.LBB404_13:                             @ %.thread17
	ldrb	r7, [r2, #1]
	ldrb	r3, [r2]
	ldrb	r6, [r2, #2]
	lsls	r7, r7, #8
	orr.w	r3, r7, r3, lsl #16
	ldr	r7, [r2, #8]
	orrs	r3, r6
	orr.w	r0, r3, r0, lsl #16
	ldr	r3, [r2, #4]
	ldrb	r2, [r2, #12]
	orrs	r0, r7
	orr.w	r0, r0, r2, lsl #24
	orrs	r0, r3
.LBB404_14:
	movw	r2, #10276
	movs	r3, #202
	cmp.w	r1, #256
	movt	r2, #16384
	str	r3, [r2]
	mov.w	r3, #83
	str	r3, [r2]
	ite	ne
	movwne	r1, #10272
	movweq	r1, #10268
	movt	r1, #16384
	str	r0, [r1]
	movs	r0, #255
	str	r0, [r2]
	pop.w	{r4, r5, r6, r7, r8, r9, r11, pc}
.Ltmp404:
	.size	RTC_SetAlarm, .Ltmp404-RTC_SetAlarm

	.globl	RTC_AlarmStructInit
	.align	2
	.type	RTC_AlarmStructInit,%function
	.code	16                      @ @RTC_AlarmStructInit
	.thumb_func
RTC_AlarmStructInit:
@ BB#0:
	movs	r1, #0
	movs	r2, #1
	strb	r1, [r0, #3]
	strb	r1, [r0]
	strb	r1, [r0, #1]
	strb	r1, [r0, #2]
	str	r1, [r0, #8]
	strb	r2, [r0, #12]
	str	r1, [r0, #4]
	bx	lr
.Ltmp405:
	.size	RTC_AlarmStructInit, .Ltmp405-RTC_AlarmStructInit

	.globl	RTC_GetAlarm
	.align	2
	.type	RTC_GetAlarm,%function
	.code	16                      @ @RTC_GetAlarm
	.thumb_func
RTC_GetAlarm:
@ BB#0:
	push	{r4, r5, r6, lr}
	movw	r3, #10272
	cmp.w	r1, #256
	movt	r3, #16384
	itt	eq
	movweq	r3, #10268
	movteq	r3, #16384
	cmp	r0, #0
	ldr	r1, [r3]
	mov.w	r3, #64
	ubfx	r4, r1, #16, #6
	and	lr, r1, #127
	and.w	r3, r3, r1, lsr #16
	bic	r6, r1, #2139062143
	strb	r4, [r2]
	ubfx	r5, r1, #8, #7
	strb	r5, [r2, #1]
	strb.w	lr, [r2, #2]
	strb	r3, [r2, #3]
	ubfx	r12, r1, #24, #6
	and	r3, r1, #1073741824
	strb.w	r12, [r2, #12]
	str	r6, [r2, #4]
	str	r3, [r2, #8]
	it	ne
	popne	{r4, r5, r6, pc}
	lsrs	r6, r1, #16
	lsrs	r4, r4, #4
	lsrs	r3, r1, #8
	lsrs	r0, r1, #24
	and	r1, r1, #15
	and	r6, r6, #15
	add.w	r4, r4, r4, lsl #2
	and	r3, r3, #15
	and	r0, r0, #15
	add.w	r4, r6, r4, lsl #1
	strb	r4, [r2]
	lsrs	r4, r5, #4
	add.w	r4, r4, r4, lsl #2
	add.w	r3, r3, r4, lsl #1
	strb	r3, [r2, #1]
	lsr.w	r3, lr, #4
	add.w	r3, r3, r3, lsl #2
	add.w	r1, r1, r3, lsl #1
	strb	r1, [r2, #2]
	lsr.w	r1, r12, #4
	add.w	r1, r1, r1, lsl #2
	add.w	r0, r0, r1, lsl #1
	strb	r0, [r2, #12]
	pop	{r4, r5, r6, pc}
.Ltmp406:
	.size	RTC_GetAlarm, .Ltmp406-RTC_GetAlarm

	.globl	RTC_AlarmCmd
	.align	2
	.type	RTC_AlarmCmd,%function
	.code	16                      @ @RTC_AlarmCmd
	.thumb_func
RTC_AlarmCmd:
@ BB#0:
	sub	sp, #8
	movw	r12, #10276
	movs	r2, #0
	movs	r3, #202
	cmp	r1, #0
	movt	r12, #16384
	str	r2, [sp, #4]
	str.w	r3, [r12]
	mov.w	r3, #83
	str.w	r3, [r12]
	beq	.LBB407_2
@ BB#1:
	movw	r1, #10248
	movt	r1, #16384
	ldr	r3, [r1]
	orrs	r0, r3
	str	r0, [r1]
	movs	r0, #1
	b	.LBB407_6
.LBB407_2:
	movw	r1, #10248
	movt	r1, #16384
	ldr	r3, [r1]
	bics	r3, r0
	lsrs	r0, r0, #8
	str	r3, [r1]
	movw	r1, #10252
	movt	r1, #16384
.LBB407_3:                              @ =>This Inner Loop Header: Depth=1
	ldr	r3, [r1]
	ldr	r2, [sp, #4]
	adds	r2, #1
	str	r2, [sp, #4]
	ldr	r2, [sp, #4]
	cmp.w	r2, #65536
	beq	.LBB407_5
@ BB#4:                                 @   in Loop: Header=BB407_3 Depth=1
	ands.w	r2, r3, r0
	beq	.LBB407_3
.LBB407_5:                              @ %.critedge
	ldr	r1, [r1]
	ands	r0, r1
	it	ne
	movne	r0, #1
.LBB407_6:
	movs	r1, #255
	str.w	r1, [r12]
	add	sp, #8
	bx	lr
.Ltmp407:
	.size	RTC_AlarmCmd, .Ltmp407-RTC_AlarmCmd

	.globl	RTC_AlarmSubSecondConfig
	.align	2
	.type	RTC_AlarmSubSecondConfig,%function
	.code	16                      @ @RTC_AlarmSubSecondConfig
	.thumb_func
RTC_AlarmSubSecondConfig:
@ BB#0:
	movw	r12, #10276
	movs	r3, #202
	cmp.w	r0, #256
	orr.w	r1, r1, r2
	movt	r12, #16384
	str.w	r3, [r12]
	mov.w	r3, #83
	str.w	r3, [r12]
	ite	ne
	movwne	r0, #10312
	movweq	r0, #10308
	movt	r0, #16384
	str	r1, [r0]
	movs	r0, #255
	str.w	r0, [r12]
	bx	lr
.Ltmp408:
	.size	RTC_AlarmSubSecondConfig, .Ltmp408-RTC_AlarmSubSecondConfig

	.globl	RTC_GetAlarmSubSecond
	.align	2
	.type	RTC_GetAlarmSubSecond,%function
	.code	16                      @ @RTC_GetAlarmSubSecond
	.thumb_func
RTC_GetAlarmSubSecond:
@ BB#0:
	movw	r1, #10312
	cmp.w	r0, #256
	movt	r1, #16384
	itt	eq
	movweq	r1, #10308
	movteq	r1, #16384
	ldr	r0, [r1]
	bfc	r0, #15, #17
	bx	lr
.Ltmp409:
	.size	RTC_GetAlarmSubSecond, .Ltmp409-RTC_GetAlarmSubSecond

	.globl	RTC_WakeUpClockConfig
	.align	2
	.type	RTC_WakeUpClockConfig,%function
	.code	16                      @ @RTC_WakeUpClockConfig
	.thumb_func
RTC_WakeUpClockConfig:
@ BB#0:
	movw	r1, #10276
	movs	r2, #202
	movt	r1, #16384
	str	r2, [r1]
	movs	r2, #83
	str	r2, [r1]
	movw	r2, #10248
	movt	r2, #16384
	ldr	r3, [r2]
	bic	r3, r3, #7
	str	r3, [r2]
	ldr	r3, [r2]
	orrs	r0, r3
	str	r0, [r2]
	movs	r0, #255
	str	r0, [r1]
	bx	lr
.Ltmp410:
	.size	RTC_WakeUpClockConfig, .Ltmp410-RTC_WakeUpClockConfig

	.globl	RTC_SetWakeUpCounter
	.align	2
	.type	RTC_SetWakeUpCounter,%function
	.code	16                      @ @RTC_SetWakeUpCounter
	.thumb_func
RTC_SetWakeUpCounter:
@ BB#0:
	movw	r1, #10276
	movs	r2, #202
	movt	r1, #16384
	str	r2, [r1]
	movs	r2, #83
	str	r2, [r1]
	movw	r2, #10260
	movt	r2, #16384
	str	r0, [r2]
	movs	r0, #255
	str	r0, [r1]
	bx	lr
.Ltmp411:
	.size	RTC_SetWakeUpCounter, .Ltmp411-RTC_SetWakeUpCounter

	.globl	RTC_GetWakeUpCounter
	.align	2
	.type	RTC_GetWakeUpCounter,%function
	.code	16                      @ @RTC_GetWakeUpCounter
	.thumb_func
RTC_GetWakeUpCounter:
@ BB#0:
	movw	r0, #10260
	movt	r0, #16384
	ldr	r0, [r0]
	uxth	r0, r0
	bx	lr
.Ltmp412:
	.size	RTC_GetWakeUpCounter, .Ltmp412-RTC_GetWakeUpCounter

	.globl	RTC_WakeUpCmd
	.align	2
	.type	RTC_WakeUpCmd,%function
	.code	16                      @ @RTC_WakeUpCmd
	.thumb_func
RTC_WakeUpCmd:
@ BB#0:
	sub	sp, #8
	movs	r1, #0
	movs	r2, #202
	cmp	r0, #0
	str	r1, [sp, #4]
	movw	r1, #10276
	movt	r1, #16384
	str	r2, [r1]
	mov.w	r2, #83
	str	r2, [r1]
	movw	r2, #10248
	movt	r2, #16384
	ldr	r3, [r2]
	beq	.LBB413_2
@ BB#1:
	orr	r0, r3, #1024
	str	r0, [r2]
	movs	r0, #1
	b	.LBB413_6
.LBB413_2:
	bic	r0, r3, #1024
	str	r0, [r2]
	movw	r0, #10252
	movt	r0, #16384
.LBB413_3:                              @ =>This Inner Loop Header: Depth=1
	ldr	r2, [r0]
	ldr	r3, [sp, #4]
	adds	r3, #1
	str	r3, [sp, #4]
	ldr	r3, [sp, #4]
	cmp.w	r3, #65536
	beq	.LBB413_5
@ BB#4:                                 @   in Loop: Header=BB413_3 Depth=1
	ands	r2, r2, #4
	beq	.LBB413_3
.LBB413_5:                              @ %.critedge
	ldr	r0, [r0]
	ubfx	r0, r0, #2, #1
.LBB413_6:
	movs	r2, #255
	str	r2, [r1]
	add	sp, #8
	bx	lr
.Ltmp413:
	.size	RTC_WakeUpCmd, .Ltmp413-RTC_WakeUpCmd

	.globl	RTC_DayLightSavingConfig
	.align	2
	.type	RTC_DayLightSavingConfig,%function
	.code	16                      @ @RTC_DayLightSavingConfig
	.thumb_func
RTC_DayLightSavingConfig:
@ BB#0:
	movw	r12, #10276
	movs	r3, #202
	orrs	r0, r1
	movt	r12, #16384
	str.w	r3, [r12]
	movs	r3, #83
	str.w	r3, [r12]
	movw	r3, #10248
	movt	r3, #16384
	ldr	r2, [r3]
	bic	r2, r2, #262144
	str	r2, [r3]
	ldr	r1, [r3]
	orrs	r0, r1
	str	r0, [r3]
	movs	r0, #255
	str.w	r0, [r12]
	bx	lr
.Ltmp414:
	.size	RTC_DayLightSavingConfig, .Ltmp414-RTC_DayLightSavingConfig

	.globl	RTC_GetStoreOperation
	.align	2
	.type	RTC_GetStoreOperation,%function
	.code	16                      @ @RTC_GetStoreOperation
	.thumb_func
RTC_GetStoreOperation:
@ BB#0:
	movw	r0, #10248
	movt	r0, #16384
	ldr	r0, [r0]
	and	r0, r0, #262144
	bx	lr
.Ltmp415:
	.size	RTC_GetStoreOperation, .Ltmp415-RTC_GetStoreOperation

	.globl	RTC_OutputConfig
	.align	2
	.type	RTC_OutputConfig,%function
	.code	16                      @ @RTC_OutputConfig
	.thumb_func
RTC_OutputConfig:
@ BB#0:
	movw	r12, #10276
	movs	r3, #202
	orrs	r0, r1
	movt	r12, #16384
	str.w	r3, [r12]
	movs	r3, #83
	str.w	r3, [r12]
	movw	r3, #10248
	movt	r3, #16384
	ldr	r2, [r3]
	bic	r2, r2, #7340032
	str	r2, [r3]
	ldr	r1, [r3]
	orrs	r0, r1
	str	r0, [r3]
	movs	r0, #255
	str.w	r0, [r12]
	bx	lr
.Ltmp416:
	.size	RTC_OutputConfig, .Ltmp416-RTC_OutputConfig

	.globl	RTC_CoarseCalibConfig
	.align	2
	.type	RTC_CoarseCalibConfig,%function
	.code	16                      @ @RTC_CoarseCalibConfig
	.thumb_func
RTC_CoarseCalibConfig:
@ BB#0:
	push.w	{r11, lr}
	sub	sp, #8
	movw	r12, #10276
	movs	r2, #202
	movw	lr, #10252
	movt	r12, #16384
	movt	lr, #16384
	str.w	r2, [r12]
	movs	r2, #83
	str.w	r2, [r12]
	movs	r2, #0
	str	r2, [sp, #4]
	ldr.w	r2, [lr]
	tst.w	r2, #64
	bne	.LBB417_5
@ BB#1:
	mov.w	r2, #-1
	str.w	r2, [lr]
.LBB417_2:                              @ =>This Inner Loop Header: Depth=1
	ldr.w	r2, [lr]
	ldr	r3, [sp, #4]
	adds	r3, #1
	str	r3, [sp, #4]
	ldr	r3, [sp, #4]
	cmp.w	r3, #65536
	beq	.LBB417_4
@ BB#3:                                 @   in Loop: Header=BB417_2 Depth=1
	ands	r2, r2, #64
	beq	.LBB417_2
.LBB417_4:                              @ %RTC_EnterInitMode.exit
	ldr.w	r2, [lr]
	tst.w	r2, #64
	beq	.LBB417_7
.LBB417_5:                              @ %RTC_EnterInitMode.exit.thread
	orrs	r0, r1
	movw	r1, #10264
	movt	r1, #16384
	str	r0, [r1]
	ldr.w	r0, [lr]
	bic	r0, r0, #128
	str.w	r0, [lr]
	movs	r0, #1
.LBB417_6:
	movs	r1, #255
	str.w	r1, [r12]
	add	sp, #8
	pop.w	{r11, pc}
.LBB417_7:
	movs	r0, #0
	b	.LBB417_6
.Ltmp417:
	.size	RTC_CoarseCalibConfig, .Ltmp417-RTC_CoarseCalibConfig

	.globl	RTC_CoarseCalibCmd
	.align	2
	.type	RTC_CoarseCalibCmd,%function
	.code	16                      @ @RTC_CoarseCalibCmd
	.thumb_func
RTC_CoarseCalibCmd:
@ BB#0:
	sub	sp, #8
	movw	r12, #10276
	movs	r1, #202
	movw	r2, #10252
	movt	r12, #16384
	movt	r2, #16384
	str.w	r1, [r12]
	movs	r1, #83
	str.w	r1, [r12]
	movs	r1, #0
	str	r1, [sp, #4]
	ldr	r1, [r2]
	tst.w	r1, #64
	bne	.LBB418_5
@ BB#1:
	mov.w	r1, #-1
	str	r1, [r2]
.LBB418_2:                              @ =>This Inner Loop Header: Depth=1
	ldr	r3, [r2]
	ldr	r1, [sp, #4]
	adds	r1, #1
	str	r1, [sp, #4]
	ldr	r1, [sp, #4]
	cmp.w	r1, #65536
	beq	.LBB418_4
@ BB#3:                                 @   in Loop: Header=BB418_2 Depth=1
	ands	r1, r3, #64
	beq	.LBB418_2
.LBB418_4:                              @ %RTC_EnterInitMode.exit
	ldr	r1, [r2]
	tst.w	r1, #64
	beq	.LBB418_7
.LBB418_5:                              @ %RTC_EnterInitMode.exit.thread
	movw	r3, #10248
	cmp	r0, #0
	movt	r3, #16384
	ldr	r1, [r3]
	ite	eq
	biceq	r0, r1, #128
	orrne	r0, r1, #128
	str	r0, [r3]
	ldr	r0, [r2]
	bic	r0, r0, #128
	str	r0, [r2]
	movs	r0, #1
.LBB418_6:
	movs	r1, #255
	str.w	r1, [r12]
	add	sp, #8
	bx	lr
.LBB418_7:
	movs	r0, #0
	b	.LBB418_6
.Ltmp418:
	.size	RTC_CoarseCalibCmd, .Ltmp418-RTC_CoarseCalibCmd

	.globl	RTC_CalibOutputCmd
	.align	2
	.type	RTC_CalibOutputCmd,%function
	.code	16                      @ @RTC_CalibOutputCmd
	.thumb_func
RTC_CalibOutputCmd:
@ BB#0:
	movw	r1, #10276
	movs	r2, #202
	cmp	r0, #0
	movt	r1, #16384
	str	r2, [r1]
	mov.w	r2, #83
	str	r2, [r1]
	movw	r2, #10248
	movt	r2, #16384
	ldr	r3, [r2]
	ite	eq
	biceq	r0, r3, #8388608
	orrne	r0, r3, #8388608
	str	r0, [r2]
	movs	r0, #255
	str	r0, [r1]
	bx	lr
.Ltmp419:
	.size	RTC_CalibOutputCmd, .Ltmp419-RTC_CalibOutputCmd

	.globl	RTC_CalibOutputConfig
	.align	2
	.type	RTC_CalibOutputConfig,%function
	.code	16                      @ @RTC_CalibOutputConfig
	.thumb_func
RTC_CalibOutputConfig:
@ BB#0:
	movw	r1, #10276
	movs	r2, #202
	movt	r1, #16384
	str	r2, [r1]
	movs	r2, #83
	str	r2, [r1]
	movw	r2, #10248
	movt	r2, #16384
	ldr	r3, [r2]
	bic	r3, r3, #524288
	str	r3, [r2]
	ldr	r3, [r2]
	orrs	r0, r3
	str	r0, [r2]
	movs	r0, #255
	str	r0, [r1]
	bx	lr
.Ltmp420:
	.size	RTC_CalibOutputConfig, .Ltmp420-RTC_CalibOutputConfig

	.globl	RTC_SmoothCalibConfig
	.align	2
	.type	RTC_SmoothCalibConfig,%function
	.code	16                      @ @RTC_SmoothCalibConfig
	.thumb_func
RTC_SmoothCalibConfig:
@ BB#0:
	push	{r4, lr}
	movw	r12, #10276
	movs	r3, #202
	movw	lr, #10252
	movt	r12, #16384
	movt	lr, #16384
	str.w	r3, [r12]
	movs	r3, #83
	str.w	r3, [r12]
	ldr.w	r3, [lr]
	tst.w	r3, #65536
	beq	.LBB421_4
@ BB#1:
	mov.w	r3, #131072
.LBB421_2:                              @ %.preheader
                                        @ =>This Inner Loop Header: Depth=1
	ldr.w	r4, [lr]
	tst.w	r4, #65536
	beq	.LBB421_4
@ BB#3:                                 @ %.preheader
                                        @   in Loop: Header=BB421_2 Depth=1
	subs	r4, r3, #1
	cmp	r3, #0
	mov	r3, r4
	bne	.LBB421_2
.LBB421_4:                              @ %.critedge
	ldr.w	r3, [lr]
	tst.w	r3, #65536
	beq	.LBB421_6
@ BB#5:
	movs	r0, #0
	b	.LBB421_7
.LBB421_6:
	orrs	r0, r1
	movw	r1, #10300
	orrs	r0, r2
	movt	r1, #16384
	str	r0, [r1]
	movs	r0, #1
.LBB421_7:
	movs	r1, #255
	str.w	r1, [r12]
	pop	{r4, pc}
.Ltmp421:
	.size	RTC_SmoothCalibConfig, .Ltmp421-RTC_SmoothCalibConfig

	.globl	RTC_TimeStampCmd
	.align	2
	.type	RTC_TimeStampCmd,%function
	.code	16                      @ @RTC_TimeStampCmd
	.thumb_func
RTC_TimeStampCmd:
@ BB#0:
	push.w	{r11, lr}
	movw	r12, #10248
	movw	lr, #10276
	cmp	r1, #0
	movw	r1, #63479
	mov.w	r2, #202
	movt	r12, #16384
	movt	lr, #16384
	movt	r1, #65535
	ldr.w	r3, [r12]
	str.w	r2, [lr]
	mov.w	r2, #83
	str.w	r2, [lr]
	it	ne
	orrne	r0, r0, #2048
	ands	r1, r3
	orrs	r0, r1
	str.w	r0, [r12]
	movs	r0, #255
	str.w	r0, [lr]
	pop.w	{r11, pc}
.Ltmp422:
	.size	RTC_TimeStampCmd, .Ltmp422-RTC_TimeStampCmd

	.globl	RTC_GetTimeStamp
	.align	2
	.type	RTC_GetTimeStamp,%function
	.code	16                      @ @RTC_GetTimeStamp
	.thumb_func
RTC_GetTimeStamp:
@ BB#0:
	push.w	{r11, lr}
	movw	r3, #10288
	cmp	r0, #0
	movt	r3, #16384
	ldr.w	r12, [r3]
	movw	r3, #10292
	movt	r3, #16384
	ldr.w	lr, [r3]
	ubfx	r3, r12, #16, #6
	strb	r3, [r1]
	ubfx	r3, r12, #8, #7
	strb	r3, [r1, #1]
	and	r3, r12, #127
	strb	r3, [r1, #2]
	mov.w	r3, #64
	and.w	r3, r3, r12, lsr #16
	strb	r3, [r1, #3]
	mov.w	r3, #0
	strb	r3, [r2, #3]
	ubfx	r3, lr, #8, #5
	strb	r3, [r2, #1]
	and	r3, lr, #63
	strb	r3, [r2, #2]
	ubfx	r3, lr, #13, #3
	strb	r3, [r2]
	it	ne
	popne.w	{r11, pc}
	ldrb	r0, [r1]
	and	r3, r0, #15
	lsrs	r0, r0, #4
	add.w	r0, r0, r0, lsl #2
	add.w	r0, r3, r0, lsl #1
	strb	r0, [r1]
	ldrb	r0, [r1, #1]
	and	r3, r0, #15
	lsrs	r0, r0, #4
	add.w	r0, r0, r0, lsl #2
	add.w	r0, r3, r0, lsl #1
	strb	r0, [r1, #1]
	ldrb	r0, [r1, #2]
	and	r3, r0, #15
	lsrs	r0, r0, #4
	add.w	r0, r0, r0, lsl #2
	add.w	r0, r3, r0, lsl #1
	strb	r0, [r1, #2]
	ldrb	r0, [r2, #1]
	and	r1, r0, #15
	lsrs	r0, r0, #4
	add.w	r0, r0, r0, lsl #2
	add.w	r0, r1, r0, lsl #1
	strb	r0, [r2, #1]
	ldrb	r0, [r2, #2]
	and	r1, r0, #15
	lsrs	r0, r0, #4
	add.w	r0, r0, r0, lsl #2
	add.w	r0, r1, r0, lsl #1
	strb	r0, [r2, #2]
	ldrb	r0, [r2]
	and	r1, r0, #15
	lsrs	r0, r0, #4
	add.w	r0, r0, r0, lsl #2
	add.w	r0, r1, r0, lsl #1
	strb	r0, [r2]
	pop.w	{r11, pc}
.Ltmp423:
	.size	RTC_GetTimeStamp, .Ltmp423-RTC_GetTimeStamp

	.globl	RTC_GetTimeStampSubSecond
	.align	2
	.type	RTC_GetTimeStampSubSecond,%function
	.code	16                      @ @RTC_GetTimeStampSubSecond
	.thumb_func
RTC_GetTimeStampSubSecond:
@ BB#0:
	movw	r0, #10296
	movt	r0, #16384
	ldr	r0, [r0]
	bx	lr
.Ltmp424:
	.size	RTC_GetTimeStampSubSecond, .Ltmp424-RTC_GetTimeStampSubSecond

	.globl	RTC_TamperTriggerConfig
	.align	2
	.type	RTC_TamperTriggerConfig,%function
	.code	16                      @ @RTC_TamperTriggerConfig
	.thumb_func
RTC_TamperTriggerConfig:
@ BB#0:
	cmp	r1, #0
	movw	r1, #10304
	lsl.w	r0, r0, #1
	movt	r1, #16384
	ldr	r2, [r1]
	ite	ne
	orrne	r0, r2
	biceq.w	r0, r2, r0
	str	r0, [r1]
	bx	lr
.Ltmp425:
	.size	RTC_TamperTriggerConfig, .Ltmp425-RTC_TamperTriggerConfig

	.globl	RTC_TamperCmd
	.align	2
	.type	RTC_TamperCmd,%function
	.code	16                      @ @RTC_TamperCmd
	.thumb_func
RTC_TamperCmd:
@ BB#0:
	cmp	r1, #0
	movw	r1, #10304
	movt	r1, #16384
	ldr	r2, [r1]
	ite	eq
	biceq.w	r0, r2, r0
	orrne	r0, r2
	str	r0, [r1]
	bx	lr
.Ltmp426:
	.size	RTC_TamperCmd, .Ltmp426-RTC_TamperCmd

	.globl	RTC_TamperFilterConfig
	.align	2
	.type	RTC_TamperFilterConfig,%function
	.code	16                      @ @RTC_TamperFilterConfig
	.thumb_func
RTC_TamperFilterConfig:
@ BB#0:
	movw	r1, #10304
	movt	r1, #16384
	ldr	r2, [r1]
	bic	r2, r2, #6144
	str	r2, [r1]
	ldr	r2, [r1]
	orrs	r0, r2
	str	r0, [r1]
	bx	lr
.Ltmp427:
	.size	RTC_TamperFilterConfig, .Ltmp427-RTC_TamperFilterConfig

	.globl	RTC_TamperSamplingFreqConfig
	.align	2
	.type	RTC_TamperSamplingFreqConfig,%function
	.code	16                      @ @RTC_TamperSamplingFreqConfig
	.thumb_func
RTC_TamperSamplingFreqConfig:
@ BB#0:
	movw	r1, #10304
	movt	r1, #16384
	ldr	r2, [r1]
	bic	r2, r2, #1792
	str	r2, [r1]
	ldr	r2, [r1]
	orrs	r0, r2
	str	r0, [r1]
	bx	lr
.Ltmp428:
	.size	RTC_TamperSamplingFreqConfig, .Ltmp428-RTC_TamperSamplingFreqConfig

	.globl	RTC_TamperPinsPrechargeDuration
	.align	2
	.type	RTC_TamperPinsPrechargeDuration,%function
	.code	16                      @ @RTC_TamperPinsPrechargeDuration
	.thumb_func
RTC_TamperPinsPrechargeDuration:
@ BB#0:
	movw	r1, #10304
	movt	r1, #16384
	ldr	r2, [r1]
	bic	r2, r2, #24576
	str	r2, [r1]
	ldr	r2, [r1]
	orrs	r0, r2
	str	r0, [r1]
	bx	lr
.Ltmp429:
	.size	RTC_TamperPinsPrechargeDuration, .Ltmp429-RTC_TamperPinsPrechargeDuration

	.globl	RTC_TimeStampOnTamperDetectionCmd
	.align	2
	.type	RTC_TimeStampOnTamperDetectionCmd,%function
	.code	16                      @ @RTC_TimeStampOnTamperDetectionCmd
	.thumb_func
RTC_TimeStampOnTamperDetectionCmd:
@ BB#0:
	movw	r1, #10304
	cmp	r0, #0
	movt	r1, #16384
	ldr	r2, [r1]
	ite	eq
	biceq	r0, r2, #128
	orrne	r0, r2, #128
	str	r0, [r1]
	bx	lr
.Ltmp430:
	.size	RTC_TimeStampOnTamperDetectionCmd, .Ltmp430-RTC_TimeStampOnTamperDetectionCmd

	.globl	RTC_TamperPullUpCmd
	.align	2
	.type	RTC_TamperPullUpCmd,%function
	.code	16                      @ @RTC_TamperPullUpCmd
	.thumb_func
RTC_TamperPullUpCmd:
@ BB#0:
	movw	r1, #10304
	cmp	r0, #0
	movt	r1, #16384
	ldr	r2, [r1]
	ite	eq
	orreq	r0, r2, #32768
	bicne	r0, r2, #32768
	str	r0, [r1]
	bx	lr
.Ltmp431:
	.size	RTC_TamperPullUpCmd, .Ltmp431-RTC_TamperPullUpCmd

	.globl	RTC_WriteBackupRegister
	.align	2
	.type	RTC_WriteBackupRegister,%function
	.code	16                      @ @RTC_WriteBackupRegister
	.thumb_func
RTC_WriteBackupRegister:
@ BB#0:
	sub	sp, #8
	movs	r2, #0
	str	r2, [sp, #4]
	movw	r2, #10320
	movt	r2, #16384
	str	r2, [sp, #4]
	ldr	r2, [sp, #4]
	add.w	r0, r2, r0, lsl #2
	str	r0, [sp, #4]
	ldr	r0, [sp, #4]
	str	r1, [r0]
	add	sp, #8
	bx	lr
.Ltmp432:
	.size	RTC_WriteBackupRegister, .Ltmp432-RTC_WriteBackupRegister

	.globl	RTC_ReadBackupRegister
	.align	2
	.type	RTC_ReadBackupRegister,%function
	.code	16                      @ @RTC_ReadBackupRegister
	.thumb_func
RTC_ReadBackupRegister:
@ BB#0:
	sub	sp, #8
	movs	r1, #0
	str	r1, [sp, #4]
	movw	r1, #10320
	movt	r1, #16384
	str	r1, [sp, #4]
	ldr	r1, [sp, #4]
	add.w	r0, r1, r0, lsl #2
	str	r0, [sp, #4]
	ldr	r0, [sp, #4]
	ldr	r0, [r0]
	add	sp, #8
	bx	lr
.Ltmp433:
	.size	RTC_ReadBackupRegister, .Ltmp433-RTC_ReadBackupRegister

	.globl	RTC_TamperPinSelection
	.align	2
	.type	RTC_TamperPinSelection,%function
	.code	16                      @ @RTC_TamperPinSelection
	.thumb_func
RTC_TamperPinSelection:
@ BB#0:
	movw	r1, #10304
	movt	r1, #16384
	ldr	r2, [r1]
	bic	r2, r2, #65536
	str	r2, [r1]
	ldr	r2, [r1]
	orrs	r0, r2
	str	r0, [r1]
	bx	lr
.Ltmp434:
	.size	RTC_TamperPinSelection, .Ltmp434-RTC_TamperPinSelection

	.globl	RTC_TimeStampPinSelection
	.align	2
	.type	RTC_TimeStampPinSelection,%function
	.code	16                      @ @RTC_TimeStampPinSelection
	.thumb_func
RTC_TimeStampPinSelection:
@ BB#0:
	movw	r1, #10304
	movt	r1, #16384
	ldr	r2, [r1]
	bic	r2, r2, #131072
	str	r2, [r1]
	ldr	r2, [r1]
	orrs	r0, r2
	str	r0, [r1]
	bx	lr
.Ltmp435:
	.size	RTC_TimeStampPinSelection, .Ltmp435-RTC_TimeStampPinSelection

	.globl	RTC_OutputTypeConfig
	.align	2
	.type	RTC_OutputTypeConfig,%function
	.code	16                      @ @RTC_OutputTypeConfig
	.thumb_func
RTC_OutputTypeConfig:
@ BB#0:
	movw	r1, #10304
	movt	r1, #16384
	ldr	r2, [r1]
	bic	r2, r2, #262144
	str	r2, [r1]
	ldr	r2, [r1]
	orrs	r0, r2
	str	r0, [r1]
	bx	lr
.Ltmp436:
	.size	RTC_OutputTypeConfig, .Ltmp436-RTC_OutputTypeConfig

	.globl	RTC_SynchroShiftConfig
	.align	2
	.type	RTC_SynchroShiftConfig,%function
	.code	16                      @ @RTC_SynchroShiftConfig
	.thumb_func
RTC_SynchroShiftConfig:
@ BB#0:
	push.w	{r11, lr}
	sub	sp, #8
	movw	r12, #10276
	movs	r2, #202
	movw	lr, #10252
	movt	r12, #16384
	movt	lr, #16384
	str.w	r2, [r12]
	movs	r2, #83
	str.w	r2, [r12]
	ldr.w	r2, [lr]
	tst.w	r2, #8
	beq	.LBB437_4
@ BB#1:
	mov.w	r2, #4096
.LBB437_2:                              @ %.preheader
                                        @ =>This Inner Loop Header: Depth=1
	ldr.w	r3, [lr]
	tst.w	r3, #8
	beq	.LBB437_4
@ BB#3:                                 @ %.preheader
                                        @   in Loop: Header=BB437_2 Depth=1
	subs	r3, r2, #1
	cmp	r2, #0
	mov	r2, r3
	bne	.LBB437_2
.LBB437_4:                              @ %.critedge
	ldr.w	r2, [lr]
	tst.w	r2, #8
	beq	.LBB437_6
@ BB#5:
	movs	r2, #0
	b	.LBB437_11
.LBB437_6:
	movw	r2, #10248
	movt	r2, #16384
	ldr	r3, [r2]
	movs	r2, #0
	tst.w	r3, #16
	bne	.LBB437_11
@ BB#7:
	orrs	r0, r1
	movw	r1, #10284
	movt	r1, #16384
	str	r0, [r1]
	movs	r0, #202
	str	r2, [sp, #4]
	str.w	r0, [r12]
	movs	r0, #83
	str.w	r0, [r12]
	ldr.w	r0, [lr]
	bic	r0, r0, #160
	str.w	r0, [lr]
.LBB437_8:                              @ =>This Inner Loop Header: Depth=1
	ldr.w	r0, [lr]
	ldr	r1, [sp, #4]
	adds	r1, #1
	str	r1, [sp, #4]
	ldr	r1, [sp, #4]
	cmp.w	r1, #131072
	beq	.LBB437_10
@ BB#9:                                 @   in Loop: Header=BB437_8 Depth=1
	ands	r0, r0, #32
	beq	.LBB437_8
.LBB437_10:                             @ %RTC_WaitForSynchro.exit
	ldr.w	r0, [lr]
	movs	r1, #255
	str.w	r1, [r12]
	ubfx	r2, r0, #5, #1
.LBB437_11:
	movs	r0, #255
	str.w	r0, [r12]
	mov	r0, r2
	add	sp, #8
	pop.w	{r11, pc}
.Ltmp437:
	.size	RTC_SynchroShiftConfig, .Ltmp437-RTC_SynchroShiftConfig

	.globl	RTC_ITConfig
	.align	2
	.type	RTC_ITConfig,%function
	.code	16                      @ @RTC_ITConfig
	.thumb_func
RTC_ITConfig:
@ BB#0:
	movw	r12, #10276
	movs	r3, #202
	cmp	r1, #0
	movt	r12, #16384
	str.w	r3, [r12]
	mov.w	r3, #83
	str.w	r3, [r12]
	beq	.LBB438_2
@ BB#1:
	movw	r3, #10248
	bic	r1, r0, #4
	and	r0, r0, #4
	movt	r3, #16384
	ldr	r2, [r3]
	orrs	r1, r2
	str	r1, [r3]
	movw	r1, #10304
	movt	r1, #16384
	ldr	r2, [r1]
	orrs	r0, r2
	b	.LBB438_3
.LBB438_2:
	orr	r1, r0, #4
	mvn	r2, #4
	orn	r0, r0, #4
	eors	r1, r2
	movw	r2, #10248
	eor	r0, r0, #4
	movt	r2, #16384
	ldr	r3, [r2]
	ands	r1, r3
	str	r1, [r2]
	movw	r1, #10304
	movt	r1, #16384
	ldr	r2, [r1]
	ands	r0, r2
.LBB438_3:
	str	r0, [r1]
	movs	r0, #255
	str.w	r0, [r12]
	bx	lr
.Ltmp438:
	.size	RTC_ITConfig, .Ltmp438-RTC_ITConfig

	.globl	RTC_GetFlagStatus
	.align	2
	.type	RTC_GetFlagStatus,%function
	.code	16                      @ @RTC_GetFlagStatus
	.thumb_func
RTC_GetFlagStatus:
@ BB#0:
	movw	r1, #10252
	movt	r1, #16384
	ldr	r1, [r1]
	ands	r0, r1
	movw	r1, #16247
	ands	r0, r1
	it	ne
	movne	r0, #1
	bx	lr
.Ltmp439:
	.size	RTC_GetFlagStatus, .Ltmp439-RTC_GetFlagStatus

	.globl	RTC_ClearFlag
	.align	2
	.type	RTC_ClearFlag,%function
	.code	16                      @ @RTC_ClearFlag
	.thumb_func
RTC_ClearFlag:
@ BB#0:
	movw	r1, #65407
	ands	r0, r1
	movw	r1, #10252
	movt	r1, #16384
	ldr	r2, [r1]
	and	r2, r2, #128
	orrs	r0, r2
	mvn	r2, #128
	eors	r0, r2
	str	r0, [r1]
	bx	lr
.Ltmp440:
	.size	RTC_ClearFlag, .Ltmp440-RTC_ClearFlag

	.globl	RTC_GetITStatus
	.align	2
	.type	RTC_GetITStatus,%function
	.code	16                      @ @RTC_GetITStatus
	.thumb_func
RTC_GetITStatus:
@ BB#0:
	movw	r1, #10304
	movw	r2, #10248
	movt	r1, #16384
	movt	r2, #16384
	ldr	r1, [r1]
	ldr	r2, [r2]
	and.w	r1, r1, r0, lsr #15
	ands	r2, r0
	and	r1, r1, #4
	orrs	r1, r2
	movw	r1, #10252
	movt	r1, #16384
	ldr	r1, [r1]
	beq	.LBB441_2
@ BB#1:
	and.w	r0, r1, r0, lsr #4
	movw	r1, #65535
	tst	r0, r1
	itt	ne
	movne	r0, #1
	bxne	lr
.LBB441_2:
	movs	r0, #0
	bx	lr
.Ltmp441:
	.size	RTC_GetITStatus, .Ltmp441-RTC_GetITStatus

	.globl	RTC_ClearITPendingBit
	.align	2
	.type	RTC_ClearITPendingBit,%function
	.code	16                      @ @RTC_ClearITPendingBit
	.thumb_func
RTC_ClearITPendingBit:
@ BB#0:
	movw	r1, #65407
	and.w	r0, r1, r0, lsr #4
	movw	r1, #10252
	movt	r1, #16384
	ldr	r2, [r1]
	and	r2, r2, #128
	orrs	r0, r2
	mvn	r2, #128
	eors	r0, r2
	str	r0, [r1]
	bx	lr
.Ltmp442:
	.size	RTC_ClearITPendingBit, .Ltmp442-RTC_ClearITPendingBit

	.globl	SDIO_DeInit
	.align	2
	.type	SDIO_DeInit,%function
	.code	16                      @ @SDIO_DeInit
	.thumb_func
SDIO_DeInit:
@ BB#0:
	push	{r7, lr}
	mov.w	r0, #2048
	movs	r1, #1
	mov	r7, sp
	bl	RCC_APB2PeriphResetCmd
	mov.w	r0, #2048
	movs	r1, #0
	bl	RCC_APB2PeriphResetCmd
	pop	{r7, pc}
.Ltmp443:
	.size	SDIO_DeInit, .Ltmp443-SDIO_DeInit

	.globl	SDIO_Init
	.align	2
	.type	SDIO_Init,%function
	.code	16                      @ @SDIO_Init
	.thumb_func
SDIO_Init:
@ BB#0:
	push.w	{r4, r5, r11, lr}
	movw	r12, #11268
	movw	r3, #33024
	adds	r5, r0, #4
	movt	r12, #16385
	movt	r3, #65535
	ldr.w	r2, [r12]
	ldr.w	lr, [r0]
	ands	r2, r3
	ldm	r5, {r1, r3, r4, r5}
	ldrb	r0, [r0, #20]
	orrs	r2, r3
	orrs	r0, r2
	orrs	r0, r1
	orrs	r0, r4
	orr.w	r0, r0, lr
	orrs	r0, r5
	str.w	r0, [r12]
	pop.w	{r4, r5, r11, pc}
.Ltmp444:
	.size	SDIO_Init, .Ltmp444-SDIO_Init

	.globl	SDIO_StructInit
	.align	2
	.type	SDIO_StructInit,%function
	.code	16                      @ @SDIO_StructInit
	.thumb_func
SDIO_StructInit:
@ BB#0:
	movs	r1, #0
	strb	r1, [r0, #20]
	str	r1, [r0]
	str	r1, [r0, #4]
	str	r1, [r0, #8]
	str	r1, [r0, #12]
	str	r1, [r0, #16]
	bx	lr
.Ltmp445:
	.size	SDIO_StructInit, .Ltmp445-SDIO_StructInit

	.globl	SDIO_ClockCmd
	.align	2
	.type	SDIO_ClockCmd,%function
	.code	16                      @ @SDIO_ClockCmd
	.thumb_func
SDIO_ClockCmd:
@ BB#0:
	movw	r1, #32928
	movt	r1, #16933
	str	r0, [r1]
	bx	lr
.Ltmp446:
	.size	SDIO_ClockCmd, .Ltmp446-SDIO_ClockCmd

	.globl	SDIO_SetPowerState
	.align	2
	.type	SDIO_SetPowerState,%function
	.code	16                      @ @SDIO_SetPowerState
	.thumb_func
SDIO_SetPowerState:
@ BB#0:
	movw	r1, #11264
	movt	r1, #16385
	str	r0, [r1]
	bx	lr
.Ltmp447:
	.size	SDIO_SetPowerState, .Ltmp447-SDIO_SetPowerState

	.globl	SDIO_GetPowerState
	.align	2
	.type	SDIO_GetPowerState,%function
	.code	16                      @ @SDIO_GetPowerState
	.thumb_func
SDIO_GetPowerState:
@ BB#0:
	movw	r0, #11264
	movt	r0, #16385
	ldr	r0, [r0]
	and	r0, r0, #3
	bx	lr
.Ltmp448:
	.size	SDIO_GetPowerState, .Ltmp448-SDIO_GetPowerState

	.globl	SDIO_SendCommand
	.align	2
	.type	SDIO_SendCommand,%function
	.code	16                      @ @SDIO_SendCommand
	.thumb_func
SDIO_SendCommand:
@ BB#0:
	push.w	{r11, lr}
	ldr	r1, [r0]
	movw	r2, #11272
	movw	r12, #11276
	movt	r2, #16385
	movt	r12, #16385
	str	r1, [r2]
	ldr.w	r2, [r12]
	ldr	r3, [r0, #4]
	ldr	r1, [r0, #8]
	ldr.w	lr, [r0, #12]
	ldr	r0, [r0, #16]
	bfc	r2, #0, #11
	orrs	r2, r3
	orrs	r1, r2
	orr.w	r1, r1, lr
	orrs	r0, r1
	str.w	r0, [r12]
	pop.w	{r11, pc}
.Ltmp449:
	.size	SDIO_SendCommand, .Ltmp449-SDIO_SendCommand

	.globl	SDIO_CmdStructInit
	.align	2
	.type	SDIO_CmdStructInit,%function
	.code	16                      @ @SDIO_CmdStructInit
	.thumb_func
SDIO_CmdStructInit:
@ BB#0:
	movs	r1, #0
	str	r1, [r0]
	str	r1, [r0, #4]
	str	r1, [r0, #8]
	str	r1, [r0, #12]
	str	r1, [r0, #16]
	bx	lr
.Ltmp450:
	.size	SDIO_CmdStructInit, .Ltmp450-SDIO_CmdStructInit

	.globl	SDIO_GetCommandResponse
	.align	2
	.type	SDIO_GetCommandResponse,%function
	.code	16                      @ @SDIO_GetCommandResponse
	.thumb_func
SDIO_GetCommandResponse:
@ BB#0:
	movw	r0, #11280
	movt	r0, #16385
	ldr	r0, [r0]
	uxtb	r0, r0
	bx	lr
.Ltmp451:
	.size	SDIO_GetCommandResponse, .Ltmp451-SDIO_GetCommandResponse

	.globl	SDIO_GetResponse
	.align	2
	.type	SDIO_GetResponse,%function
	.code	16                      @ @SDIO_GetResponse
	.thumb_func
SDIO_GetResponse:
@ BB#0:
	sub	sp, #8
	movs	r1, #0
	str	r1, [sp, #4]
	movw	r1, #11284
	movt	r1, #16385
	add	r0, r1
	str	r0, [sp, #4]
	ldr	r0, [sp, #4]
	ldr	r0, [r0]
	add	sp, #8
	bx	lr
.Ltmp452:
	.size	SDIO_GetResponse, .Ltmp452-SDIO_GetResponse

	.globl	SDIO_DataConfig
	.align	2
	.type	SDIO_DataConfig,%function
	.code	16                      @ @SDIO_DataConfig
	.thumb_func
SDIO_DataConfig:
@ BB#0:
	push.w	{r11, lr}
	ldr	r1, [r0]
	movw	r2, #11300
	movw	r12, #11308
	movt	r2, #16385
	movt	r12, #16385
	str	r1, [r2]
	movw	r2, #11304
	ldr	r1, [r0, #4]
	movt	r2, #16385
	str	r1, [r2]
	ldr.w	r2, [r12]
	ldr	r3, [r0, #8]
	ldr	r1, [r0, #12]
	ldr.w	lr, [r0, #16]
	ldr	r0, [r0, #20]
	bic	r2, r2, #247
	orrs	r2, r3
	orrs	r1, r2
	orr.w	r1, r1, lr
	orrs	r0, r1
	str.w	r0, [r12]
	pop.w	{r11, pc}
.Ltmp453:
	.size	SDIO_DataConfig, .Ltmp453-SDIO_DataConfig

	.globl	SDIO_DataStructInit
	.align	2
	.type	SDIO_DataStructInit,%function
	.code	16                      @ @SDIO_DataStructInit
	.thumb_func
SDIO_DataStructInit:
@ BB#0:
	mov.w	r1, #-1
	movs	r2, #0
	stm.w	r0, {r1, r2}
	str	r2, [r0, #8]
	str	r2, [r0, #12]
	str	r2, [r0, #16]
	str	r2, [r0, #20]
	bx	lr
.Ltmp454:
	.size	SDIO_DataStructInit, .Ltmp454-SDIO_DataStructInit

	.globl	SDIO_GetDataCounter
	.align	2
	.type	SDIO_GetDataCounter,%function
	.code	16                      @ @SDIO_GetDataCounter
	.thumb_func
SDIO_GetDataCounter:
@ BB#0:
	movw	r0, #11312
	movt	r0, #16385
	ldr	r0, [r0]
	bx	lr
.Ltmp455:
	.size	SDIO_GetDataCounter, .Ltmp455-SDIO_GetDataCounter

	.globl	SDIO_ReadData
	.align	2
	.type	SDIO_ReadData,%function
	.code	16                      @ @SDIO_ReadData
	.thumb_func
SDIO_ReadData:
@ BB#0:
	movw	r0, #11392
	movt	r0, #16385
	ldr	r0, [r0]
	bx	lr
.Ltmp456:
	.size	SDIO_ReadData, .Ltmp456-SDIO_ReadData

	.globl	SDIO_WriteData
	.align	2
	.type	SDIO_WriteData,%function
	.code	16                      @ @SDIO_WriteData
	.thumb_func
SDIO_WriteData:
@ BB#0:
	movw	r1, #11392
	movt	r1, #16385
	str	r0, [r1]
	bx	lr
.Ltmp457:
	.size	SDIO_WriteData, .Ltmp457-SDIO_WriteData

	.globl	SDIO_GetFIFOCount
	.align	2
	.type	SDIO_GetFIFOCount,%function
	.code	16                      @ @SDIO_GetFIFOCount
	.thumb_func
SDIO_GetFIFOCount:
@ BB#0:
	movw	r0, #11336
	movt	r0, #16385
	ldr	r0, [r0]
	bx	lr
.Ltmp458:
	.size	SDIO_GetFIFOCount, .Ltmp458-SDIO_GetFIFOCount

	.globl	SDIO_StartSDIOReadWait
	.align	2
	.type	SDIO_StartSDIOReadWait,%function
	.code	16                      @ @SDIO_StartSDIOReadWait
	.thumb_func
SDIO_StartSDIOReadWait:
@ BB#0:
	movw	r1, #34208
	movt	r1, #16933
	str	r0, [r1]
	bx	lr
.Ltmp459:
	.size	SDIO_StartSDIOReadWait, .Ltmp459-SDIO_StartSDIOReadWait

	.globl	SDIO_StopSDIOReadWait
	.align	2
	.type	SDIO_StopSDIOReadWait,%function
	.code	16                      @ @SDIO_StopSDIOReadWait
	.thumb_func
SDIO_StopSDIOReadWait:
@ BB#0:
	movw	r1, #34212
	movt	r1, #16933
	str	r0, [r1]
	bx	lr
.Ltmp460:
	.size	SDIO_StopSDIOReadWait, .Ltmp460-SDIO_StopSDIOReadWait

	.globl	SDIO_SetSDIOReadWaitMode
	.align	2
	.type	SDIO_SetSDIOReadWaitMode,%function
	.code	16                      @ @SDIO_SetSDIOReadWaitMode
	.thumb_func
SDIO_SetSDIOReadWaitMode:
@ BB#0:
	movw	r1, #34216
	movt	r1, #16933
	str	r0, [r1]
	bx	lr
.Ltmp461:
	.size	SDIO_SetSDIOReadWaitMode, .Ltmp461-SDIO_SetSDIOReadWaitMode

	.globl	SDIO_SetSDIOOperation
	.align	2
	.type	SDIO_SetSDIOOperation,%function
	.code	16                      @ @SDIO_SetSDIOOperation
	.thumb_func
SDIO_SetSDIOOperation:
@ BB#0:
	movw	r1, #34220
	movt	r1, #16933
	str	r0, [r1]
	bx	lr
.Ltmp462:
	.size	SDIO_SetSDIOOperation, .Ltmp462-SDIO_SetSDIOOperation

	.globl	SDIO_SendSDIOSuspendCmd
	.align	2
	.type	SDIO_SendSDIOSuspendCmd,%function
	.code	16                      @ @SDIO_SendSDIOSuspendCmd
	.thumb_func
SDIO_SendSDIOSuspendCmd:
@ BB#0:
	movw	r1, #33196
	movt	r1, #16933
	str	r0, [r1]
	bx	lr
.Ltmp463:
	.size	SDIO_SendSDIOSuspendCmd, .Ltmp463-SDIO_SendSDIOSuspendCmd

	.globl	SDIO_CommandCompletionCmd
	.align	2
	.type	SDIO_CommandCompletionCmd,%function
	.code	16                      @ @SDIO_CommandCompletionCmd
	.thumb_func
SDIO_CommandCompletionCmd:
@ BB#0:
	movw	r1, #33200
	movt	r1, #16933
	str	r0, [r1]
	bx	lr
.Ltmp464:
	.size	SDIO_CommandCompletionCmd, .Ltmp464-SDIO_CommandCompletionCmd

	.globl	SDIO_CEATAITCmd
	.align	2
	.type	SDIO_CEATAITCmd,%function
	.code	16                      @ @SDIO_CEATAITCmd
	.thumb_func
SDIO_CEATAITCmd:
@ BB#0:
	movs	r1, #1
	bic.w	r0, r1, r0
	movw	r1, #33204
	movt	r1, #16933
	str	r0, [r1]
	bx	lr
.Ltmp465:
	.size	SDIO_CEATAITCmd, .Ltmp465-SDIO_CEATAITCmd

	.globl	SDIO_SendCEATACmd
	.align	2
	.type	SDIO_SendCEATACmd,%function
	.code	16                      @ @SDIO_SendCEATACmd
	.thumb_func
SDIO_SendCEATACmd:
@ BB#0:
	movw	r1, #33208
	movt	r1, #16933
	str	r0, [r1]
	bx	lr
.Ltmp466:
	.size	SDIO_SendCEATACmd, .Ltmp466-SDIO_SendCEATACmd

	.globl	SDIO_DMACmd
	.align	2
	.type	SDIO_DMACmd,%function
	.code	16                      @ @SDIO_DMACmd
	.thumb_func
SDIO_DMACmd:
@ BB#0:
	movw	r1, #34188
	movt	r1, #16933
	str	r0, [r1]
	bx	lr
.Ltmp467:
	.size	SDIO_DMACmd, .Ltmp467-SDIO_DMACmd

	.globl	SDIO_ITConfig
	.align	2
	.type	SDIO_ITConfig,%function
	.code	16                      @ @SDIO_ITConfig
	.thumb_func
SDIO_ITConfig:
@ BB#0:
	cmp	r1, #0
	movw	r1, #11324
	movt	r1, #16385
	ldr	r2, [r1]
	ite	eq
	biceq.w	r0, r2, r0
	orrne	r0, r2
	str	r0, [r1]
	bx	lr
.Ltmp468:
	.size	SDIO_ITConfig, .Ltmp468-SDIO_ITConfig

	.globl	SDIO_GetFlagStatus
	.align	2
	.type	SDIO_GetFlagStatus,%function
	.code	16                      @ @SDIO_GetFlagStatus
	.thumb_func
SDIO_GetFlagStatus:
@ BB#0:
	movw	r1, #11316
	movt	r1, #16385
	ldr	r1, [r1]
	ands	r0, r1
	it	ne
	movne	r0, #1
	bx	lr
.Ltmp469:
	.size	SDIO_GetFlagStatus, .Ltmp469-SDIO_GetFlagStatus

	.globl	SDIO_ClearFlag
	.align	2
	.type	SDIO_ClearFlag,%function
	.code	16                      @ @SDIO_ClearFlag
	.thumb_func
SDIO_ClearFlag:
@ BB#0:
	movw	r1, #11320
	movt	r1, #16385
	str	r0, [r1]
	bx	lr
.Ltmp470:
	.size	SDIO_ClearFlag, .Ltmp470-SDIO_ClearFlag

	.globl	SDIO_GetITStatus
	.align	2
	.type	SDIO_GetITStatus,%function
	.code	16                      @ @SDIO_GetITStatus
	.thumb_func
SDIO_GetITStatus:
@ BB#0:
	movw	r1, #11316
	movt	r1, #16385
	ldr	r1, [r1]
	ands	r0, r1
	it	ne
	movne	r0, #1
	bx	lr
.Ltmp471:
	.size	SDIO_GetITStatus, .Ltmp471-SDIO_GetITStatus

	.globl	SDIO_ClearITPendingBit
	.align	2
	.type	SDIO_ClearITPendingBit,%function
	.code	16                      @ @SDIO_ClearITPendingBit
	.thumb_func
SDIO_ClearITPendingBit:
@ BB#0:
	movw	r1, #11320
	movt	r1, #16385
	str	r0, [r1]
	bx	lr
.Ltmp472:
	.size	SDIO_ClearITPendingBit, .Ltmp472-SDIO_ClearITPendingBit

	.globl	SPI_I2S_DeInit
	.align	2
	.type	SPI_I2S_DeInit,%function
	.code	16                      @ @SPI_I2S_DeInit
	.thumb_func
SPI_I2S_DeInit:
@ BB#0:
	push	{r7, lr}
	movw	r1, #14336
	mov	r7, sp
	movt	r1, #16384
	cmp	r0, r1
	beq	.LBB473_3
@ BB#1:
	movw	r1, #15360
	movt	r1, #16384
	cmp	r0, r1
	bne	.LBB473_5
@ BB#2:
	mov.w	r0, #32768
	movs	r1, #1
	bl	RCC_APB1PeriphResetCmd
	mov.w	r0, #32768
	b	.LBB473_4
.LBB473_3:
	mov.w	r0, #16384
	movs	r1, #1
	bl	RCC_APB1PeriphResetCmd
	mov.w	r0, #16384
.LBB473_4:
	movs	r1, #0
	bl	RCC_APB1PeriphResetCmd
	pop	{r7, pc}
.LBB473_5:
	movw	r1, #12288
	movt	r1, #16385
	cmp	r0, r1
	it	ne
	popne	{r7, pc}
	mov.w	r0, #4096
	movs	r1, #1
	bl	RCC_APB2PeriphResetCmd
	mov.w	r0, #4096
	movs	r1, #0
	bl	RCC_APB2PeriphResetCmd
	pop	{r7, pc}
.Ltmp473:
	.size	SPI_I2S_DeInit, .Ltmp473-SPI_I2S_DeInit

	.globl	SPI_Init
	.align	2
	.type	SPI_Init,%function
	.code	16                      @ @SPI_Init
	.thumb_func
SPI_Init:
@ BB#0:
	ldrh.w	r12, [r0]
	ldrh	r3, [r1]
	ldrh	r2, [r1, #2]
	orrs	r2, r3
	ldrh	r3, [r1, #4]
	orrs	r2, r3
	ldrh	r3, [r1, #6]
	orrs	r2, r3
	ldrh	r3, [r1, #8]
	orrs	r2, r3
	ldrh	r3, [r1, #10]
	orrs	r2, r3
	ldrh	r3, [r1, #12]
	orrs	r2, r3
	ldrh	r3, [r1, #14]
	orrs	r2, r3
	and	r3, r12, #12352
	orrs	r2, r3
	strh	r2, [r0]
	ldrh	r2, [r0, #28]
	bic	r2, r2, #2048
	strh	r2, [r0, #28]
	ldrh	r1, [r1, #16]
	strh	r1, [r0, #16]
	bx	lr
.Ltmp474:
	.size	SPI_Init, .Ltmp474-SPI_Init

	.globl	I2S_Init
	.align	2
	.type	I2S_Init,%function
	.code	16                      @ @I2S_Init
	.thumb_func
I2S_Init:
@ BB#0:
	push.w	{r4, r5, r11, lr}
	ldrh	r2, [r0, #28]
	movw	r3, #61504
	ands	r2, r3
	strh	r2, [r0, #28]
	movs	r2, #2
	strh	r2, [r0, #32]
	ldrh.w	lr, [r0, #28]
	ldr	r2, [r1, #8]
	cmp	r2, #2
	bne	.LBB475_2
@ BB#1:                                 @ %._crit_edge
	ldrh	r3, [r1, #6]
	mov.w	r12, #0
	movs	r2, #2
	b	.LBB475_6
.LBB475_2:
	movw	r2, #14344
	ldrh.w	r12, [r1, #4]
	movw	r4, #14340
	movw	r5, #4608
	movt	r2, #16386
	movt	r4, #16386
	movt	r5, #122
	ldr	r3, [r2]
	tst.w	r3, #8388608
	ittt	ne
	ldrne	r3, [r2]
	bicne	r3, r3, #8388608
	strne	r3, [r2]
	movw	r2, #14468
	movt	r2, #16386
	ldr	r3, [r2]
	ldr	r2, [r2]
	ldr	r4, [r4]
	and	r4, r4, #63
	ubfx	r3, r3, #6, #9
	ubfx	r2, r2, #28, #3
	udiv	r4, r5, r4
	muls	r3, r4, r3
	udiv	r2, r3, r2
	ldrh	r3, [r1, #6]
	cmp.w	r3, #512
	bne	.LBB475_4
@ BB#3:
	ldr	r5, [r1, #8]
	lsrs	r2, r2, #8
	add.w	r2, r2, r2, lsl #2
	lsls	r2, r2, #1
	b	.LBB475_5
.LBB475_4:
	movs	r4, #6
	cmp.w	r12, #0
	it	eq
	moveq	r4, #5
	ldr	r5, [r1, #8]
	lsrs	r2, r4
	add.w	r2, r2, r2, lsl #2
	lsls	r2, r2, #1
.LBB475_5:
	udiv	r2, r2, r5
	movw	r5, #52429
	add.w	r2, r2, #5
	movt	r5, #52428
	uxth	r2, r2
	umull	r2, r5, r2, r5
	ubfx	r4, r5, #3, #1
	rsb	r2, r4, r5, lsr #3
	lsl.w	r12, r4, #8
	lsr.w	r2, r2, #1
.LBB475_6:
	subs	r4, r2, #2
	uxth	r4, r4
	cmp	r4, #253
	ite	ls
	orrls.w	r3, r3, r12
	movhi	r2, #2
	orrs	r2, r3
	strh	r2, [r0, #32]
	ldrh	r2, [r1]
	ldrh	r3, [r1, #2]
	orrs	r2, r3
	ldrh	r3, [r1, #4]
	ldrh	r1, [r1, #12]
	orrs	r2, r3
	orrs	r1, r2
	orr.w	r1, r1, lr
	orr	r1, r1, #2048
	strh	r1, [r0, #28]
	pop.w	{r4, r5, r11, pc}
.Ltmp475:
	.size	I2S_Init, .Ltmp475-I2S_Init

	.globl	SPI_StructInit
	.align	2
	.type	SPI_StructInit,%function
	.code	16                      @ @SPI_StructInit
	.thumb_func
SPI_StructInit:
@ BB#0:
	movs	r1, #0
	strh	r1, [r0, #2]
	strh	r1, [r0]
	strh	r1, [r0, #6]
	strh	r1, [r0, #4]
	strh	r1, [r0, #10]
	strh	r1, [r0, #8]
	strh	r1, [r0, #14]
	strh	r1, [r0, #12]
	movs	r1, #7
	strh	r1, [r0, #16]
	bx	lr
.Ltmp476:
	.size	SPI_StructInit, .Ltmp476-SPI_StructInit

	.globl	I2S_StructInit
	.align	2
	.type	I2S_StructInit,%function
	.code	16                      @ @I2S_StructInit
	.thumb_func
I2S_StructInit:
@ BB#0:
	movs	r1, #0
	movs	r2, #2
	strh	r1, [r0]
	strh	r1, [r0, #2]
	strh	r1, [r0, #4]
	strh	r1, [r0, #6]
	str	r2, [r0, #8]
	strh	r1, [r0, #12]
	bx	lr
.Ltmp477:
	.size	I2S_StructInit, .Ltmp477-I2S_StructInit

	.globl	SPI_Cmd
	.align	2
	.type	SPI_Cmd,%function
	.code	16                      @ @SPI_Cmd
	.thumb_func
SPI_Cmd:
@ BB#0:
	ldrh	r2, [r0]
	cmp	r1, #0
	ite	eq
	biceq	r1, r2, #64
	orrne	r1, r2, #64
	strh	r1, [r0]
	bx	lr
.Ltmp478:
	.size	SPI_Cmd, .Ltmp478-SPI_Cmd

	.globl	I2S_Cmd
	.align	2
	.type	I2S_Cmd,%function
	.code	16                      @ @I2S_Cmd
	.thumb_func
I2S_Cmd:
@ BB#0:
	ldrh	r2, [r0, #28]
	cmp	r1, #0
	ite	eq
	biceq	r1, r2, #1024
	orrne	r1, r2, #1024
	strh	r1, [r0, #28]
	bx	lr
.Ltmp479:
	.size	I2S_Cmd, .Ltmp479-I2S_Cmd

	.globl	SPI_DataSizeConfig
	.align	2
	.type	SPI_DataSizeConfig,%function
	.code	16                      @ @SPI_DataSizeConfig
	.thumb_func
SPI_DataSizeConfig:
@ BB#0:
	ldrh	r2, [r0]
	bic	r2, r2, #2048
	strh	r2, [r0]
	ldrh	r2, [r0]
	orrs	r1, r2
	strh	r1, [r0]
	bx	lr
.Ltmp480:
	.size	SPI_DataSizeConfig, .Ltmp480-SPI_DataSizeConfig

	.globl	SPI_BiDirectionalLineConfig
	.align	2
	.type	SPI_BiDirectionalLineConfig,%function
	.code	16                      @ @SPI_BiDirectionalLineConfig
	.thumb_func
SPI_BiDirectionalLineConfig:
@ BB#0:
	ldrh	r2, [r0]
	cmp.w	r1, #16384
	ite	ne
	bicne	r1, r2, #16384
	orreq	r1, r2, #16384
	strh	r1, [r0]
	bx	lr
.Ltmp481:
	.size	SPI_BiDirectionalLineConfig, .Ltmp481-SPI_BiDirectionalLineConfig

	.globl	SPI_NSSInternalSoftwareConfig
	.align	2
	.type	SPI_NSSInternalSoftwareConfig,%function
	.code	16                      @ @SPI_NSSInternalSoftwareConfig
	.thumb_func
SPI_NSSInternalSoftwareConfig:
@ BB#0:
	ldrh	r2, [r0]
	movw	r3, #65279
	cmp	r1, r3
	ite	eq
	biceq	r1, r2, #256
	orrne	r1, r2, #256
	strh	r1, [r0]
	bx	lr
.Ltmp482:
	.size	SPI_NSSInternalSoftwareConfig, .Ltmp482-SPI_NSSInternalSoftwareConfig

	.globl	SPI_SSOutputCmd
	.align	2
	.type	SPI_SSOutputCmd,%function
	.code	16                      @ @SPI_SSOutputCmd
	.thumb_func
SPI_SSOutputCmd:
@ BB#0:
	ldrh	r2, [r0, #4]
	cmp	r1, #0
	ite	eq
	biceq	r1, r2, #4
	orrne	r1, r2, #4
	strh	r1, [r0, #4]
	bx	lr
.Ltmp483:
	.size	SPI_SSOutputCmd, .Ltmp483-SPI_SSOutputCmd

	.globl	SPI_TIModeCmd
	.align	2
	.type	SPI_TIModeCmd,%function
	.code	16                      @ @SPI_TIModeCmd
	.thumb_func
SPI_TIModeCmd:
@ BB#0:
	ldrh	r2, [r0, #4]
	cmp	r1, #0
	ite	eq
	biceq	r1, r2, #16
	orrne	r1, r2, #16
	strh	r1, [r0, #4]
	bx	lr
.Ltmp484:
	.size	SPI_TIModeCmd, .Ltmp484-SPI_TIModeCmd

	.globl	I2S_FullDuplexConfig
	.align	2
	.type	I2S_FullDuplexConfig,%function
	.code	16                      @ @I2S_FullDuplexConfig
	.thumb_func
I2S_FullDuplexConfig:
@ BB#0:
	ldrh	r2, [r0, #28]
	movw	r3, #61504
	ands	r2, r3
	mov.w	r3, #256
	strh	r2, [r0, #28]
	movs	r2, #2
	strh	r2, [r0, #32]
	ldrh.w	r12, [r0, #28]
	ldrh	r2, [r1]
	cmp	r2, #0
	it	ne
	cmpne.w	r2, #512
	beq	.LBB485_2
@ BB#1:
	cmp.w	r2, #768
	mov.w	r3, #0
	it	ne
	cmpne.w	r2, #256
.LBB485_2:
	orr.w	r12, r12, r3
	ldrh	r3, [r1, #2]
	ldrh	r2, [r1, #4]
	ldrh	r1, [r1, #12]
	orrs	r2, r3
	orrs	r1, r2
	orr.w	r1, r1, r12
	orr	r1, r1, #2048
	strh	r1, [r0, #28]
	bx	lr
.Ltmp485:
	.size	I2S_FullDuplexConfig, .Ltmp485-I2S_FullDuplexConfig

	.globl	SPI_I2S_ReceiveData
	.align	2
	.type	SPI_I2S_ReceiveData,%function
	.code	16                      @ @SPI_I2S_ReceiveData
	.thumb_func
SPI_I2S_ReceiveData:
@ BB#0:
	ldrh	r0, [r0, #12]
	bx	lr
.Ltmp486:
	.size	SPI_I2S_ReceiveData, .Ltmp486-SPI_I2S_ReceiveData

	.globl	SPI_I2S_SendData
	.align	2
	.type	SPI_I2S_SendData,%function
	.code	16                      @ @SPI_I2S_SendData
	.thumb_func
SPI_I2S_SendData:
@ BB#0:
	strh	r1, [r0, #12]
	bx	lr
.Ltmp487:
	.size	SPI_I2S_SendData, .Ltmp487-SPI_I2S_SendData

	.globl	SPI_CalculateCRC
	.align	2
	.type	SPI_CalculateCRC,%function
	.code	16                      @ @SPI_CalculateCRC
	.thumb_func
SPI_CalculateCRC:
@ BB#0:
	ldrh	r2, [r0]
	cmp	r1, #0
	ite	eq
	biceq	r1, r2, #8192
	orrne	r1, r2, #8192
	strh	r1, [r0]
	bx	lr
.Ltmp488:
	.size	SPI_CalculateCRC, .Ltmp488-SPI_CalculateCRC

	.globl	SPI_TransmitCRC
	.align	2
	.type	SPI_TransmitCRC,%function
	.code	16                      @ @SPI_TransmitCRC
	.thumb_func
SPI_TransmitCRC:
@ BB#0:
	ldrh	r1, [r0]
	orr	r1, r1, #4096
	strh	r1, [r0]
	bx	lr
.Ltmp489:
	.size	SPI_TransmitCRC, .Ltmp489-SPI_TransmitCRC

	.globl	SPI_GetCRC
	.align	2
	.type	SPI_GetCRC,%function
	.code	16                      @ @SPI_GetCRC
	.thumb_func
SPI_GetCRC:
@ BB#0:
	add.w	r2, r0, #24
	cmp	r1, #1
	it	eq
	addeq.w	r2, r0, #20
	ldrh	r0, [r2]
	bx	lr
.Ltmp490:
	.size	SPI_GetCRC, .Ltmp490-SPI_GetCRC

	.globl	SPI_GetCRCPolynomial
	.align	2
	.type	SPI_GetCRCPolynomial,%function
	.code	16                      @ @SPI_GetCRCPolynomial
	.thumb_func
SPI_GetCRCPolynomial:
@ BB#0:
	ldrh	r0, [r0, #16]
	bx	lr
.Ltmp491:
	.size	SPI_GetCRCPolynomial, .Ltmp491-SPI_GetCRCPolynomial

	.globl	SPI_I2S_DMACmd
	.align	2
	.type	SPI_I2S_DMACmd,%function
	.code	16                      @ @SPI_I2S_DMACmd
	.thumb_func
SPI_I2S_DMACmd:
@ BB#0:
	cmp	r2, #0
	ldrh	r2, [r0, #4]
	ite	eq
	biceq.w	r1, r2, r1
	orrne	r1, r2
	strh	r1, [r0, #4]
	bx	lr
.Ltmp492:
	.size	SPI_I2S_DMACmd, .Ltmp492-SPI_I2S_DMACmd

	.globl	SPI_I2S_ITConfig
	.align	2
	.type	SPI_I2S_ITConfig,%function
	.code	16                      @ @SPI_I2S_ITConfig
	.thumb_func
SPI_I2S_ITConfig:
@ BB#0:
	cmp	r2, #0
	ldrh	r2, [r0, #4]
	lsr.w	r1, r1, #4
	mov.w	r3, #1
	lsl.w	r1, r3, r1
	ite	eq
	biceq.w	r1, r2, r1
	orrne	r1, r2
	strh	r1, [r0, #4]
	bx	lr
.Ltmp493:
	.size	SPI_I2S_ITConfig, .Ltmp493-SPI_I2S_ITConfig

	.globl	SPI_I2S_GetFlagStatus
	.align	2
	.type	SPI_I2S_GetFlagStatus,%function
	.code	16                      @ @SPI_I2S_GetFlagStatus
	.thumb_func
SPI_I2S_GetFlagStatus:
@ BB#0:
	ldrh	r0, [r0, #8]
	ands	r0, r1
	it	ne
	movne	r0, #1
	bx	lr
.Ltmp494:
	.size	SPI_I2S_GetFlagStatus, .Ltmp494-SPI_I2S_GetFlagStatus

	.globl	SPI_I2S_ClearFlag
	.align	2
	.type	SPI_I2S_ClearFlag,%function
	.code	16                      @ @SPI_I2S_ClearFlag
	.thumb_func
SPI_I2S_ClearFlag:
@ BB#0:
	mvns	r1, r1
	strh	r1, [r0, #8]
	bx	lr
.Ltmp495:
	.size	SPI_I2S_ClearFlag, .Ltmp495-SPI_I2S_ClearFlag

	.globl	SPI_I2S_GetITStatus
	.align	2
	.type	SPI_I2S_GetITStatus,%function
	.code	16                      @ @SPI_I2S_GetITStatus
	.thumb_func
SPI_I2S_GetITStatus:
@ BB#0:
	mov	r2, r0
	and	r3, r1, #15
	movs	r0, #1
	ldrh.w	r12, [r2, #4]
	ldrh	r2, [r2, #8]
	lsl.w	r3, r0, r3
	tst	r3, r2
	beq	.LBB496_2
@ BB#1:
	lsrs	r1, r1, #4
	lsl.w	r1, r0, r1
	tst.w	r12, r1
	it	eq
	moveq	r0, #0
	b	.LBB496_3
.LBB496_2:
	movs	r0, #0
.LBB496_3:
	bx	lr
.Ltmp496:
	.size	SPI_I2S_GetITStatus, .Ltmp496-SPI_I2S_GetITStatus

	.globl	SPI_I2S_ClearITPendingBit
	.align	2
	.type	SPI_I2S_ClearITPendingBit,%function
	.code	16                      @ @SPI_I2S_ClearITPendingBit
	.thumb_func
SPI_I2S_ClearITPendingBit:
@ BB#0:
	and	r1, r1, #15
	movs	r2, #1
	lsl.w	r1, r2, r1
	mvns	r1, r1
	strh	r1, [r0, #8]
	bx	lr
.Ltmp497:
	.size	SPI_I2S_ClearITPendingBit, .Ltmp497-SPI_I2S_ClearITPendingBit

	.globl	SYSCFG_DeInit
	.align	2
	.type	SYSCFG_DeInit,%function
	.code	16                      @ @SYSCFG_DeInit
	.thumb_func
SYSCFG_DeInit:
@ BB#0:
	push	{r7, lr}
	mov.w	r0, #16384
	movs	r1, #1
	mov	r7, sp
	bl	RCC_APB2PeriphResetCmd
	mov.w	r0, #16384
	movs	r1, #0
	bl	RCC_APB2PeriphResetCmd
	pop	{r7, pc}
.Ltmp498:
	.size	SYSCFG_DeInit, .Ltmp498-SYSCFG_DeInit

	.globl	SYSCFG_MemoryRemapConfig
	.align	2
	.type	SYSCFG_MemoryRemapConfig,%function
	.code	16                      @ @SYSCFG_MemoryRemapConfig
	.thumb_func
SYSCFG_MemoryRemapConfig:
@ BB#0:
	movw	r1, #14336
	movt	r1, #16385
	str	r0, [r1]
	bx	lr
.Ltmp499:
	.size	SYSCFG_MemoryRemapConfig, .Ltmp499-SYSCFG_MemoryRemapConfig

	.globl	SYSCFG_EXTILineConfig
	.align	2
	.type	SYSCFG_EXTILineConfig,%function
	.code	16                      @ @SYSCFG_EXTILineConfig
	.thumb_func
SYSCFG_EXTILineConfig:
@ BB#0:
	push.w	{r11, lr}
	movs	r2, #12
	movw	lr, #14344
	movs	r3, #15
	and.w	r2, r2, r1, lsl #2
	and	r1, r1, #252
	movt	lr, #16385
	lsl.w	r12, r3, r2
	ldr.w	r3, [r1, lr]
	lsls	r0, r2
	bic.w	r3, r3, r12
	str.w	r3, [r1, lr]
	ldr.w	r2, [r1, lr]
	orrs	r0, r2
	str.w	r0, [r1, lr]
	pop.w	{r11, pc}
.Ltmp500:
	.size	SYSCFG_EXTILineConfig, .Ltmp500-SYSCFG_EXTILineConfig

	.globl	SYSCFG_ETH_MediaInterfaceConfig
	.align	2
	.type	SYSCFG_ETH_MediaInterfaceConfig,%function
	.code	16                      @ @SYSCFG_ETH_MediaInterfaceConfig
	.thumb_func
SYSCFG_ETH_MediaInterfaceConfig:
@ BB#0:
	movs	r1, #220
	movt	r1, #16935
	str	r0, [r1]
	bx	lr
.Ltmp501:
	.size	SYSCFG_ETH_MediaInterfaceConfig, .Ltmp501-SYSCFG_ETH_MediaInterfaceConfig

	.globl	SYSCFG_CompensationCellCmd
	.align	2
	.type	SYSCFG_CompensationCellCmd,%function
	.code	16                      @ @SYSCFG_CompensationCellCmd
	.thumb_func
SYSCFG_CompensationCellCmd:
@ BB#0:
	movw	r1, #1024
	movt	r1, #16935
	str	r0, [r1]
	bx	lr
.Ltmp502:
	.size	SYSCFG_CompensationCellCmd, .Ltmp502-SYSCFG_CompensationCellCmd

	.globl	SYSCFG_GetCompensationCellStatus
	.align	2
	.type	SYSCFG_GetCompensationCellStatus,%function
	.code	16                      @ @SYSCFG_GetCompensationCellStatus
	.thumb_func
SYSCFG_GetCompensationCellStatus:
@ BB#0:
	movw	r0, #14368
	movt	r0, #16385
	ldr	r0, [r0]
	ubfx	r0, r0, #8, #1
	bx	lr
.Ltmp503:
	.size	SYSCFG_GetCompensationCellStatus, .Ltmp503-SYSCFG_GetCompensationCellStatus

	.globl	TIM_DeInit
	.align	2
	.type	TIM_DeInit,%function
	.code	16                      @ @TIM_DeInit
	.thumb_func
TIM_DeInit:
@ BB#0:
	push	{r7, lr}
	movw	r1, #1023
	mov	r7, sp
	movt	r1, #16384
	cmp	r0, r1
	bgt	.LBB504_3
@ BB#1:
	cmp.w	r0, #1073741824
	bne.w	.LBB504_28
@ BB#2:
	movs	r0, #1
	movs	r1, #1
	bl	RCC_APB1PeriphResetCmd
	movs	r0, #1
	b	.LBB504_27
.LBB504_3:
	movw	r1, #2047
	movt	r1, #16384
	cmp	r0, r1
	bgt	.LBB504_6
@ BB#4:
	movw	r1, #1024
	movt	r1, #16384
	cmp	r0, r1
	bne.w	.LBB504_28
@ BB#5:
	movs	r0, #2
	movs	r1, #1
	bl	RCC_APB1PeriphResetCmd
	movs	r0, #2
	b	.LBB504_27
.LBB504_6:
	movw	r1, #3071
	movt	r1, #16384
	cmp	r0, r1
	bgt	.LBB504_9
@ BB#7:
	movw	r1, #2048
	movt	r1, #16384
	cmp	r0, r1
	bne.w	.LBB504_28
@ BB#8:
	movs	r0, #4
	movs	r1, #1
	bl	RCC_APB1PeriphResetCmd
	movs	r0, #4
	b	.LBB504_27
.LBB504_9:
	movw	r1, #4095
	movt	r1, #16384
	cmp	r0, r1
	bgt	.LBB504_12
@ BB#10:
	movw	r1, #3072
	movt	r1, #16384
	cmp	r0, r1
	bne	.LBB504_28
@ BB#11:
	movs	r0, #8
	movs	r1, #1
	bl	RCC_APB1PeriphResetCmd
	movs	r0, #8
	b	.LBB504_27
.LBB504_12:
	movw	r1, #5119
	movt	r1, #16384
	cmp	r0, r1
	bgt	.LBB504_15
@ BB#13:
	movw	r1, #4096
	movt	r1, #16384
	cmp	r0, r1
	bne	.LBB504_28
@ BB#14:
	movs	r0, #16
	movs	r1, #1
	bl	RCC_APB1PeriphResetCmd
	movs	r0, #16
	b	.LBB504_27
.LBB504_15:
	movw	r1, #6143
	movt	r1, #16384
	cmp	r0, r1
	bgt	.LBB504_18
@ BB#16:
	movw	r1, #5120
	movt	r1, #16384
	cmp	r0, r1
	bne	.LBB504_28
@ BB#17:
	movs	r0, #32
	movs	r1, #1
	bl	RCC_APB1PeriphResetCmd
	movs	r0, #32
	b	.LBB504_27
.LBB504_18:
	movw	r1, #7167
	movt	r1, #16384
	cmp	r0, r1
	bgt	.LBB504_21
@ BB#19:
	movw	r1, #6144
	movt	r1, #16384
	cmp	r0, r1
	bne	.LBB504_28
@ BB#20:
	movs	r0, #64
	movs	r1, #1
	bl	RCC_APB1PeriphResetCmd
	movs	r0, #64
	b	.LBB504_27
.LBB504_21:
	movw	r1, #8191
	movt	r1, #16384
	cmp	r0, r1
	bgt	.LBB504_24
@ BB#22:
	movw	r1, #7168
	movt	r1, #16384
	cmp	r0, r1
	bne	.LBB504_28
@ BB#23:
	movs	r0, #128
	movs	r1, #1
	bl	RCC_APB1PeriphResetCmd
	movs	r0, #128
	b	.LBB504_27
.LBB504_24:
	movw	r1, #65535
	movt	r1, #16384
	cmp	r0, r1
	bgt	.LBB504_29
@ BB#25:
	movw	r1, #8192
	movt	r1, #16384
	cmp	r0, r1
	bne	.LBB504_28
@ BB#26:
	mov.w	r0, #256
	movs	r1, #1
	bl	RCC_APB1PeriphResetCmd
	mov.w	r0, #256
.LBB504_27:
	movs	r1, #0
	bl	RCC_APB1PeriphResetCmd
.LBB504_28:
	pop	{r7, pc}
.LBB504_29:
	movw	r1, #1023
	movt	r1, #16385
	cmp	r0, r1
	bgt	.LBB504_32
@ BB#30:
	movs	r1, #0
	movt	r1, #16385
	cmp	r0, r1
	bne	.LBB504_28
@ BB#31:
	movs	r0, #1
	movs	r1, #1
	bl	RCC_APB2PeriphResetCmd
	movs	r0, #1
	b	.LBB504_40
.LBB504_32:
	movw	r1, #16383
	movt	r1, #16385
	cmp	r0, r1
	bgt	.LBB504_35
@ BB#33:
	movw	r1, #1024
	movt	r1, #16385
	cmp	r0, r1
	bne	.LBB504_28
@ BB#34:
	movs	r0, #2
	movs	r1, #1
	bl	RCC_APB2PeriphResetCmd
	movs	r0, #2
	b	.LBB504_40
.LBB504_35:
	movw	r1, #16384
	movt	r1, #16385
	cmp	r0, r1
	beq	.LBB504_38
@ BB#36:
	movw	r1, #17408
	movt	r1, #16385
	cmp	r0, r1
	bne	.LBB504_39
@ BB#37:
	mov.w	r0, #131072
	movs	r1, #1
	bl	RCC_APB2PeriphResetCmd
	mov.w	r0, #131072
	b	.LBB504_40
.LBB504_38:
	mov.w	r0, #65536
	movs	r1, #1
	bl	RCC_APB2PeriphResetCmd
	mov.w	r0, #65536
	b	.LBB504_40
.LBB504_39:
	movw	r1, #18432
	movt	r1, #16385
	cmp	r0, r1
	it	ne
	popne	{r7, pc}
	mov.w	r0, #262144
	movs	r1, #1
	bl	RCC_APB2PeriphResetCmd
	mov.w	r0, #262144
.LBB504_40:
	movs	r1, #0
	bl	RCC_APB2PeriphResetCmd
	pop	{r7, pc}
.Ltmp504:
	.size	TIM_DeInit, .Ltmp504-TIM_DeInit

	.globl	TIM_TimeBaseInit
	.align	2
	.type	TIM_TimeBaseInit,%function
	.code	16                      @ @TIM_TimeBaseInit
	.thumb_func
TIM_TimeBaseInit:
@ BB#0:
	ldrh.w	r12, [r0]
	movw	r3, #1023
	movt	r3, #16384
	cmp	r0, r3
	bgt	.LBB505_2
@ BB#1:
	cmp.w	r0, #1073741824
	beq	.LBB505_9
	b	.LBB505_10
.LBB505_2:
	movw	r3, #2047
	movt	r3, #16384
	cmp	r0, r3
	bgt	.LBB505_4
@ BB#3:
	movw	r3, #1024
	movt	r3, #16384
	b	.LBB505_8
.LBB505_4:
	movw	r3, #3071
	movt	r3, #16384
	cmp	r0, r3
	bgt	.LBB505_6
@ BB#5:
	movw	r3, #2048
	movt	r3, #16384
	b	.LBB505_8
.LBB505_6:
	movw	r3, #3072
	movt	r3, #16384
	cmp	r0, r3
	ittt	ne
	movne	r3, #0
	movtne	r3, #16385
	cmpne	r0, r3
	beq	.LBB505_9
@ BB#7:
	movw	r3, #1024
	movt	r3, #16385
.LBB505_8:
	cmp	r0, r3
	bne	.LBB505_10
.LBB505_9:
	ldrh	r3, [r1, #2]
	bic	r2, r12, #112
	orr.w	r12, r3, r2
.LBB505_10:
	movw	r2, #5120
	orr	r3, r0, #1024
	movt	r2, #16384
	cmp	r3, r2
	ittt	ne
	bicne	r12, r12, #768
	ldrhne	r2, [r1, #8]
	orrne.w	r12, r12, r2
	strh.w	r12, [r0]
	ldr	r2, [r1, #4]
	str	r2, [r0, #44]
	ldrh	r2, [r1]
	strh	r2, [r0, #40]
	movw	r2, #1024
	movt	r2, #16385
	cmp	r3, r2
	itt	eq
	ldrbeq	r1, [r1, #10]
	strheq	r1, [r0, #48]
	movs	r1, #1
	strh	r1, [r0, #20]
	bx	lr
.Ltmp505:
	.size	TIM_TimeBaseInit, .Ltmp505-TIM_TimeBaseInit

	.globl	TIM_TimeBaseStructInit
	.align	2
	.type	TIM_TimeBaseStructInit,%function
	.code	16                      @ @TIM_TimeBaseStructInit
	.thumb_func
TIM_TimeBaseStructInit:
@ BB#0:
	mov.w	r1, #-1
	str	r1, [r0, #4]
	movs	r1, #0
	strh	r1, [r0]
	strh	r1, [r0, #8]
	strh	r1, [r0, #2]
	strb	r1, [r0, #10]
	bx	lr
.Ltmp506:
	.size	TIM_TimeBaseStructInit, .Ltmp506-TIM_TimeBaseStructInit

	.globl	TIM_PrescalerConfig
	.align	2
	.type	TIM_PrescalerConfig,%function
	.code	16                      @ @TIM_PrescalerConfig
	.thumb_func
TIM_PrescalerConfig:
@ BB#0:
	strh	r1, [r0, #40]
	strh	r2, [r0, #20]
	bx	lr
.Ltmp507:
	.size	TIM_PrescalerConfig, .Ltmp507-TIM_PrescalerConfig

	.globl	TIM_CounterModeConfig
	.align	2
	.type	TIM_CounterModeConfig,%function
	.code	16                      @ @TIM_CounterModeConfig
	.thumb_func
TIM_CounterModeConfig:
@ BB#0:
	ldrh	r2, [r0]
	bic	r2, r2, #112
	orrs	r1, r2
	strh	r1, [r0]
	bx	lr
.Ltmp508:
	.size	TIM_CounterModeConfig, .Ltmp508-TIM_CounterModeConfig

	.globl	TIM_SetCounter
	.align	2
	.type	TIM_SetCounter,%function
	.code	16                      @ @TIM_SetCounter
	.thumb_func
TIM_SetCounter:
@ BB#0:
	str	r1, [r0, #36]
	bx	lr
.Ltmp509:
	.size	TIM_SetCounter, .Ltmp509-TIM_SetCounter

	.globl	TIM_SetAutoreload
	.align	2
	.type	TIM_SetAutoreload,%function
	.code	16                      @ @TIM_SetAutoreload
	.thumb_func
TIM_SetAutoreload:
@ BB#0:
	str	r1, [r0, #44]
	bx	lr
.Ltmp510:
	.size	TIM_SetAutoreload, .Ltmp510-TIM_SetAutoreload

	.globl	TIM_GetCounter
	.align	2
	.type	TIM_GetCounter,%function
	.code	16                      @ @TIM_GetCounter
	.thumb_func
TIM_GetCounter:
@ BB#0:
	ldr	r0, [r0, #36]
	bx	lr
.Ltmp511:
	.size	TIM_GetCounter, .Ltmp511-TIM_GetCounter

	.globl	TIM_GetPrescaler
	.align	2
	.type	TIM_GetPrescaler,%function
	.code	16                      @ @TIM_GetPrescaler
	.thumb_func
TIM_GetPrescaler:
@ BB#0:
	ldrh	r0, [r0, #40]
	bx	lr
.Ltmp512:
	.size	TIM_GetPrescaler, .Ltmp512-TIM_GetPrescaler

	.globl	TIM_UpdateDisableConfig
	.align	2
	.type	TIM_UpdateDisableConfig,%function
	.code	16                      @ @TIM_UpdateDisableConfig
	.thumb_func
TIM_UpdateDisableConfig:
@ BB#0:
	ldrh	r2, [r0]
	cmp	r1, #0
	ite	eq
	biceq	r1, r2, #2
	orrne	r1, r2, #2
	strh	r1, [r0]
	bx	lr
.Ltmp513:
	.size	TIM_UpdateDisableConfig, .Ltmp513-TIM_UpdateDisableConfig

	.globl	TIM_UpdateRequestConfig
	.align	2
	.type	TIM_UpdateRequestConfig,%function
	.code	16                      @ @TIM_UpdateRequestConfig
	.thumb_func
TIM_UpdateRequestConfig:
@ BB#0:
	ldrh	r2, [r0]
	cmp	r1, #0
	ite	eq
	biceq	r1, r2, #4
	orrne	r1, r2, #4
	strh	r1, [r0]
	bx	lr
.Ltmp514:
	.size	TIM_UpdateRequestConfig, .Ltmp514-TIM_UpdateRequestConfig

	.globl	TIM_ARRPreloadConfig
	.align	2
	.type	TIM_ARRPreloadConfig,%function
	.code	16                      @ @TIM_ARRPreloadConfig
	.thumb_func
TIM_ARRPreloadConfig:
@ BB#0:
	ldrh	r2, [r0]
	cmp	r1, #0
	ite	eq
	biceq	r1, r2, #128
	orrne	r1, r2, #128
	strh	r1, [r0]
	bx	lr
.Ltmp515:
	.size	TIM_ARRPreloadConfig, .Ltmp515-TIM_ARRPreloadConfig

	.globl	TIM_SelectOnePulseMode
	.align	2
	.type	TIM_SelectOnePulseMode,%function
	.code	16                      @ @TIM_SelectOnePulseMode
	.thumb_func
TIM_SelectOnePulseMode:
@ BB#0:
	ldrh	r2, [r0]
	bic	r2, r2, #8
	strh	r2, [r0]
	ldrh	r2, [r0]
	orrs	r1, r2
	strh	r1, [r0]
	bx	lr
.Ltmp516:
	.size	TIM_SelectOnePulseMode, .Ltmp516-TIM_SelectOnePulseMode

	.globl	TIM_SetClockDivision
	.align	2
	.type	TIM_SetClockDivision,%function
	.code	16                      @ @TIM_SetClockDivision
	.thumb_func
TIM_SetClockDivision:
@ BB#0:
	ldrh	r2, [r0]
	bic	r2, r2, #768
	strh	r2, [r0]
	ldrh	r2, [r0]
	orrs	r1, r2
	strh	r1, [r0]
	bx	lr
.Ltmp517:
	.size	TIM_SetClockDivision, .Ltmp517-TIM_SetClockDivision

	.globl	TIM_Cmd
	.align	2
	.type	TIM_Cmd,%function
	.code	16                      @ @TIM_Cmd
	.thumb_func
TIM_Cmd:
@ BB#0:
	ldrh	r2, [r0]
	cmp	r1, #0
	ite	eq
	biceq	r1, r2, #1
	orrne	r1, r2, #1
	strh	r1, [r0]
	bx	lr
.Ltmp518:
	.size	TIM_Cmd, .Ltmp518-TIM_Cmd

	.globl	TIM_OC1Init
	.align	2
	.type	TIM_OC1Init,%function
	.code	16                      @ @TIM_OC1Init
	.thumb_func
TIM_OC1Init:
@ BB#0:
	push	{r4, lr}
	ldrh	r2, [r0, #32]
	bic	r2, r2, #1
	strh	r2, [r0, #32]
	ldrh	r4, [r0, #32]
	ldrh.w	lr, [r0, #4]
	ldrh	r3, [r0, #24]
	ldrh	r2, [r1]
	bic	r3, r3, #115
	orr.w	r12, r3, r2
	ldrh	r3, [r1, #12]
	bic	r2, r4, #2
	movw	r4, #1024
	movt	r4, #16385
	orrs	r2, r3
	ldrh	r3, [r1, #2]
	orrs	r2, r3
	orr	r3, r0, #1024
	cmp	r3, r4
	bne	.LBB519_2
@ BB#1:
	ldrh	r4, [r1, #16]
	bic	r3, lr, #768
	bic	r2, r2, #12
	orrs	r3, r4
	ldrh	r4, [r1, #18]
	orr.w	lr, r3, r4
	ldrh	r3, [r1, #14]
	bic	r3, r3, #4
	orrs	r2, r3
	ldrh	r3, [r1, #4]
	orrs	r2, r3
.LBB519_2:
	strh.w	lr, [r0, #4]
	strh.w	r12, [r0, #24]
	ldr	r1, [r1, #8]
	str	r1, [r0, #52]
	strh	r2, [r0, #32]
	pop	{r4, pc}
.Ltmp519:
	.size	TIM_OC1Init, .Ltmp519-TIM_OC1Init

	.globl	TIM_OC2Init
	.align	2
	.type	TIM_OC2Init,%function
	.code	16                      @ @TIM_OC2Init
	.thumb_func
TIM_OC2Init:
@ BB#0:
	push	{r4, lr}
	ldrh	r2, [r0, #32]
	bic	r2, r2, #16
	strh	r2, [r0, #32]
	ldrh	r4, [r0, #32]
	ldrh.w	lr, [r0, #4]
	ldrh	r3, [r0, #24]
	ldrh	r2, [r1]
	bic	r3, r3, #29440
	orr.w	r12, r3, r2, lsl #8
	ldrh	r3, [r1, #12]
	bic	r2, r4, #32
	movw	r4, #1024
	movt	r4, #16385
	orr.w	r2, r2, r3, lsl #4
	ldrh	r3, [r1, #2]
	orr.w	r2, r2, r3, lsl #4
	orr	r3, r0, #1024
	cmp	r3, r4
	bne	.LBB520_2
@ BB#1:
	movw	r3, #65343
	movw	r4, #65456
	ands	r2, r3
	ldrh	r3, [r1, #14]
	and.w	r3, r4, r3, lsl #4
	bic	r4, lr, #3072
	orrs	r2, r3
	ldrh	r3, [r1, #4]
	orr.w	r2, r2, r3, lsl #4
	ldrh	r3, [r1, #16]
	orr.w	r3, r4, r3, lsl #2
	ldrh	r4, [r1, #18]
	orr.w	lr, r3, r4, lsl #2
.LBB520_2:
	strh.w	lr, [r0, #4]
	strh.w	r12, [r0, #24]
	ldr	r1, [r1, #8]
	str	r1, [r0, #56]
	strh	r2, [r0, #32]
	pop	{r4, pc}
.Ltmp520:
	.size	TIM_OC2Init, .Ltmp520-TIM_OC2Init

	.globl	TIM_OC3Init
	.align	2
	.type	TIM_OC3Init,%function
	.code	16                      @ @TIM_OC3Init
	.thumb_func
TIM_OC3Init:
@ BB#0:
	push	{r4, lr}
	ldrh	r2, [r0, #32]
	bic	r2, r2, #256
	strh	r2, [r0, #32]
	ldrh	r4, [r0, #32]
	ldrh.w	lr, [r0, #4]
	ldrh	r3, [r0, #28]
	ldrh	r2, [r1]
	bic	r3, r3, #115
	orr.w	r12, r3, r2
	ldrh	r3, [r1, #12]
	bic	r2, r4, #512
	movw	r4, #1024
	movt	r4, #16385
	orr.w	r2, r2, r3, lsl #8
	ldrh	r3, [r1, #2]
	orr.w	r2, r2, r3, lsl #8
	orr	r3, r0, #1024
	cmp	r3, r4
	bne	.LBB521_2
@ BB#1:
	movw	r3, #62463
	mov.w	r4, #64256
	ands	r2, r3
	ldrh	r3, [r1, #14]
	and.w	r3, r4, r3, lsl #8
	bic	r4, lr, #12288
	orrs	r2, r3
	ldrh	r3, [r1, #4]
	orr.w	r2, r2, r3, lsl #8
	ldrh	r3, [r1, #16]
	orr.w	r3, r4, r3, lsl #4
	ldrh	r4, [r1, #18]
	orr.w	lr, r3, r4, lsl #4
.LBB521_2:
	strh.w	lr, [r0, #4]
	strh.w	r12, [r0, #28]
	ldr	r1, [r1, #8]
	str	r1, [r0, #60]
	strh	r2, [r0, #32]
	pop	{r4, pc}
.Ltmp521:
	.size	TIM_OC3Init, .Ltmp521-TIM_OC3Init

	.globl	TIM_OC4Init
	.align	2
	.type	TIM_OC4Init,%function
	.code	16                      @ @TIM_OC4Init
	.thumb_func
TIM_OC4Init:
@ BB#0:
	push	{r4, lr}
	ldrh	r2, [r0, #32]
	bic	r2, r2, #4096
	strh	r2, [r0, #32]
	ldrh.w	lr, [r0, #32]
	ldrh	r4, [r0, #4]
	ldrh	r3, [r0, #28]
	ldrh	r2, [r1]
	bic	r3, r3, #29440
	orr.w	r12, r3, r2, lsl #8
	ldrh	r3, [r1, #12]
	bic	r2, lr, #8192
	orr.w	r2, r2, r3, lsl #12
	ldrh	r3, [r1, #2]
	orr.w	lr, r2, r3, lsl #12
	movw	r3, #1024
	orr	r2, r0, #1024
	movt	r3, #16385
	cmp	r2, r3
	ittt	eq
	ldrheq	r2, [r1, #16]
	biceq	r3, r4, #16384
	orreq.w	r4, r3, r2, lsl #6
	strh	r4, [r0, #4]
	strh.w	r12, [r0, #28]
	ldr	r1, [r1, #8]
	str	r1, [r0, #64]
	strh.w	lr, [r0, #32]
	pop	{r4, pc}
.Ltmp522:
	.size	TIM_OC4Init, .Ltmp522-TIM_OC4Init

	.globl	TIM_OCStructInit
	.align	2
	.type	TIM_OCStructInit,%function
	.code	16                      @ @TIM_OCStructInit
	.thumb_func
TIM_OCStructInit:
@ BB#0:
	movs	r1, #0
	strh	r1, [r0]
	strh	r1, [r0, #2]
	strh	r1, [r0, #4]
	str	r1, [r0, #8]
	strh	r1, [r0, #14]
	strh	r1, [r0, #12]
	strh	r1, [r0, #18]
	strh	r1, [r0, #16]
	bx	lr
.Ltmp523:
	.size	TIM_OCStructInit, .Ltmp523-TIM_OCStructInit

	.globl	TIM_SelectOCxM
	.align	2
	.type	TIM_SelectOCxM,%function
	.code	16                      @ @TIM_SelectOCxM
	.thumb_func
TIM_SelectOCxM:
@ BB#0:
	movs	r3, #1
	lsl.w	r12, r3, r1
	ldrh	r3, [r0, #32]
	bic.w	r3, r3, r12
	strh	r3, [r0, #32]
	adds	r0, #24
	orr	r3, r1, #8
	cmp	r3, #8
	bne	.LBB524_2
@ BB#1:
	lsrs	r1, r1, #1
	movw	r3, #65423
	ldr.w	r12, [r1, r0]
	and.w	r3, r3, r12
	str	r3, [r1, r0]
	ldr	r3, [r1, r0]
	b	.LBB524_3
.LBB524_2:
	movw	r3, #65532
	lsls	r2, r2, #8
	add	r1, r3
	movw	r3, #36863
	uxth	r2, r2
	ubfx	r1, r1, #1, #15
	ldr.w	r12, [r1, r0]
	and.w	r3, r3, r12
	str	r3, [r1, r0]
	ldr	r3, [r1, r0]
.LBB524_3:
	orrs	r2, r3
	str	r2, [r1, r0]
	bx	lr
.Ltmp524:
	.size	TIM_SelectOCxM, .Ltmp524-TIM_SelectOCxM

	.globl	TIM_SetCompare1
	.align	2
	.type	TIM_SetCompare1,%function
	.code	16                      @ @TIM_SetCompare1
	.thumb_func
TIM_SetCompare1:
@ BB#0:
	str	r1, [r0, #52]
	bx	lr
.Ltmp525:
	.size	TIM_SetCompare1, .Ltmp525-TIM_SetCompare1

	.globl	TIM_SetCompare2
	.align	2
	.type	TIM_SetCompare2,%function
	.code	16                      @ @TIM_SetCompare2
	.thumb_func
TIM_SetCompare2:
@ BB#0:
	str	r1, [r0, #56]
	bx	lr
.Ltmp526:
	.size	TIM_SetCompare2, .Ltmp526-TIM_SetCompare2

	.globl	TIM_SetCompare3
	.align	2
	.type	TIM_SetCompare3,%function
	.code	16                      @ @TIM_SetCompare3
	.thumb_func
TIM_SetCompare3:
@ BB#0:
	str	r1, [r0, #60]
	bx	lr
.Ltmp527:
	.size	TIM_SetCompare3, .Ltmp527-TIM_SetCompare3

	.globl	TIM_SetCompare4
	.align	2
	.type	TIM_SetCompare4,%function
	.code	16                      @ @TIM_SetCompare4
	.thumb_func
TIM_SetCompare4:
@ BB#0:
	str	r1, [r0, #64]
	bx	lr
.Ltmp528:
	.size	TIM_SetCompare4, .Ltmp528-TIM_SetCompare4

	.globl	TIM_ForcedOC1Config
	.align	2
	.type	TIM_ForcedOC1Config,%function
	.code	16                      @ @TIM_ForcedOC1Config
	.thumb_func
TIM_ForcedOC1Config:
@ BB#0:
	ldrh	r2, [r0, #24]
	bic	r2, r2, #112
	orrs	r1, r2
	strh	r1, [r0, #24]
	bx	lr
.Ltmp529:
	.size	TIM_ForcedOC1Config, .Ltmp529-TIM_ForcedOC1Config

	.globl	TIM_ForcedOC2Config
	.align	2
	.type	TIM_ForcedOC2Config,%function
	.code	16                      @ @TIM_ForcedOC2Config
	.thumb_func
TIM_ForcedOC2Config:
@ BB#0:
	ldrh	r2, [r0, #24]
	bic	r2, r2, #28672
	orr.w	r1, r2, r1, lsl #8
	strh	r1, [r0, #24]
	bx	lr
.Ltmp530:
	.size	TIM_ForcedOC2Config, .Ltmp530-TIM_ForcedOC2Config

	.globl	TIM_ForcedOC3Config
	.align	2
	.type	TIM_ForcedOC3Config,%function
	.code	16                      @ @TIM_ForcedOC3Config
	.thumb_func
TIM_ForcedOC3Config:
@ BB#0:
	ldrh	r2, [r0, #28]
	bic	r2, r2, #112
	orrs	r1, r2
	strh	r1, [r0, #28]
	bx	lr
.Ltmp531:
	.size	TIM_ForcedOC3Config, .Ltmp531-TIM_ForcedOC3Config

	.globl	TIM_ForcedOC4Config
	.align	2
	.type	TIM_ForcedOC4Config,%function
	.code	16                      @ @TIM_ForcedOC4Config
	.thumb_func
TIM_ForcedOC4Config:
@ BB#0:
	ldrh	r2, [r0, #28]
	bic	r2, r2, #28672
	orr.w	r1, r2, r1, lsl #8
	strh	r1, [r0, #28]
	bx	lr
.Ltmp532:
	.size	TIM_ForcedOC4Config, .Ltmp532-TIM_ForcedOC4Config

	.globl	TIM_OC1PreloadConfig
	.align	2
	.type	TIM_OC1PreloadConfig,%function
	.code	16                      @ @TIM_OC1PreloadConfig
	.thumb_func
TIM_OC1PreloadConfig:
@ BB#0:
	ldrh	r2, [r0, #24]
	bic	r2, r2, #8
	orrs	r1, r2
	strh	r1, [r0, #24]
	bx	lr
.Ltmp533:
	.size	TIM_OC1PreloadConfig, .Ltmp533-TIM_OC1PreloadConfig

	.globl	TIM_OC2PreloadConfig
	.align	2
	.type	TIM_OC2PreloadConfig,%function
	.code	16                      @ @TIM_OC2PreloadConfig
	.thumb_func
TIM_OC2PreloadConfig:
@ BB#0:
	ldrh	r2, [r0, #24]
	bic	r2, r2, #2048
	orr.w	r1, r2, r1, lsl #8
	strh	r1, [r0, #24]
	bx	lr
.Ltmp534:
	.size	TIM_OC2PreloadConfig, .Ltmp534-TIM_OC2PreloadConfig

	.globl	TIM_OC3PreloadConfig
	.align	2
	.type	TIM_OC3PreloadConfig,%function
	.code	16                      @ @TIM_OC3PreloadConfig
	.thumb_func
TIM_OC3PreloadConfig:
@ BB#0:
	ldrh	r2, [r0, #28]
	bic	r2, r2, #8
	orrs	r1, r2
	strh	r1, [r0, #28]
	bx	lr
.Ltmp535:
	.size	TIM_OC3PreloadConfig, .Ltmp535-TIM_OC3PreloadConfig

	.globl	TIM_OC4PreloadConfig
	.align	2
	.type	TIM_OC4PreloadConfig,%function
	.code	16                      @ @TIM_OC4PreloadConfig
	.thumb_func
TIM_OC4PreloadConfig:
@ BB#0:
	ldrh	r2, [r0, #28]
	bic	r2, r2, #2048
	orr.w	r1, r2, r1, lsl #8
	strh	r1, [r0, #28]
	bx	lr
.Ltmp536:
	.size	TIM_OC4PreloadConfig, .Ltmp536-TIM_OC4PreloadConfig

	.globl	TIM_OC1FastConfig
	.align	2
	.type	TIM_OC1FastConfig,%function
	.code	16                      @ @TIM_OC1FastConfig
	.thumb_func
TIM_OC1FastConfig:
@ BB#0:
	ldrh	r2, [r0, #24]
	bic	r2, r2, #4
	orrs	r1, r2
	strh	r1, [r0, #24]
	bx	lr
.Ltmp537:
	.size	TIM_OC1FastConfig, .Ltmp537-TIM_OC1FastConfig

	.globl	TIM_OC2FastConfig
	.align	2
	.type	TIM_OC2FastConfig,%function
	.code	16                      @ @TIM_OC2FastConfig
	.thumb_func
TIM_OC2FastConfig:
@ BB#0:
	ldrh	r2, [r0, #24]
	bic	r2, r2, #1024
	orr.w	r1, r2, r1, lsl #8
	strh	r1, [r0, #24]
	bx	lr
.Ltmp538:
	.size	TIM_OC2FastConfig, .Ltmp538-TIM_OC2FastConfig

	.globl	TIM_OC3FastConfig
	.align	2
	.type	TIM_OC3FastConfig,%function
	.code	16                      @ @TIM_OC3FastConfig
	.thumb_func
TIM_OC3FastConfig:
@ BB#0:
	ldrh	r2, [r0, #28]
	bic	r2, r2, #4
	orrs	r1, r2
	strh	r1, [r0, #28]
	bx	lr
.Ltmp539:
	.size	TIM_OC3FastConfig, .Ltmp539-TIM_OC3FastConfig

	.globl	TIM_OC4FastConfig
	.align	2
	.type	TIM_OC4FastConfig,%function
	.code	16                      @ @TIM_OC4FastConfig
	.thumb_func
TIM_OC4FastConfig:
@ BB#0:
	ldrh	r2, [r0, #28]
	bic	r2, r2, #1024
	orr.w	r1, r2, r1, lsl #8
	strh	r1, [r0, #28]
	bx	lr
.Ltmp540:
	.size	TIM_OC4FastConfig, .Ltmp540-TIM_OC4FastConfig

	.globl	TIM_ClearOC1Ref
	.align	2
	.type	TIM_ClearOC1Ref,%function
	.code	16                      @ @TIM_ClearOC1Ref
	.thumb_func
TIM_ClearOC1Ref:
@ BB#0:
	ldrh	r2, [r0, #24]
	bic	r2, r2, #128
	orrs	r1, r2
	strh	r1, [r0, #24]
	bx	lr
.Ltmp541:
	.size	TIM_ClearOC1Ref, .Ltmp541-TIM_ClearOC1Ref

	.globl	TIM_ClearOC2Ref
	.align	2
	.type	TIM_ClearOC2Ref,%function
	.code	16                      @ @TIM_ClearOC2Ref
	.thumb_func
TIM_ClearOC2Ref:
@ BB#0:
	ldrh	r2, [r0, #24]
	bfc	r2, #15, #17
	orr.w	r1, r2, r1, lsl #8
	strh	r1, [r0, #24]
	bx	lr
.Ltmp542:
	.size	TIM_ClearOC2Ref, .Ltmp542-TIM_ClearOC2Ref

	.globl	TIM_ClearOC3Ref
	.align	2
	.type	TIM_ClearOC3Ref,%function
	.code	16                      @ @TIM_ClearOC3Ref
	.thumb_func
TIM_ClearOC3Ref:
@ BB#0:
	ldrh	r2, [r0, #28]
	bic	r2, r2, #128
	orrs	r1, r2
	strh	r1, [r0, #28]
	bx	lr
.Ltmp543:
	.size	TIM_ClearOC3Ref, .Ltmp543-TIM_ClearOC3Ref

	.globl	TIM_ClearOC4Ref
	.align	2
	.type	TIM_ClearOC4Ref,%function
	.code	16                      @ @TIM_ClearOC4Ref
	.thumb_func
TIM_ClearOC4Ref:
@ BB#0:
	ldrh	r2, [r0, #28]
	bfc	r2, #15, #17
	orr.w	r1, r2, r1, lsl #8
	strh	r1, [r0, #28]
	bx	lr
.Ltmp544:
	.size	TIM_ClearOC4Ref, .Ltmp544-TIM_ClearOC4Ref

	.globl	TIM_OC1PolarityConfig
	.align	2
	.type	TIM_OC1PolarityConfig,%function
	.code	16                      @ @TIM_OC1PolarityConfig
	.thumb_func
TIM_OC1PolarityConfig:
@ BB#0:
	ldrh	r2, [r0, #32]
	bic	r2, r2, #2
	orrs	r1, r2
	strh	r1, [r0, #32]
	bx	lr
.Ltmp545:
	.size	TIM_OC1PolarityConfig, .Ltmp545-TIM_OC1PolarityConfig

	.globl	TIM_OC1NPolarityConfig
	.align	2
	.type	TIM_OC1NPolarityConfig,%function
	.code	16                      @ @TIM_OC1NPolarityConfig
	.thumb_func
TIM_OC1NPolarityConfig:
@ BB#0:
	ldrh	r2, [r0, #32]
	bic	r2, r2, #8
	orrs	r1, r2
	strh	r1, [r0, #32]
	bx	lr
.Ltmp546:
	.size	TIM_OC1NPolarityConfig, .Ltmp546-TIM_OC1NPolarityConfig

	.globl	TIM_OC2PolarityConfig
	.align	2
	.type	TIM_OC2PolarityConfig,%function
	.code	16                      @ @TIM_OC2PolarityConfig
	.thumb_func
TIM_OC2PolarityConfig:
@ BB#0:
	ldrh	r2, [r0, #32]
	bic	r2, r2, #32
	orr.w	r1, r2, r1, lsl #4
	strh	r1, [r0, #32]
	bx	lr
.Ltmp547:
	.size	TIM_OC2PolarityConfig, .Ltmp547-TIM_OC2PolarityConfig

	.globl	TIM_OC2NPolarityConfig
	.align	2
	.type	TIM_OC2NPolarityConfig,%function
	.code	16                      @ @TIM_OC2NPolarityConfig
	.thumb_func
TIM_OC2NPolarityConfig:
@ BB#0:
	ldrh	r2, [r0, #32]
	bic	r2, r2, #128
	orr.w	r1, r2, r1, lsl #4
	strh	r1, [r0, #32]
	bx	lr
.Ltmp548:
	.size	TIM_OC2NPolarityConfig, .Ltmp548-TIM_OC2NPolarityConfig

	.globl	TIM_OC3PolarityConfig
	.align	2
	.type	TIM_OC3PolarityConfig,%function
	.code	16                      @ @TIM_OC3PolarityConfig
	.thumb_func
TIM_OC3PolarityConfig:
@ BB#0:
	ldrh	r2, [r0, #32]
	bic	r2, r2, #512
	orr.w	r1, r2, r1, lsl #8
	strh	r1, [r0, #32]
	bx	lr
.Ltmp549:
	.size	TIM_OC3PolarityConfig, .Ltmp549-TIM_OC3PolarityConfig

	.globl	TIM_OC3NPolarityConfig
	.align	2
	.type	TIM_OC3NPolarityConfig,%function
	.code	16                      @ @TIM_OC3NPolarityConfig
	.thumb_func
TIM_OC3NPolarityConfig:
@ BB#0:
	ldrh	r2, [r0, #32]
	bic	r2, r2, #2048
	orr.w	r1, r2, r1, lsl #8
	strh	r1, [r0, #32]
	bx	lr
.Ltmp550:
	.size	TIM_OC3NPolarityConfig, .Ltmp550-TIM_OC3NPolarityConfig

	.globl	TIM_OC4PolarityConfig
	.align	2
	.type	TIM_OC4PolarityConfig,%function
	.code	16                      @ @TIM_OC4PolarityConfig
	.thumb_func
TIM_OC4PolarityConfig:
@ BB#0:
	ldrh	r2, [r0, #32]
	bic	r2, r2, #8192
	orr.w	r1, r2, r1, lsl #12
	strh	r1, [r0, #32]
	bx	lr
.Ltmp551:
	.size	TIM_OC4PolarityConfig, .Ltmp551-TIM_OC4PolarityConfig

	.globl	TIM_CCxCmd
	.align	2
	.type	TIM_CCxCmd,%function
	.code	16                      @ @TIM_CCxCmd
	.thumb_func
TIM_CCxCmd:
@ BB#0:
	movs	r3, #1
	lsl.w	r12, r3, r1
	ldrh	r3, [r0, #32]
	lsl.w	r1, r2, r1
	bic.w	r3, r3, r12
	strh	r3, [r0, #32]
	ldrh	r2, [r0, #32]
	orrs	r1, r2
	strh	r1, [r0, #32]
	bx	lr
.Ltmp552:
	.size	TIM_CCxCmd, .Ltmp552-TIM_CCxCmd

	.globl	TIM_CCxNCmd
	.align	2
	.type	TIM_CCxNCmd,%function
	.code	16                      @ @TIM_CCxNCmd
	.thumb_func
TIM_CCxNCmd:
@ BB#0:
	movs	r3, #4
	lsl.w	r12, r3, r1
	ldrh	r3, [r0, #32]
	lsl.w	r1, r2, r1
	bic.w	r3, r3, r12
	strh	r3, [r0, #32]
	ldrh	r2, [r0, #32]
	orrs	r1, r2
	strh	r1, [r0, #32]
	bx	lr
.Ltmp553:
	.size	TIM_CCxNCmd, .Ltmp553-TIM_CCxNCmd

	.globl	TIM_ICInit
	.align	2
	.type	TIM_ICInit,%function
	.code	16                      @ @TIM_ICInit
	.thumb_func
TIM_ICInit:
@ BB#0:
	push	{r4, lr}
	ldrh	r2, [r1]
	cmp	r2, #4
	bne	.LBB554_2
@ BB#1:
	ldrh.w	r12, [r1, #2]
	ldrh	r3, [r1, #4]
	ldrh	r4, [r1, #8]
	ldrh	r2, [r0, #32]
	bic	r2, r2, #16
	strh	r2, [r0, #32]
	lsls	r2, r4, #12
	movw	r4, #3327
	orr.w	r2, r2, r3, lsl #8
	ldrh	r3, [r0, #24]
	ands	r3, r4
	orrs	r2, r3
	ldrh	r3, [r0, #32]
	strh	r2, [r0, #24]
	bic	r2, r3, #176
	orr.w	r2, r2, r12, lsl #4
	orr	r2, r2, #16
	strh	r2, [r0, #32]
	ldrh	r1, [r1, #6]
	ldrh	r2, [r0, #24]
	bic	r2, r2, #3072
	strh	r2, [r0, #24]
	ldrh	r2, [r0, #24]
	orr.w	r1, r2, r1, lsl #8
	strh	r1, [r0, #24]
	pop	{r4, pc}
.LBB554_2:
	cbnz	r2, .LBB554_4
@ BB#3:
	ldrh.w	r12, [r1, #2]
	ldrh	r3, [r1, #8]
	ldrh	r4, [r1, #4]
	ldrh	r2, [r0, #32]
	bic	r2, r2, #1
	strh	r2, [r0, #32]
	orr.w	r2, r4, r3, lsl #4
	ldrh	r3, [r0, #24]
	bic	r3, r3, #243
	orrs	r2, r3
	ldrh	r3, [r0, #32]
	strh	r2, [r0, #24]
	bic	r2, r3, #11
	orr.w	r2, r2, r12
	orr	r2, r2, #1
	strh	r2, [r0, #32]
	ldrh	r1, [r1, #6]
	ldrh	r2, [r0, #24]
	bic	r2, r2, #12
	strh	r2, [r0, #24]
	ldrh	r2, [r0, #24]
	orrs	r1, r2
	strh	r1, [r0, #24]
	pop	{r4, pc}
.LBB554_4:
	ldrh.w	lr, [r1, #8]
	ldrh	r3, [r1, #4]
	ldrh.w	r12, [r1, #2]
	ldrh	r4, [r0, #32]
	cmp	r2, #8
	bne	.LBB554_6
@ BB#5:
	bic	r2, r4, #256
	strh	r2, [r0, #32]
	orr.w	r2, r3, lr, lsl #4
	ldrh	r3, [r0, #28]
	bic	r3, r3, #243
	orrs	r2, r3
	ldrh	r3, [r0, #32]
	strh	r2, [r0, #28]
	bic	r2, r3, #2816
	orr.w	r2, r2, r12, lsl #8
	orr	r2, r2, #256
	strh	r2, [r0, #32]
	ldrh	r1, [r1, #6]
	ldrh	r2, [r0, #28]
	bic	r2, r2, #12
	strh	r2, [r0, #28]
	ldrh	r2, [r0, #28]
	orrs	r1, r2
	strh	r1, [r0, #28]
	pop	{r4, pc}
.LBB554_6:
	bic	r2, r4, #4096
	movw	r4, #3327
	strh	r2, [r0, #32]
	lsl.w	r2, lr, #12
	orr.w	r2, r2, r3, lsl #8
	ldrh	r3, [r0, #28]
	ands	r3, r4
	orrs	r2, r3
	ldrh	r3, [r0, #32]
	strh	r2, [r0, #28]
	movw	r2, #20479
	ands	r2, r3
	orr.w	r2, r2, r12, lsl #12
	orr	r2, r2, #4096
	strh	r2, [r0, #32]
	ldrh	r1, [r1, #6]
	ldrh	r2, [r0, #28]
	bic	r2, r2, #3072
	strh	r2, [r0, #28]
	ldrh	r2, [r0, #28]
	orr.w	r1, r2, r1, lsl #8
	strh	r1, [r0, #28]
	pop	{r4, pc}
.Ltmp554:
	.size	TIM_ICInit, .Ltmp554-TIM_ICInit

	.globl	TIM_SetIC1Prescaler
	.align	2
	.type	TIM_SetIC1Prescaler,%function
	.code	16                      @ @TIM_SetIC1Prescaler
	.thumb_func
TIM_SetIC1Prescaler:
@ BB#0:
	ldrh	r2, [r0, #24]
	bic	r2, r2, #12
	strh	r2, [r0, #24]
	ldrh	r2, [r0, #24]
	orrs	r1, r2
	strh	r1, [r0, #24]
	bx	lr
.Ltmp555:
	.size	TIM_SetIC1Prescaler, .Ltmp555-TIM_SetIC1Prescaler

	.globl	TIM_SetIC2Prescaler
	.align	2
	.type	TIM_SetIC2Prescaler,%function
	.code	16                      @ @TIM_SetIC2Prescaler
	.thumb_func
TIM_SetIC2Prescaler:
@ BB#0:
	ldrh	r2, [r0, #24]
	bic	r2, r2, #3072
	strh	r2, [r0, #24]
	ldrh	r2, [r0, #24]
	orr.w	r1, r2, r1, lsl #8
	strh	r1, [r0, #24]
	bx	lr
.Ltmp556:
	.size	TIM_SetIC2Prescaler, .Ltmp556-TIM_SetIC2Prescaler

	.globl	TIM_SetIC3Prescaler
	.align	2
	.type	TIM_SetIC3Prescaler,%function
	.code	16                      @ @TIM_SetIC3Prescaler
	.thumb_func
TIM_SetIC3Prescaler:
@ BB#0:
	ldrh	r2, [r0, #28]
	bic	r2, r2, #12
	strh	r2, [r0, #28]
	ldrh	r2, [r0, #28]
	orrs	r1, r2
	strh	r1, [r0, #28]
	bx	lr
.Ltmp557:
	.size	TIM_SetIC3Prescaler, .Ltmp557-TIM_SetIC3Prescaler

	.globl	TIM_SetIC4Prescaler
	.align	2
	.type	TIM_SetIC4Prescaler,%function
	.code	16                      @ @TIM_SetIC4Prescaler
	.thumb_func
TIM_SetIC4Prescaler:
@ BB#0:
	ldrh	r2, [r0, #28]
	bic	r2, r2, #3072
	strh	r2, [r0, #28]
	ldrh	r2, [r0, #28]
	orr.w	r1, r2, r1, lsl #8
	strh	r1, [r0, #28]
	bx	lr
.Ltmp558:
	.size	TIM_SetIC4Prescaler, .Ltmp558-TIM_SetIC4Prescaler

	.globl	TIM_ICStructInit
	.align	2
	.type	TIM_ICStructInit,%function
	.code	16                      @ @TIM_ICStructInit
	.thumb_func
TIM_ICStructInit:
@ BB#0:
	movs	r1, #0
	movs	r2, #1
	strh	r1, [r0, #2]
	strh	r1, [r0]
	strh	r1, [r0, #6]
	strh	r2, [r0, #4]
	strh	r1, [r0, #8]
	bx	lr
.Ltmp559:
	.size	TIM_ICStructInit, .Ltmp559-TIM_ICStructInit

	.globl	TIM_PWMIConfig
	.align	2
	.type	TIM_PWMIConfig,%function
	.code	16                      @ @TIM_PWMIConfig
	.thumb_func
TIM_PWMIConfig:
@ BB#0:
	push	{r4, r5, r6, lr}
	ldrh	r3, [r1, #4]
	mov.w	lr, #1
	mov.w	r12, #0
	cmp	r3, #1
	it	eq
	moveq.w	lr, #2
	ldrh	r2, [r1, #2]
	cmp	r2, #0
	it	eq
	moveq.w	r12, #2
	ldrh	r6, [r1]
	ldrh	r4, [r1, #8]
	ldrh	r5, [r0, #32]
	cmp	r6, #0
	beq	.LBB560_2
@ BB#1:
	bic	r5, r5, #16
	lsls	r4, r4, #12
	strh	r5, [r0, #32]
	orr.w	r3, r4, r3, lsl #8
	movw	r5, #3327
	ldrh	r4, [r0, #24]
	ands	r4, r5
	orrs	r3, r4
	ldrh	r4, [r0, #32]
	strh	r3, [r0, #24]
	bic	r3, r4, #176
	orr.w	r2, r3, r2, lsl #4
	orr	r2, r2, #16
	strh	r2, [r0, #32]
	ldrh	r2, [r1, #6]
	ldrh	r3, [r0, #24]
	bic	r3, r3, #3072
	strh	r3, [r0, #24]
	ldrh	r3, [r0, #24]
	orr.w	r2, r3, r2, lsl #8
	strh	r2, [r0, #24]
	ldrh	r2, [r1, #8]
	ldrh	r3, [r0, #32]
	bic	r3, r3, #1
	orr.w	r2, lr, r2, lsl #4
	strh	r3, [r0, #32]
	ldrh	r3, [r0, #24]
	bic	r3, r3, #243
	orrs	r2, r3
	ldrh	r3, [r0, #32]
	strh	r2, [r0, #24]
	bic	r2, r3, #11
	orr.w	r2, r2, r12
	orr	r2, r2, #1
	strh	r2, [r0, #32]
	ldrh	r1, [r1, #6]
	ldrh	r2, [r0, #24]
	bic	r2, r2, #12
	strh	r2, [r0, #24]
	ldrh	r2, [r0, #24]
	orrs	r1, r2
	strh	r1, [r0, #24]
	pop	{r4, r5, r6, pc}
.LBB560_2:
	bic	r5, r5, #1
	orr.w	r3, r3, r4, lsl #4
	movw	r6, #3327
	strh	r5, [r0, #32]
	ldrh	r4, [r0, #24]
	bic	r4, r4, #243
	orrs	r3, r4
	ldrh	r4, [r0, #32]
	strh	r3, [r0, #24]
	bic	r3, r4, #11
	orrs	r2, r3
	orr	r2, r2, #1
	strh	r2, [r0, #32]
	ldrh	r2, [r1, #6]
	ldrh	r3, [r0, #24]
	bic	r3, r3, #12
	strh	r3, [r0, #24]
	ldrh	r3, [r0, #24]
	orrs	r2, r3
	strh	r2, [r0, #24]
	ldrh	r2, [r1, #8]
	ldrh	r3, [r0, #32]
	bic	r3, r3, #16
	lsls	r2, r2, #12
	strh	r3, [r0, #32]
	orr.w	r2, r2, lr, lsl #8
	ldrh	r3, [r0, #24]
	ands	r3, r6
	orrs	r2, r3
	ldrh	r3, [r0, #32]
	strh	r2, [r0, #24]
	bic	r2, r3, #176
	orr.w	r2, r2, r12, lsl #4
	orr	r2, r2, #16
	strh	r2, [r0, #32]
	ldrh	r1, [r1, #6]
	ldrh	r2, [r0, #24]
	bic	r2, r2, #3072
	strh	r2, [r0, #24]
	ldrh	r2, [r0, #24]
	orr.w	r1, r2, r1, lsl #8
	strh	r1, [r0, #24]
	pop	{r4, r5, r6, pc}
.Ltmp560:
	.size	TIM_PWMIConfig, .Ltmp560-TIM_PWMIConfig

	.globl	TIM_GetCapture1
	.align	2
	.type	TIM_GetCapture1,%function
	.code	16                      @ @TIM_GetCapture1
	.thumb_func
TIM_GetCapture1:
@ BB#0:
	ldr	r0, [r0, #52]
	bx	lr
.Ltmp561:
	.size	TIM_GetCapture1, .Ltmp561-TIM_GetCapture1

	.globl	TIM_GetCapture2
	.align	2
	.type	TIM_GetCapture2,%function
	.code	16                      @ @TIM_GetCapture2
	.thumb_func
TIM_GetCapture2:
@ BB#0:
	ldr	r0, [r0, #56]
	bx	lr
.Ltmp562:
	.size	TIM_GetCapture2, .Ltmp562-TIM_GetCapture2

	.globl	TIM_GetCapture3
	.align	2
	.type	TIM_GetCapture3,%function
	.code	16                      @ @TIM_GetCapture3
	.thumb_func
TIM_GetCapture3:
@ BB#0:
	ldr	r0, [r0, #60]
	bx	lr
.Ltmp563:
	.size	TIM_GetCapture3, .Ltmp563-TIM_GetCapture3

	.globl	TIM_GetCapture4
	.align	2
	.type	TIM_GetCapture4,%function
	.code	16                      @ @TIM_GetCapture4
	.thumb_func
TIM_GetCapture4:
@ BB#0:
	ldr	r0, [r0, #64]
	bx	lr
.Ltmp564:
	.size	TIM_GetCapture4, .Ltmp564-TIM_GetCapture4

	.globl	TIM_BDTRConfig
	.align	2
	.type	TIM_BDTRConfig,%function
	.code	16                      @ @TIM_BDTRConfig
	.thumb_func
TIM_BDTRConfig:
@ BB#0:
	ldrh	r2, [r1]
	ldrh	r3, [r1, #2]
	orrs	r2, r3
	ldrh	r3, [r1, #4]
	orrs	r2, r3
	ldrh	r3, [r1, #6]
	orrs	r2, r3
	ldrh	r3, [r1, #8]
	orrs	r2, r3
	ldrh	r3, [r1, #10]
	ldrh	r1, [r1, #12]
	orrs	r2, r3
	orrs	r1, r2
	strh.w	r1, [r0, #68]
	bx	lr
.Ltmp565:
	.size	TIM_BDTRConfig, .Ltmp565-TIM_BDTRConfig

	.globl	TIM_BDTRStructInit
	.align	2
	.type	TIM_BDTRStructInit,%function
	.code	16                      @ @TIM_BDTRStructInit
	.thumb_func
TIM_BDTRStructInit:
@ BB#0:
	movs	r1, #0
	strh	r1, [r0, #2]
	strh	r1, [r0]
	strh	r1, [r0, #6]
	strh	r1, [r0, #4]
	strh	r1, [r0, #10]
	strh	r1, [r0, #8]
	strh	r1, [r0, #12]
	bx	lr
.Ltmp566:
	.size	TIM_BDTRStructInit, .Ltmp566-TIM_BDTRStructInit

	.globl	TIM_CtrlPWMOutputs
	.align	2
	.type	TIM_CtrlPWMOutputs,%function
	.code	16                      @ @TIM_CtrlPWMOutputs
	.thumb_func
TIM_CtrlPWMOutputs:
@ BB#0:
	ldrh.w	r2, [r0, #68]
	cmp	r1, #0
	ittt	eq
	bfceq	r2, #15, #17
	strheq.w	r2, [r0, #68]
	bxeq	lr
	orr	r1, r2, #32768
	strh.w	r1, [r0, #68]
	bx	lr
.Ltmp567:
	.size	TIM_CtrlPWMOutputs, .Ltmp567-TIM_CtrlPWMOutputs

	.globl	TIM_SelectCOM
	.align	2
	.type	TIM_SelectCOM,%function
	.code	16                      @ @TIM_SelectCOM
	.thumb_func
TIM_SelectCOM:
@ BB#0:
	ldrh	r2, [r0, #4]
	cmp	r1, #0
	ite	eq
	biceq	r1, r2, #4
	orrne	r1, r2, #4
	strh	r1, [r0, #4]
	bx	lr
.Ltmp568:
	.size	TIM_SelectCOM, .Ltmp568-TIM_SelectCOM

	.globl	TIM_CCPreloadControl
	.align	2
	.type	TIM_CCPreloadControl,%function
	.code	16                      @ @TIM_CCPreloadControl
	.thumb_func
TIM_CCPreloadControl:
@ BB#0:
	ldrh	r2, [r0, #4]
	cmp	r1, #0
	ite	eq
	biceq	r1, r2, #1
	orrne	r1, r2, #1
	strh	r1, [r0, #4]
	bx	lr
.Ltmp569:
	.size	TIM_CCPreloadControl, .Ltmp569-TIM_CCPreloadControl

	.globl	TIM_ITConfig
	.align	2
	.type	TIM_ITConfig,%function
	.code	16                      @ @TIM_ITConfig
	.thumb_func
TIM_ITConfig:
@ BB#0:
	cmp	r2, #0
	ldrh	r2, [r0, #12]
	ite	eq
	biceq.w	r1, r2, r1
	orrne	r1, r2
	strh	r1, [r0, #12]
	bx	lr
.Ltmp570:
	.size	TIM_ITConfig, .Ltmp570-TIM_ITConfig

	.globl	TIM_GenerateEvent
	.align	2
	.type	TIM_GenerateEvent,%function
	.code	16                      @ @TIM_GenerateEvent
	.thumb_func
TIM_GenerateEvent:
@ BB#0:
	strh	r1, [r0, #20]
	bx	lr
.Ltmp571:
	.size	TIM_GenerateEvent, .Ltmp571-TIM_GenerateEvent

	.globl	TIM_GetFlagStatus
	.align	2
	.type	TIM_GetFlagStatus,%function
	.code	16                      @ @TIM_GetFlagStatus
	.thumb_func
TIM_GetFlagStatus:
@ BB#0:
	ldrh	r0, [r0, #16]
	ands	r0, r1
	it	ne
	movne	r0, #1
	bx	lr
.Ltmp572:
	.size	TIM_GetFlagStatus, .Ltmp572-TIM_GetFlagStatus

	.globl	TIM_ClearFlag
	.align	2
	.type	TIM_ClearFlag,%function
	.code	16                      @ @TIM_ClearFlag
	.thumb_func
TIM_ClearFlag:
@ BB#0:
	mvns	r1, r1
	strh	r1, [r0, #16]
	bx	lr
.Ltmp573:
	.size	TIM_ClearFlag, .Ltmp573-TIM_ClearFlag

	.globl	TIM_GetITStatus
	.align	2
	.type	TIM_GetITStatus,%function
	.code	16                      @ @TIM_GetITStatus
	.thumb_func
TIM_GetITStatus:
@ BB#0:
	ldrh	r2, [r0, #16]
	ands	r2, r1
	it	ne
	movne	r2, #1
	ldrh	r0, [r0, #12]
	ands	r0, r1
	it	ne
	movne	r0, #1
	ands	r0, r2
	bx	lr
.Ltmp574:
	.size	TIM_GetITStatus, .Ltmp574-TIM_GetITStatus

	.globl	TIM_ClearITPendingBit
	.align	2
	.type	TIM_ClearITPendingBit,%function
	.code	16                      @ @TIM_ClearITPendingBit
	.thumb_func
TIM_ClearITPendingBit:
@ BB#0:
	mvns	r1, r1
	strh	r1, [r0, #16]
	bx	lr
.Ltmp575:
	.size	TIM_ClearITPendingBit, .Ltmp575-TIM_ClearITPendingBit

	.globl	TIM_DMAConfig
	.align	2
	.type	TIM_DMAConfig,%function
	.code	16                      @ @TIM_DMAConfig
	.thumb_func
TIM_DMAConfig:
@ BB#0:
	orrs	r1, r2
	strh.w	r1, [r0, #72]
	bx	lr
.Ltmp576:
	.size	TIM_DMAConfig, .Ltmp576-TIM_DMAConfig

	.globl	TIM_DMACmd
	.align	2
	.type	TIM_DMACmd,%function
	.code	16                      @ @TIM_DMACmd
	.thumb_func
TIM_DMACmd:
@ BB#0:
	cmp	r2, #0
	ldrh	r2, [r0, #12]
	ite	eq
	biceq.w	r1, r2, r1
	orrne	r1, r2
	strh	r1, [r0, #12]
	bx	lr
.Ltmp577:
	.size	TIM_DMACmd, .Ltmp577-TIM_DMACmd

	.globl	TIM_SelectCCDMA
	.align	2
	.type	TIM_SelectCCDMA,%function
	.code	16                      @ @TIM_SelectCCDMA
	.thumb_func
TIM_SelectCCDMA:
@ BB#0:
	ldrh	r2, [r0, #4]
	cmp	r1, #0
	ite	eq
	biceq	r1, r2, #8
	orrne	r1, r2, #8
	strh	r1, [r0, #4]
	bx	lr
.Ltmp578:
	.size	TIM_SelectCCDMA, .Ltmp578-TIM_SelectCCDMA

	.globl	TIM_InternalClockConfig
	.align	2
	.type	TIM_InternalClockConfig,%function
	.code	16                      @ @TIM_InternalClockConfig
	.thumb_func
TIM_InternalClockConfig:
@ BB#0:
	ldrh	r1, [r0, #8]
	bic	r1, r1, #7
	strh	r1, [r0, #8]
	bx	lr
.Ltmp579:
	.size	TIM_InternalClockConfig, .Ltmp579-TIM_InternalClockConfig

	.globl	TIM_ITRxExternalClockConfig
	.align	2
	.type	TIM_ITRxExternalClockConfig,%function
	.code	16                      @ @TIM_ITRxExternalClockConfig
	.thumb_func
TIM_ITRxExternalClockConfig:
@ BB#0:
	ldrh	r2, [r0, #8]
	bic	r2, r2, #112
	orrs	r1, r2
	strh	r1, [r0, #8]
	ldrh	r1, [r0, #8]
	orr	r1, r1, #7
	strh	r1, [r0, #8]
	bx	lr
.Ltmp580:
	.size	TIM_ITRxExternalClockConfig, .Ltmp580-TIM_ITRxExternalClockConfig

	.globl	TIM_SelectInputTrigger
	.align	2
	.type	TIM_SelectInputTrigger,%function
	.code	16                      @ @TIM_SelectInputTrigger
	.thumb_func
TIM_SelectInputTrigger:
@ BB#0:
	ldrh	r2, [r0, #8]
	bic	r2, r2, #112
	orrs	r1, r2
	strh	r1, [r0, #8]
	bx	lr
.Ltmp581:
	.size	TIM_SelectInputTrigger, .Ltmp581-TIM_SelectInputTrigger

	.globl	TIM_TIxExternalClockConfig
	.align	2
	.type	TIM_TIxExternalClockConfig,%function
	.code	16                      @ @TIM_TIxExternalClockConfig
	.thumb_func
TIM_TIxExternalClockConfig:
@ BB#0:
	push.w	{r11, lr}
	ldrh.w	r12, [r0, #32]
	cmp	r1, #96
	bne	.LBB582_2
@ BB#1:
	bic	r12, r12, #16
	movw	lr, #3327
	strh.w	r12, [r0, #32]
	ldrh.w	r12, [r0, #24]
	and.w	r12, r12, lr
	orr.w	r3, r12, r3, lsl #12
	ldrh.w	r12, [r0, #32]
	orr	r3, r3, #256
	strh	r3, [r0, #24]
	bic	r3, r12, #176
	orr.w	r2, r3, r2, lsl #4
	orr	r2, r2, #16
	b	.LBB582_3
.LBB582_2:
	bic	r12, r12, #1
	strh.w	r12, [r0, #32]
	ldrh.w	r12, [r0, #24]
	bic	r12, r12, #243
	orr.w	r3, r12, r3, lsl #4
	ldrh.w	r12, [r0, #32]
	orr	r3, r3, #1
	strh	r3, [r0, #24]
	bic	r3, r12, #11
	orrs	r2, r3
	orr	r2, r2, #1
.LBB582_3:
	strh	r2, [r0, #32]
	ldrh	r2, [r0, #8]
	bic	r2, r2, #112
	orrs	r1, r2
	strh	r1, [r0, #8]
	ldrh	r1, [r0, #8]
	orr	r1, r1, #7
	strh	r1, [r0, #8]
	pop.w	{r11, pc}
.Ltmp582:
	.size	TIM_TIxExternalClockConfig, .Ltmp582-TIM_TIxExternalClockConfig

	.globl	TIM_ETRClockMode1Config
	.align	2
	.type	TIM_ETRClockMode1Config,%function
	.code	16                      @ @TIM_ETRClockMode1Config
	.thumb_func
TIM_ETRClockMode1Config:
@ BB#0:
	orrs	r1, r2
	ldrh	r2, [r0, #8]
	orr.w	r1, r1, r3, lsl #8
	uxtb	r2, r2
	orrs	r1, r2
	strh	r1, [r0, #8]
	ldrh	r1, [r0, #8]
	orr	r1, r1, #119
	strh	r1, [r0, #8]
	bx	lr
.Ltmp583:
	.size	TIM_ETRClockMode1Config, .Ltmp583-TIM_ETRClockMode1Config

	.globl	TIM_ETRConfig
	.align	2
	.type	TIM_ETRConfig,%function
	.code	16                      @ @TIM_ETRConfig
	.thumb_func
TIM_ETRConfig:
@ BB#0:
	orrs	r1, r2
	ldrh	r2, [r0, #8]
	orr.w	r1, r1, r3, lsl #8
	uxtb	r2, r2
	orrs	r1, r2
	strh	r1, [r0, #8]
	bx	lr
.Ltmp584:
	.size	TIM_ETRConfig, .Ltmp584-TIM_ETRConfig

	.globl	TIM_ETRClockMode2Config
	.align	2
	.type	TIM_ETRClockMode2Config,%function
	.code	16                      @ @TIM_ETRClockMode2Config
	.thumb_func
TIM_ETRClockMode2Config:
@ BB#0:
	orrs	r1, r2
	ldrh	r2, [r0, #8]
	orr.w	r1, r1, r3, lsl #8
	uxtb	r2, r2
	orrs	r1, r2
	strh	r1, [r0, #8]
	ldrh	r1, [r0, #8]
	orr	r1, r1, #16384
	strh	r1, [r0, #8]
	bx	lr
.Ltmp585:
	.size	TIM_ETRClockMode2Config, .Ltmp585-TIM_ETRClockMode2Config

	.globl	TIM_SelectOutputTrigger
	.align	2
	.type	TIM_SelectOutputTrigger,%function
	.code	16                      @ @TIM_SelectOutputTrigger
	.thumb_func
TIM_SelectOutputTrigger:
@ BB#0:
	ldrh	r2, [r0, #4]
	bic	r2, r2, #112
	strh	r2, [r0, #4]
	ldrh	r2, [r0, #4]
	orrs	r1, r2
	strh	r1, [r0, #4]
	bx	lr
.Ltmp586:
	.size	TIM_SelectOutputTrigger, .Ltmp586-TIM_SelectOutputTrigger

	.globl	TIM_SelectSlaveMode
	.align	2
	.type	TIM_SelectSlaveMode,%function
	.code	16                      @ @TIM_SelectSlaveMode
	.thumb_func
TIM_SelectSlaveMode:
@ BB#0:
	ldrh	r2, [r0, #8]
	bic	r2, r2, #7
	strh	r2, [r0, #8]
	ldrh	r2, [r0, #8]
	orrs	r1, r2
	strh	r1, [r0, #8]
	bx	lr
.Ltmp587:
	.size	TIM_SelectSlaveMode, .Ltmp587-TIM_SelectSlaveMode

	.globl	TIM_SelectMasterSlaveMode
	.align	2
	.type	TIM_SelectMasterSlaveMode,%function
	.code	16                      @ @TIM_SelectMasterSlaveMode
	.thumb_func
TIM_SelectMasterSlaveMode:
@ BB#0:
	ldrh	r2, [r0, #8]
	bic	r2, r2, #128
	strh	r2, [r0, #8]
	ldrh	r2, [r0, #8]
	orrs	r1, r2
	strh	r1, [r0, #8]
	bx	lr
.Ltmp588:
	.size	TIM_SelectMasterSlaveMode, .Ltmp588-TIM_SelectMasterSlaveMode

	.globl	TIM_EncoderInterfaceConfig
	.align	2
	.type	TIM_EncoderInterfaceConfig,%function
	.code	16                      @ @TIM_EncoderInterfaceConfig
	.thumb_func
TIM_EncoderInterfaceConfig:
@ BB#0:
	push.w	{r11, lr}
	ldrh.w	r12, [r0, #8]
	bic	r12, r12, #7
	orr.w	r1, r1, r12
	ldrh.w	r12, [r0, #24]
	ldrh.w	lr, [r0, #32]
	strh	r1, [r0, #8]
	movw	r1, #64764
	and.w	r12, r12, r1
	movw	r1, #257
	orr.w	r1, r1, r12
	strh	r1, [r0, #24]
	orr.w	r1, r2, r3, lsl #4
	bic	r2, lr, #34
	orrs	r1, r2
	strh	r1, [r0, #32]
	pop.w	{r11, pc}
.Ltmp589:
	.size	TIM_EncoderInterfaceConfig, .Ltmp589-TIM_EncoderInterfaceConfig

	.globl	TIM_SelectHallSensor
	.align	2
	.type	TIM_SelectHallSensor,%function
	.code	16                      @ @TIM_SelectHallSensor
	.thumb_func
TIM_SelectHallSensor:
@ BB#0:
	ldrh	r2, [r0, #4]
	cmp	r1, #0
	ite	eq
	biceq	r1, r2, #128
	orrne	r1, r2, #128
	strh	r1, [r0, #4]
	bx	lr
.Ltmp590:
	.size	TIM_SelectHallSensor, .Ltmp590-TIM_SelectHallSensor

	.globl	TIM_RemapConfig
	.align	2
	.type	TIM_RemapConfig,%function
	.code	16                      @ @TIM_RemapConfig
	.thumb_func
TIM_RemapConfig:
@ BB#0:
	strh.w	r1, [r0, #80]
	bx	lr
.Ltmp591:
	.size	TIM_RemapConfig, .Ltmp591-TIM_RemapConfig

	.globl	USART_DeInit
	.align	2
	.type	USART_DeInit,%function
	.code	16                      @ @USART_DeInit
	.thumb_func
USART_DeInit:
@ BB#0:
	push	{r7, lr}
	movw	r1, #18431
	mov	r7, sp
	movt	r1, #16384
	cmp	r0, r1
	bgt	.LBB592_3
@ BB#1:
	movw	r1, #17408
	movt	r1, #16384
	cmp	r0, r1
	bne	.LBB592_16
@ BB#2:
	mov.w	r0, #131072
	movs	r1, #1
	bl	RCC_APB1PeriphResetCmd
	mov.w	r0, #131072
	b	.LBB592_13
.LBB592_3:
	movw	r1, #19455
	movt	r1, #16384
	cmp	r0, r1
	bgt	.LBB592_6
@ BB#4:
	movw	r1, #18432
	movt	r1, #16384
	cmp	r0, r1
	bne	.LBB592_16
@ BB#5:
	mov.w	r0, #262144
	movs	r1, #1
	bl	RCC_APB1PeriphResetCmd
	mov.w	r0, #262144
	b	.LBB592_13
.LBB592_6:
	movw	r1, #20479
	movt	r1, #16384
	cmp	r0, r1
	bgt	.LBB592_9
@ BB#7:
	movw	r1, #19456
	movt	r1, #16384
	cmp	r0, r1
	bne	.LBB592_16
@ BB#8:
	mov.w	r0, #524288
	movs	r1, #1
	bl	RCC_APB1PeriphResetCmd
	mov.w	r0, #524288
	b	.LBB592_13
.LBB592_9:
	movw	r1, #20480
	movt	r1, #16384
	cmp	r0, r1
	beq	.LBB592_12
@ BB#10:
	movw	r1, #5120
	movt	r1, #16385
	cmp	r0, r1
	bne	.LBB592_14
@ BB#11:
	movs	r0, #32
	movs	r1, #1
	bl	RCC_APB2PeriphResetCmd
	movs	r0, #32
	b	.LBB592_15
.LBB592_12:
	mov.w	r0, #1048576
	movs	r1, #1
	bl	RCC_APB1PeriphResetCmd
	mov.w	r0, #1048576
.LBB592_13:
	movs	r1, #0
	bl	RCC_APB1PeriphResetCmd
	pop	{r7, pc}
.LBB592_14:
	movw	r1, #4096
	movt	r1, #16385
	cmp	r0, r1
	it	ne
	popne	{r7, pc}
	movs	r0, #16
	movs	r1, #1
	bl	RCC_APB2PeriphResetCmd
	movs	r0, #16
.LBB592_15:
	movs	r1, #0
	bl	RCC_APB2PeriphResetCmd
.LBB592_16:
	pop	{r7, pc}
.Ltmp592:
	.size	USART_DeInit, .Ltmp592-USART_DeInit

	.globl	USART_Init
	.align	2
	.type	USART_Init,%function
	.code	16                      @ @USART_Init
	.thumb_func
USART_Init:
@ BB#0:
	push	{r4, r5, r7, lr}
	add	r7, sp, #8
	sub	sp, #16
	mov	r4, r0
	mov	r5, r1
	ldrh	r0, [r4, #16]
	ldrh	r1, [r5, #6]
	bic	r0, r0, #12288
	orrs	r0, r1
	movw	r1, #59891
	strh	r0, [r4, #16]
	ldrh	r0, [r4, #12]
	ldrh	r2, [r5, #8]
	ands	r0, r1
	ldrh	r1, [r5, #4]
	orrs	r1, r2
	ldrh	r2, [r5, #10]
	orrs	r1, r2
	orrs	r0, r1
	strh	r0, [r4, #12]
	ldrh	r0, [r4, #20]
	ldrh	r1, [r5, #12]
	bic	r0, r0, #768
	orrs	r0, r1
	strh	r0, [r4, #20]
	mov	r0, sp
	bl	RCC_GetClocksFreq
	movw	r1, #5120
	orr	r0, r4, #1024
	movs	r2, #2
	movt	r1, #16385
	cmp	r0, r1
	mov.w	r1, #25
	ite	ne
	ldrne	r0, [sp, #8]
	ldreq	r0, [sp, #12]
	muls	r0, r1, r0
	ldrsh.w	r1, [r4, #12]
	cmp	r1, #0
	it	lt
	movlt	r2, #1
	ldr	r1, [r5]
	lsls	r1, r2
	udiv	r0, r0, r1
	movw	r1, #34079
	movt	r1, #20971
	umull	r2, r3, r0, r1
	lsrs	r3, r3, #5
	mvn	r2, #99
	mla	r2, r3, r2, r0
	lsls	r0, r3, #4
	ldrsh.w	r3, [r4, #12]
	cmp.w	r3, #-1
	ble	.LBB593_2
@ BB#1:
	movs	r3, #50
	add.w	r2, r3, r2, lsl #4
	umull	r1, r2, r2, r1
	ubfx	r1, r2, #5, #4
	b	.LBB593_3
.LBB593_2:
	movs	r3, #50
	add.w	r2, r3, r2, lsl #3
	umull	r1, r2, r2, r1
	ubfx	r1, r2, #5, #3
.LBB593_3:
	orrs	r0, r1
	strh	r0, [r4, #8]
	add	sp, #16
	pop	{r4, r5, r7, pc}
.Ltmp593:
	.size	USART_Init, .Ltmp593-USART_Init

	.globl	USART_StructInit
	.align	2
	.type	USART_StructInit,%function
	.code	16                      @ @USART_StructInit
	.thumb_func
USART_StructInit:
@ BB#0:
	mov.w	r1, #9600
	movs	r2, #12
	str	r1, [r0]
	movs	r1, #0
	strh	r1, [r0, #6]
	strh	r1, [r0, #4]
	strh	r2, [r0, #10]
	strh	r1, [r0, #8]
	strh	r1, [r0, #12]
	bx	lr
.Ltmp594:
	.size	USART_StructInit, .Ltmp594-USART_StructInit

	.globl	USART_ClockInit
	.align	2
	.type	USART_ClockInit,%function
	.code	16                      @ @USART_ClockInit
	.thumb_func
USART_ClockInit:
@ BB#0:
	ldrh.w	r12, [r0, #16]
	ldrh	r3, [r1]
	ldrh	r2, [r1, #2]
	orrs	r2, r3
	ldrh	r3, [r1, #4]
	ldrh	r1, [r1, #6]
	orrs	r2, r3
	orrs	r1, r2
	bic	r2, r12, #3840
	orrs	r1, r2
	strh	r1, [r0, #16]
	bx	lr
.Ltmp595:
	.size	USART_ClockInit, .Ltmp595-USART_ClockInit

	.globl	USART_ClockStructInit
	.align	2
	.type	USART_ClockStructInit,%function
	.code	16                      @ @USART_ClockStructInit
	.thumb_func
USART_ClockStructInit:
@ BB#0:
	movs	r1, #0
	strh	r1, [r0, #2]
	strh	r1, [r0]
	strh	r1, [r0, #6]
	strh	r1, [r0, #4]
	bx	lr
.Ltmp596:
	.size	USART_ClockStructInit, .Ltmp596-USART_ClockStructInit

	.globl	USART_Cmd
	.align	2
	.type	USART_Cmd,%function
	.code	16                      @ @USART_Cmd
	.thumb_func
USART_Cmd:
@ BB#0:
	ldrh	r2, [r0, #12]
	cmp	r1, #0
	ite	eq
	biceq	r1, r2, #8192
	orrne	r1, r2, #8192
	strh	r1, [r0, #12]
	bx	lr
.Ltmp597:
	.size	USART_Cmd, .Ltmp597-USART_Cmd

	.globl	USART_SetPrescaler
	.align	2
	.type	USART_SetPrescaler,%function
	.code	16                      @ @USART_SetPrescaler
	.thumb_func
USART_SetPrescaler:
@ BB#0:
	ldrh	r2, [r0, #24]
	bic	r2, r2, #255
	strh	r2, [r0, #24]
	ldrh	r2, [r0, #24]
	orrs	r1, r2
	strh	r1, [r0, #24]
	bx	lr
.Ltmp598:
	.size	USART_SetPrescaler, .Ltmp598-USART_SetPrescaler

	.globl	USART_OverSampling8Cmd
	.align	2
	.type	USART_OverSampling8Cmd,%function
	.code	16                      @ @USART_OverSampling8Cmd
	.thumb_func
USART_OverSampling8Cmd:
@ BB#0:
	ldrh	r2, [r0, #12]
	cmp	r1, #0
	ittt	eq
	bfceq	r2, #15, #17
	strheq	r2, [r0, #12]
	bxeq	lr
	orr	r1, r2, #32768
	strh	r1, [r0, #12]
	bx	lr
.Ltmp599:
	.size	USART_OverSampling8Cmd, .Ltmp599-USART_OverSampling8Cmd

	.globl	USART_OneBitMethodCmd
	.align	2
	.type	USART_OneBitMethodCmd,%function
	.code	16                      @ @USART_OneBitMethodCmd
	.thumb_func
USART_OneBitMethodCmd:
@ BB#0:
	ldrh	r2, [r0, #20]
	cmp	r1, #0
	ite	eq
	biceq	r1, r2, #2048
	orrne	r1, r2, #2048
	strh	r1, [r0, #20]
	bx	lr
.Ltmp600:
	.size	USART_OneBitMethodCmd, .Ltmp600-USART_OneBitMethodCmd

	.globl	USART_SendData
	.align	2
	.type	USART_SendData,%function
	.code	16                      @ @USART_SendData
	.thumb_func
USART_SendData:
@ BB#0:
	bfc	r1, #9, #23
	strh	r1, [r0, #4]
	bx	lr
.Ltmp601:
	.size	USART_SendData, .Ltmp601-USART_SendData

	.globl	USART_ReceiveData
	.align	2
	.type	USART_ReceiveData,%function
	.code	16                      @ @USART_ReceiveData
	.thumb_func
USART_ReceiveData:
@ BB#0:
	ldrh	r0, [r0, #4]
	bfc	r0, #9, #23
	bx	lr
.Ltmp602:
	.size	USART_ReceiveData, .Ltmp602-USART_ReceiveData

	.globl	USART_SetAddress
	.align	2
	.type	USART_SetAddress,%function
	.code	16                      @ @USART_SetAddress
	.thumb_func
USART_SetAddress:
@ BB#0:
	ldrh	r2, [r0, #16]
	bic	r2, r2, #15
	strh	r2, [r0, #16]
	ldrh	r2, [r0, #16]
	orrs	r1, r2
	strh	r1, [r0, #16]
	bx	lr
.Ltmp603:
	.size	USART_SetAddress, .Ltmp603-USART_SetAddress

	.globl	USART_ReceiverWakeUpCmd
	.align	2
	.type	USART_ReceiverWakeUpCmd,%function
	.code	16                      @ @USART_ReceiverWakeUpCmd
	.thumb_func
USART_ReceiverWakeUpCmd:
@ BB#0:
	ldrh	r2, [r0, #12]
	cmp	r1, #0
	ite	eq
	biceq	r1, r2, #2
	orrne	r1, r2, #2
	strh	r1, [r0, #12]
	bx	lr
.Ltmp604:
	.size	USART_ReceiverWakeUpCmd, .Ltmp604-USART_ReceiverWakeUpCmd

	.globl	USART_WakeUpConfig
	.align	2
	.type	USART_WakeUpConfig,%function
	.code	16                      @ @USART_WakeUpConfig
	.thumb_func
USART_WakeUpConfig:
@ BB#0:
	ldrh	r2, [r0, #12]
	bic	r2, r2, #2048
	strh	r2, [r0, #12]
	ldrh	r2, [r0, #12]
	orrs	r1, r2
	strh	r1, [r0, #12]
	bx	lr
.Ltmp605:
	.size	USART_WakeUpConfig, .Ltmp605-USART_WakeUpConfig

	.globl	USART_LINBreakDetectLengthConfig
	.align	2
	.type	USART_LINBreakDetectLengthConfig,%function
	.code	16                      @ @USART_LINBreakDetectLengthConfig
	.thumb_func
USART_LINBreakDetectLengthConfig:
@ BB#0:
	ldrh	r2, [r0, #16]
	bic	r2, r2, #32
	strh	r2, [r0, #16]
	ldrh	r2, [r0, #16]
	orrs	r1, r2
	strh	r1, [r0, #16]
	bx	lr
.Ltmp606:
	.size	USART_LINBreakDetectLengthConfig, .Ltmp606-USART_LINBreakDetectLengthConfig

	.globl	USART_LINCmd
	.align	2
	.type	USART_LINCmd,%function
	.code	16                      @ @USART_LINCmd
	.thumb_func
USART_LINCmd:
@ BB#0:
	ldrh	r2, [r0, #16]
	cmp	r1, #0
	ite	eq
	biceq	r1, r2, #16384
	orrne	r1, r2, #16384
	strh	r1, [r0, #16]
	bx	lr
.Ltmp607:
	.size	USART_LINCmd, .Ltmp607-USART_LINCmd

	.globl	USART_SendBreak
	.align	2
	.type	USART_SendBreak,%function
	.code	16                      @ @USART_SendBreak
	.thumb_func
USART_SendBreak:
@ BB#0:
	ldrh	r1, [r0, #12]
	orr	r1, r1, #1
	strh	r1, [r0, #12]
	bx	lr
.Ltmp608:
	.size	USART_SendBreak, .Ltmp608-USART_SendBreak

	.globl	USART_HalfDuplexCmd
	.align	2
	.type	USART_HalfDuplexCmd,%function
	.code	16                      @ @USART_HalfDuplexCmd
	.thumb_func
USART_HalfDuplexCmd:
@ BB#0:
	ldrh	r2, [r0, #20]
	cmp	r1, #0
	ite	eq
	biceq	r1, r2, #8
	orrne	r1, r2, #8
	strh	r1, [r0, #20]
	bx	lr
.Ltmp609:
	.size	USART_HalfDuplexCmd, .Ltmp609-USART_HalfDuplexCmd

	.globl	USART_SetGuardTime
	.align	2
	.type	USART_SetGuardTime,%function
	.code	16                      @ @USART_SetGuardTime
	.thumb_func
USART_SetGuardTime:
@ BB#0:
	ldrh	r2, [r0, #24]
	uxtb	r2, r2
	strh	r2, [r0, #24]
	ldrh	r2, [r0, #24]
	orr.w	r1, r2, r1, lsl #8
	strh	r1, [r0, #24]
	bx	lr
.Ltmp610:
	.size	USART_SetGuardTime, .Ltmp610-USART_SetGuardTime

	.globl	USART_SmartCardCmd
	.align	2
	.type	USART_SmartCardCmd,%function
	.code	16                      @ @USART_SmartCardCmd
	.thumb_func
USART_SmartCardCmd:
@ BB#0:
	ldrh	r2, [r0, #20]
	cmp	r1, #0
	ite	eq
	biceq	r1, r2, #32
	orrne	r1, r2, #32
	strh	r1, [r0, #20]
	bx	lr
.Ltmp611:
	.size	USART_SmartCardCmd, .Ltmp611-USART_SmartCardCmd

	.globl	USART_SmartCardNACKCmd
	.align	2
	.type	USART_SmartCardNACKCmd,%function
	.code	16                      @ @USART_SmartCardNACKCmd
	.thumb_func
USART_SmartCardNACKCmd:
@ BB#0:
	ldrh	r2, [r0, #20]
	cmp	r1, #0
	ite	eq
	biceq	r1, r2, #16
	orrne	r1, r2, #16
	strh	r1, [r0, #20]
	bx	lr
.Ltmp612:
	.size	USART_SmartCardNACKCmd, .Ltmp612-USART_SmartCardNACKCmd

	.globl	USART_IrDAConfig
	.align	2
	.type	USART_IrDAConfig,%function
	.code	16                      @ @USART_IrDAConfig
	.thumb_func
USART_IrDAConfig:
@ BB#0:
	ldrh	r2, [r0, #20]
	bic	r2, r2, #4
	strh	r2, [r0, #20]
	ldrh	r2, [r0, #20]
	orrs	r1, r2
	strh	r1, [r0, #20]
	bx	lr
.Ltmp613:
	.size	USART_IrDAConfig, .Ltmp613-USART_IrDAConfig

	.globl	USART_IrDACmd
	.align	2
	.type	USART_IrDACmd,%function
	.code	16                      @ @USART_IrDACmd
	.thumb_func
USART_IrDACmd:
@ BB#0:
	ldrh	r2, [r0, #20]
	cmp	r1, #0
	ite	eq
	biceq	r1, r2, #2
	orrne	r1, r2, #2
	strh	r1, [r0, #20]
	bx	lr
.Ltmp614:
	.size	USART_IrDACmd, .Ltmp614-USART_IrDACmd

	.globl	USART_DMACmd
	.align	2
	.type	USART_DMACmd,%function
	.code	16                      @ @USART_DMACmd
	.thumb_func
USART_DMACmd:
@ BB#0:
	cmp	r2, #0
	ldrh	r2, [r0, #20]
	ite	eq
	biceq.w	r1, r2, r1
	orrne	r1, r2
	strh	r1, [r0, #20]
	bx	lr
.Ltmp615:
	.size	USART_DMACmd, .Ltmp615-USART_DMACmd

	.globl	USART_ITConfig
	.align	2
	.type	USART_ITConfig,%function
	.code	16                      @ @USART_ITConfig
	.thumb_func
USART_ITConfig:
@ BB#0:
	and	r12, r1, #31
	movs	r3, #1
	ubfx	r1, r1, #5, #3
	lsl.w	r3, r3, r12
	cmp	r1, #2
	bne	.LBB616_2
@ BB#1:
	adds	r0, #16
	b	.LBB616_3
.LBB616_2:
	cmp	r1, #1
	ite	ne
	addne	r0, #20
	addeq	r0, #12
.LBB616_3:
	ldr	r1, [r0]
	cmp	r2, #0
	ite	eq
	biceq	r1, r3
	orrne	r1, r3
	str	r1, [r0]
	bx	lr
.Ltmp616:
	.size	USART_ITConfig, .Ltmp616-USART_ITConfig

	.globl	USART_GetFlagStatus
	.align	2
	.type	USART_GetFlagStatus,%function
	.code	16                      @ @USART_GetFlagStatus
	.thumb_func
USART_GetFlagStatus:
@ BB#0:
	ldrh	r0, [r0]
	ands	r0, r1
	it	ne
	movne	r0, #1
	bx	lr
.Ltmp617:
	.size	USART_GetFlagStatus, .Ltmp617-USART_GetFlagStatus

	.globl	USART_ClearFlag
	.align	2
	.type	USART_ClearFlag,%function
	.code	16                      @ @USART_ClearFlag
	.thumb_func
USART_ClearFlag:
@ BB#0:
	mvns	r1, r1
	strh	r1, [r0]
	bx	lr
.Ltmp618:
	.size	USART_ClearFlag, .Ltmp618-USART_ClearFlag

	.globl	USART_GetITStatus
	.align	2
	.type	USART_GetITStatus,%function
	.code	16                      @ @USART_GetITStatus
	.thumb_func
USART_GetITStatus:
@ BB#0:
	and	r2, r1, #31
	movs	r3, #1
	lsl.w	r2, r3, r2
	ubfx	r3, r1, #5, #3
	cmp	r3, #2
	bne	.LBB619_2
@ BB#1:
	ldrh	r3, [r0, #16]
	b	.LBB619_3
.LBB619_2:
	cmp	r3, #1
	ite	ne
	ldrhne	r3, [r0, #20]
	ldrheq	r3, [r0, #12]
.LBB619_3:
	ands	r2, r3
	lsr.w	r1, r1, #8
	mov.w	r3, #1
	it	ne
	movne	r2, #1
	ldrh	r0, [r0]
	lsl.w	r1, r3, r1
	ands	r0, r1
	it	ne
	movne	r0, #1
	ands	r0, r2
	bx	lr
.Ltmp619:
	.size	USART_GetITStatus, .Ltmp619-USART_GetITStatus

	.globl	USART_ClearITPendingBit
	.align	2
	.type	USART_ClearITPendingBit,%function
	.code	16                      @ @USART_ClearITPendingBit
	.thumb_func
USART_ClearITPendingBit:
@ BB#0:
	lsrs	r1, r1, #8
	movs	r2, #1
	lsl.w	r1, r2, r1
	mvns	r1, r1
	strh	r1, [r0]
	bx	lr
.Ltmp620:
	.size	USART_ClearITPendingBit, .Ltmp620-USART_ClearITPendingBit

	.globl	WWDG_DeInit
	.align	2
	.type	WWDG_DeInit,%function
	.code	16                      @ @WWDG_DeInit
	.thumb_func
WWDG_DeInit:
@ BB#0:
	push	{r7, lr}
	mov.w	r0, #2048
	movs	r1, #1
	mov	r7, sp
	bl	RCC_APB1PeriphResetCmd
	mov.w	r0, #2048
	movs	r1, #0
	bl	RCC_APB1PeriphResetCmd
	pop	{r7, pc}
.Ltmp621:
	.size	WWDG_DeInit, .Ltmp621-WWDG_DeInit

	.globl	WWDG_SetPrescaler
	.align	2
	.type	WWDG_SetPrescaler,%function
	.code	16                      @ @WWDG_SetPrescaler
	.thumb_func
WWDG_SetPrescaler:
@ BB#0:
	movw	r1, #11268
	movt	r1, #16384
	ldr	r2, [r1]
	bic	r2, r2, #384
	orrs	r0, r2
	str	r0, [r1]
	bx	lr
.Ltmp622:
	.size	WWDG_SetPrescaler, .Ltmp622-WWDG_SetPrescaler

	.globl	WWDG_SetWindowValue
	.align	2
	.type	WWDG_SetWindowValue,%function
	.code	16                      @ @WWDG_SetWindowValue
	.thumb_func
WWDG_SetWindowValue:
@ BB#0:
	sub	sp, #8
	movs	r1, #0
	and	r0, r0, #127
	str	r1, [sp, #4]
	movw	r1, #11268
	movt	r1, #16384
	ldr	r2, [r1]
	bic	r2, r2, #127
	str	r2, [sp, #4]
	ldr	r2, [sp, #4]
	orrs	r0, r2
	str	r0, [sp, #4]
	ldr	r0, [sp, #4]
	str	r0, [r1]
	add	sp, #8
	bx	lr
.Ltmp623:
	.size	WWDG_SetWindowValue, .Ltmp623-WWDG_SetWindowValue

	.globl	WWDG_EnableIT
	.align	2
	.type	WWDG_EnableIT,%function
	.code	16                      @ @WWDG_EnableIT
	.thumb_func
WWDG_EnableIT:
@ BB#0:
	movw	r0, #32932
	movs	r1, #1
	movt	r0, #16901
	str	r1, [r0]
	bx	lr
.Ltmp624:
	.size	WWDG_EnableIT, .Ltmp624-WWDG_EnableIT

	.globl	WWDG_SetCounter
	.align	2
	.type	WWDG_SetCounter,%function
	.code	16                      @ @WWDG_SetCounter
	.thumb_func
WWDG_SetCounter:
@ BB#0:
	movw	r1, #11264
	and	r0, r0, #127
	movt	r1, #16384
	str	r0, [r1]
	bx	lr
.Ltmp625:
	.size	WWDG_SetCounter, .Ltmp625-WWDG_SetCounter

	.globl	WWDG_Enable
	.align	2
	.type	WWDG_Enable,%function
	.code	16                      @ @WWDG_Enable
	.thumb_func
WWDG_Enable:
@ BB#0:
	movw	r1, #11264
	orr	r0, r0, #128
	movt	r1, #16384
	str	r0, [r1]
	bx	lr
.Ltmp626:
	.size	WWDG_Enable, .Ltmp626-WWDG_Enable

	.globl	WWDG_GetFlagStatus
	.align	2
	.type	WWDG_GetFlagStatus,%function
	.code	16                      @ @WWDG_GetFlagStatus
	.thumb_func
WWDG_GetFlagStatus:
@ BB#0:
	movw	r0, #11272
	movt	r0, #16384
	ldr	r0, [r0]
	cmp	r0, #0
	it	ne
	movne	r0, #1
	bx	lr
.Ltmp627:
	.size	WWDG_GetFlagStatus, .Ltmp627-WWDG_GetFlagStatus

	.globl	WWDG_ClearFlag
	.align	2
	.type	WWDG_ClearFlag,%function
	.code	16                      @ @WWDG_ClearFlag
	.thumb_func
WWDG_ClearFlag:
@ BB#0:
	movw	r0, #11272
	movs	r1, #0
	movt	r0, #16384
	str	r1, [r0]
	bx	lr
.Ltmp628:
	.size	WWDG_ClearFlag, .Ltmp628-WWDG_ClearFlag

	.globl	SystemInit
	.align	2
	.type	SystemInit,%function
	.code	16                      @ @SystemInit
	.thumb_func
SystemInit:
@ BB#0:
	push.w	{r11, lr}
	sub	sp, #8
	movw	r1, #14336
	mov.w	r12, #0
	movw	r3, #65535
	movw	lr, #14340
	movt	r1, #16386
	movt	r3, #65270
	movt	lr, #16386
	ldr	r0, [r1]
	orr	r0, r0, #1
	str	r0, [r1]
	movw	r0, #14344
	movt	r0, #16386
	str.w	r12, [r0]
	ldr	r2, [r1]
	ands	r2, r3
	movw	r3, #12304
	movt	r3, #9216
	str	r2, [r1]
	str.w	r3, [lr]
	ldr	r3, [r1]
	bic	r3, r3, #262144
	str	r3, [r1]
	movw	r3, #14348
	movt	r3, #16386
	str.w	r12, [r3]
	str.w	r12, [sp, #4]
	str.w	r12, [sp]
	ldr	r3, [r1]
	orr	r3, r3, #65536
	str	r3, [r1]
.LBB629_1:                              @ =>This Inner Loop Header: Depth=1
	ldr	r3, [r1]
	and	r3, r3, #131072
	str	r3, [sp]
	ldr	r3, [sp, #4]
	adds	r3, #1
	str	r3, [sp, #4]
	ldr	r3, [sp]
	cbnz	r3, .LBB629_3
@ BB#2:                                 @   in Loop: Header=BB629_1 Depth=1
	ldr	r3, [sp, #4]
	cmp.w	r3, #1280
	bne	.LBB629_1
.LBB629_3:                              @ %.critedge.i
	ldr	r3, [r1]
	tst.w	r3, #131072
	ite	eq
	moveq	r3, #0
	movne	r3, #1
	str	r3, [sp]
	ldr	r3, [sp]
	cmp	r3, #1
	bne	.LBB629_8
@ BB#4:
	movw	r3, #14400
	movt	r3, #16386
	ldr	r2, [r3]
	orr	r2, r2, #268435456
	str	r2, [r3]
	movw	r2, #28672
	movt	r2, #16384
	ldr	r3, [r2]
	orr	r3, r3, #16384
	str	r3, [r2]
	ldr	r2, [r0]
	str	r2, [r0]
	ldr	r2, [r0]
	orr	r2, r2, #32768
	str	r2, [r0]
	ldr	r2, [r0]
	orr	r2, r2, #5120
	str	r2, [r0]
	movw	r2, #21529
	movt	r2, #1856
	str.w	r2, [lr]
	ldr	r2, [r1]
	orr	r2, r2, #16777216
	str	r2, [r1]
.LBB629_5:                              @ =>This Inner Loop Header: Depth=1
	ldr	r2, [r1]
	tst.w	r2, #33554432
	beq	.LBB629_5
@ BB#6:
	movw	r1, #15360
	movw	r2, #1541
	movt	r1, #16386
	str	r2, [r1]
	ldr	r1, [r0]
	bic	r1, r1, #3
	str	r1, [r0]
	ldr	r1, [r0]
	orr	r1, r1, #2
	str	r1, [r0]
.LBB629_7:                              @ =>This Inner Loop Header: Depth=1
	ldr	r1, [r0]
	and	r1, r1, #12
	cmp	r1, #8
	bne	.LBB629_7
.LBB629_8:                              @ %SetSysClock.exit
	movw	r0, #60680
	mov.w	r1, #134217728
	movt	r0, #57344
	str	r1, [r0]
	add	sp, #8
	pop.w	{r11, pc}
.Ltmp629:
	.size	SystemInit, .Ltmp629-SystemInit

	.globl	SystemCoreClockUpdate
	.align	2
	.type	SystemCoreClockUpdate,%function
	.code	16                      @ @SystemCoreClockUpdate
	.thumb_func
SystemCoreClockUpdate:
@ BB#0:
	movw	r0, #14344
	movt	r0, #16386
	ldr	r1, [r0]
	and	r1, r1, #12
	cmp	r1, #8
	beq	.LBB630_3
@ BB#1:
	cmp	r1, #4
	bne	.LBB630_5
@ BB#2:
	movw	r1, :lower16:SystemCoreClock
	movw	r2, #4608
	movt	r1, :upper16:SystemCoreClock
	movt	r2, #122
	str	r2, [r1]
	b	.LBB630_8
.LBB630_3:
	movw	r1, #14340
	movt	r1, #16386
	ldr	r3, [r1]
	ldr	r2, [r1]
	and	r2, r2, #63
	tst.w	r3, #4194304
	beq	.LBB630_6
@ BB#4:
	movw	r3, #4608
	movt	r3, #122
	b	.LBB630_7
.LBB630_5:
	movw	r2, #9216
	cmp	r1, #0
	movw	r1, :lower16:SystemCoreClock
	movt	r1, :upper16:SystemCoreClock
	movt	r2, #244
	str	r2, [r1]
	b	.LBB630_8
.LBB630_6:
	movw	r3, #9216
	movt	r3, #244
.LBB630_7:
	udiv	r2, r3, r2
	ldr	r3, [r1]
	ubfx	r3, r3, #6, #9
	ldr	r1, [r1]
	muls	r2, r3, r2
	movs	r3, #2
	ubfx	r1, r1, #16, #2
	add.w	r1, r3, r1, lsl #1
	udiv	r1, r2, r1
	movw	r2, :lower16:SystemCoreClock
	movt	r2, :upper16:SystemCoreClock
	str	r1, [r2]
.LBB630_8:
	ldr	r0, [r0]
	movw	r1, :lower16:AHBPrescTable
	movt	r1, :upper16:AHBPrescTable
	ubfx	r0, r0, #4, #4
	ldrb	r0, [r1, r0]
	movw	r1, :lower16:SystemCoreClock
	movt	r1, :upper16:SystemCoreClock
	ldr	r2, [r1]
	lsr.w	r0, r2, r0
	str	r0, [r1]
	bx	lr
.Ltmp630:
	.size	SystemCoreClockUpdate, .Ltmp630-SystemCoreClockUpdate

	.globl	USART1_init
	.align	2
	.type	USART1_init,%function
	.code	16                      @ @USART1_init
	.thumb_func
USART1_init:
@ BB#0:
	push.w	{r4, r5, r6, r7, r8, lr}
	add	r7, sp, #12
	sub	sp, #48
	mov	r4, r0
	movs	r0, #2
	movs	r1, #1
	movs	r6, #2
	mov.w	r8, #1
	bl	RCC_AHB1PeriphClockCmd
	movw	r5, #1024
	movs	r1, #6
	movs	r2, #7
	movt	r5, #16386
	mov	r0, r5
	bl	GPIO_PinAFConfig
	mov	r0, r5
	movs	r1, #7
	movs	r2, #7
	bl	GPIO_PinAFConfig
	movs	r0, #192
	add	r1, sp, #28
	str	r0, [sp, #28]
	str	r6, [sp, #36]
	str	r6, [sp, #32]
	movs	r6, #0
	mov	r0, r5
	str	r6, [sp, #40]
	str.w	r8, [sp, #44]
	bl	GPIO_Init
	movs	r0, #16
	movs	r1, #1
	bl	RCC_APB2PeriphClockCmd
	str	r4, [sp, #12]
	movw	r4, #4096
	movs	r0, #12
	strh.w	r6, [sp, #16]
	strh.w	r6, [sp, #18]
	strh.w	r6, [sp, #20]
	strh.w	r6, [sp, #24]
	add	r1, sp, #12
	movt	r4, #16385
	strh.w	r0, [sp, #22]
	mov	r0, r4
	bl	USART_Init
	mov	r0, r4
	movw	r1, #1317
	movs	r2, #1
	bl	USART_ITConfig
	movs	r0, #37
	strb.w	r0, [sp, #4]
	add	r0, sp, #4
	strb.w	r6, [sp, #5]
	strb.w	r6, [sp, #6]
	str.w	r8, [sp, #8]
	bl	NVIC_Init
	mov	r0, r4
	movs	r1, #1
	bl	USART_Cmd
	add	sp, #48
	pop.w	{r4, r5, r6, r7, r8, pc}
.Ltmp631:
	.size	USART1_init, .Ltmp631-USART1_init

	.globl	USART1_IRQHandler
	.align	2
	.type	USART1_IRQHandler,%function
	.code	16                      @ @USART1_IRQHandler
	.thumb_func
USART1_IRQHandler:
@ BB#0:
	push.w	{r4, r7, r11, lr}
	movw	r0, #4096
	movw	r1, #1317
	add	r7, sp, #4
	movt	r0, #16385
	bl	USART_GetITStatus
	cmp	r0, #1
	it	ne
	popne.w	{r4, r7, r11, pc}
	movw	r4, :lower16:usart1_rx_event
	movs	r0, #0
	movt	r4, :upper16:usart1_rx_event
	str	r0, [r4]
	movw	r0, #4096
	movt	r0, #16385
	bl	USART_ReceiveData
	movw	r1, :lower16:USART1_IRQHandler.cnt
	uxtb	r3, r0
	movt	r1, :upper16:USART1_IRQHandler.cnt
	cmp	r3, #10
	ldrb	r2, [r1]
	bne	.LBB632_4
@ BB#1:
	cmp	r2, #98
	bhi	.LBB632_6
@ BB#2:                                 @ %.lr.ph
	movw	r0, :lower16:usart1_rx_string_arr
	movs	r3, #0
	movt	r0, :upper16:usart1_rx_string_arr
.LBB632_3:                              @ =>This Inner Loop Header: Depth=1
	strb	r3, [r0, r2]
	adds	r2, #1
	cmp	r2, #99
	blt	.LBB632_3
	b	.LBB632_6
.LBB632_4:
	cmp	r2, #98
	bhi	.LBB632_6
@ BB#5:
	movw	r3, :lower16:usart1_rx_string_arr
	movt	r3, :upper16:usart1_rx_string_arr
	strb	r0, [r3, r2]
	ldrb	r0, [r1]
	adds	r0, #1
	strb	r0, [r1]
	pop.w	{r4, r7, r11, pc}
.LBB632_6:                              @ %._crit_edge
	movs	r0, #0
	strb	r0, [r1]
	movs	r0, #1
	str	r0, [r4]
	pop.w	{r4, r7, r11, pc}
.Ltmp632:
	.size	USART1_IRQHandler, .Ltmp632-USART1_IRQHandler

	.type	delay,%object           @ @delay
	.bss
	.globl	delay
	.align	2
delay:
	.byte	0                       @ 0x0
	.size	delay, 1

	.type	delay_max,%object       @ @delay_max
	.globl	delay_max
	.align	2
delay_max:
	.byte	0                       @ 0x0
	.size	delay_max, 1

	.type	delay_postavljen,%object @ @delay_postavljen
	.globl	delay_postavljen
	.align	2
delay_postavljen:
	.byte	0                       @ 0x0
	.size	delay_postavljen, 1

	.type	variable_delay,%object  @ @variable_delay
	.globl	variable_delay
	.align	2
variable_delay:
	.byte	0                       @ 0x0
	.size	variable_delay, 1

	.type	.L.str,%object          @ @.str
	.section	.rodata.str1.1,"aMS",%progbits,1
.L.str:
	.asciz	"PD13"
	.size	.L.str, 5

	.type	.L.str1,%object         @ @.str1
.L.str1:
	.asciz	"PD14"
	.size	.L.str1, 5

	.type	.L.str2,%object         @ @.str2
.L.str2:
	.asciz	"PD15"
	.size	.L.str2, 5

	.type	.L.str3,%object         @ @.str3
	.section	.rodata,"a",%progbits
.L.str3:
	.asciz	"PD12"
	.size	.L.str3, 5

	.type	delay_flag,%object      @ @delay_flag
	.comm	delay_flag,4,4
	.type	.L.str4,%object         @ @.str4
	.section	.rodata.str1.1,"aMS",%progbits,1
.L.str4:
	.asciz	"----- clock print: ---------------------------------\n"
	.size	.L.str4, 54

	.type	.L.str15,%object        @ @.str15
.L.str15:
	.asciz	"SystemCoreClock: %lu MHz\n"
	.size	.L.str15, 26

	.type	.L.str26,%object        @ @.str26
.L.str26:
	.asciz	"define HSI: %lu MHz\n"
	.size	.L.str26, 21

	.type	.L.str37,%object        @ @.str37
.L.str37:
	.asciz	"define HSE: %lu MHz\n"
	.size	.L.str37, 21

	.type	.L.str48,%object        @ @.str48
.L.str48:
	.asciz	"RCC_ClocksStatus.SYSCLK_Frequency:\t%lu MHz\n"
	.size	.L.str48, 44

	.type	.L.str5,%object         @ @.str5
.L.str5:
	.asciz	"RCC_ClocksStatus.HCLK_Frequency:\t%lu MHz\n"
	.size	.L.str5, 42

	.type	.L.str6,%object         @ @.str6
.L.str6:
	.asciz	"RCC_ClocksStatus.PCLK1_Frequency:\t%lu MHz\n"
	.size	.L.str6, 43

	.type	.L.str7,%object         @ @.str7
.L.str7:
	.asciz	"RCC_ClocksStatus.PCLK2_Frequency:\t%lu MHz\n"
	.size	.L.str7, 43

	.type	.L.str8,%object         @ @.str8
.L.str8:
	.asciz	"RCC Sys clk source [0 - HSI, 4 - HSE, 8 - PLL]: %d\n"
	.size	.L.str8, 52

	.type	.L.str9,%object         @ @.str9
.L.str9:
	.asciz	"----------------------------------------------------\n"
	.size	.L.str9, 54

	.type	uptime_us,%object       @ @uptime_us
	.bss
	.globl	uptime_us
	.align	2
uptime_us:
	.long	0                       @ 0x0
	.size	uptime_us, 4

	.type	get_uptime.uptime_ms,%object @ @get_uptime.uptime_ms
	.local	get_uptime.uptime_ms
	.comm	get_uptime.uptime_ms,2,4
	.type	get_uptime.uptime_s,%object @ @get_uptime.uptime_s
	.local	get_uptime.uptime_s
	.comm	get_uptime.uptime_s,1,4
	.type	get_uptime.uptime_m,%object @ @get_uptime.uptime_m
	.local	get_uptime.uptime_m
	.comm	get_uptime.uptime_m,1,4
	.type	get_uptime.uptime_h,%object @ @get_uptime.uptime_h
	.local	get_uptime.uptime_h
	.comm	get_uptime.uptime_h,1,4
	.type	get_uptime.uptime_d,%object @ @get_uptime.uptime_d
	.local	get_uptime.uptime_d
	.comm	get_uptime.uptime_d,2,4
	.type	get_uptime.msb_ms,%object @ @get_uptime.msb_ms
	.local	get_uptime.msb_ms
	.comm	get_uptime.msb_ms,1,4
	.type	.L.str10,%object        @ @.str10
	.section	.rodata.str1.1,"aMS",%progbits,1
.L.str10:
	.asciz	"uptime: %d days, %.2d:%.2d:%.2d.%.3d"
	.size	.L.str10, 37

	.type	.L.str13,%object        @ @.str13
.L.str13:
	.asciz	"get_led_structure(): wrong port\n"
	.size	.L.str13, 33

	.type	.L.str114,%object       @ @.str114
.L.str114:
	.asciz	"get_led_structure(): wrong pin.\n"
	.size	.L.str114, 33

	.type	.L.str215,%object       @ @.str215
.L.str215:
	.asciz	"led_set(): pogresan argument\n"
	.size	.L.str215, 30

	.type	.L.str316,%object       @ @.str316
.L.str316:
	.asciz	"led(): wrong state\n"
	.size	.L.str316, 20

	.type	.L.str21,%object        @ @.str21
.L.str21:
	.asciz	"\033c"
	.size	.L.str21, 3

	.type	.L.str122,%object       @ @.str122
.L.str122:
	.asciz	"\t\t\t\tSTM32 pocetak\n"
	.size	.L.str122, 19

	.type	.L.str223,%object       @ @.str223
.L.str223:
	.asciz	"Na pocetku bje\305\241e \305\241tos.\n"
	.size	.L.str223, 26

	.type	.L.str324,%object       @ @.str324
.L.str324:
	.asciz	"________________________________________________________________________________\n"
	.size	.L.str324, 82

	.type	.L.str425,%object       @ @.str425
.L.str425:
	.asciz	"sad ide while\n"
	.size	.L.str425, 15

	.type	__env,%object           @ @__env
	.bss
	.globl	__env
	.align	2
__env:
	.zero	4
	.size	__env, 4

	.type	environ,%object         @ @environ
	.section	.data.rel,"aw",%progbits
	.globl	environ
	.align	2
environ:
	.long	__env
	.size	environ, 4

	.type	.L.str126,%object       @ @.str126
	.section	.rodata.str1.1,"aMS",%progbits,1
.L.str126:
	.asciz	"Heap and stack collision\n"
	.size	.L.str126, 26

	.type	.Lswitch.table1,%object @ @switch.table1
	.section	.rodata,"a",%progbits
	.align	2
.Lswitch.table1:
	.long	0                       @ 0x0
	.long	256                     @ 0x100
	.long	512                     @ 0x200
	.size	.Lswitch.table1, 12

	.type	APBAHBPrescTable,%object @ @APBAHBPrescTable
APBAHBPrescTable:
	.ascii	"\000\000\000\000\001\002\003\004\001\002\003\004\006\007\b\t"
	.size	APBAHBPrescTable, 16

	.type	SystemCoreClock,%object @ @SystemCoreClock
	.data
	.globl	SystemCoreClock
	.align	2
SystemCoreClock:
	.long	168000000               @ 0xa037a00
	.size	SystemCoreClock, 4

	.type	AHBPrescTable,%object   @ @AHBPrescTable
	.section	.rodata,"a",%progbits
	.globl	AHBPrescTable
AHBPrescTable:
	.ascii	"\000\000\000\000\000\000\000\000\001\002\003\004\006\007\b\t"
	.size	AHBPrescTable, 16

	.type	usart1_rx_event,%object @ @usart1_rx_event
	.data
	.globl	usart1_rx_event
	.align	2
usart1_rx_event:
	.long	2                       @ 0x2
	.size	usart1_rx_event, 4

	.type	usart2_rx_event,%object @ @usart2_rx_event
	.globl	usart2_rx_event
	.align	2
usart2_rx_event:
	.long	2                       @ 0x2
	.size	usart2_rx_event, 4

	.type	usart3_rx_event,%object @ @usart3_rx_event
	.globl	usart3_rx_event
	.align	2
usart3_rx_event:
	.long	2                       @ 0x2
	.size	usart3_rx_event, 4

	.type	usart1_rx_string_arr,%object @ @usart1_rx_string_arr
	.bss
	.globl	usart1_rx_string_arr
usart1_rx_string_arr:
	.zero	100
	.size	usart1_rx_string_arr, 100

	.type	usart2_rx_string_arr,%object @ @usart2_rx_string_arr
	.globl	usart2_rx_string_arr
usart2_rx_string_arr:
	.zero	100
	.size	usart2_rx_string_arr, 100

	.type	usart3_rx_string_arr,%object @ @usart3_rx_string_arr
	.globl	usart3_rx_string_arr
usart3_rx_string_arr:
	.zero	100
	.size	usart3_rx_string_arr, 100

	.type	testbuffer,%object      @ @testbuffer
	.data
	.globl	testbuffer
testbuffer:
	.asciz	"Ovo je testni buffer za USART TX IRQ\n"
	.size	testbuffer, 38

	.type	USART1_IRQHandler.cnt,%object @ @USART1_IRQHandler.cnt
	.local	USART1_IRQHandler.cnt
	.comm	USART1_IRQHandler.cnt,1,4
	.type	_MergedGlobals,%object  @ @_MergedGlobals
	.local	_MergedGlobals
	.comm	_MergedGlobals,44,16

	.ident	"clang version 3.5.0 (tags/RELEASE_350/final)"
	.ident	"clang version 3.5.0 (tags/RELEASE_350/final)"
	.ident	"clang version 3.5.0 (tags/RELEASE_350/final)"
	.ident	"clang version 3.5.0 (tags/RELEASE_350/final)"
	.ident	"clang version 3.5.0 (tags/RELEASE_350/final)"
	.ident	"clang version 3.5.0 (tags/RELEASE_350/final)"
	.ident	"clang version 3.5.0 (tags/RELEASE_350/final)"
	.ident	"clang version 3.5.0 (tags/RELEASE_350/final)"
	.ident	"clang version 3.5.0 (tags/RELEASE_350/final)"
	.ident	"clang version 3.5.0 (tags/RELEASE_350/final)"
	.ident	"clang version 3.5.0 (tags/RELEASE_350/final)"
	.ident	"clang version 3.5.0 (tags/RELEASE_350/final)"
	.ident	"clang version 3.5.0 (tags/RELEASE_350/final)"
	.ident	"clang version 3.5.0 (tags/RELEASE_350/final)"
	.ident	"clang version 3.5.0 (tags/RELEASE_350/final)"
	.ident	"clang version 3.5.0 (tags/RELEASE_350/final)"
	.ident	"clang version 3.5.0 (tags/RELEASE_350/final)"
	.ident	"clang version 3.5.0 (tags/RELEASE_350/final)"
	.ident	"clang version 3.5.0 (tags/RELEASE_350/final)"
	.ident	"clang version 3.5.0 (tags/RELEASE_350/final)"
	.ident	"clang version 3.5.0 (tags/RELEASE_350/final)"
	.ident	"clang version 3.5.0 (tags/RELEASE_350/final)"
	.ident	"clang version 3.5.0 (tags/RELEASE_350/final)"
	.ident	"clang version 3.5.0 (tags/RELEASE_350/final)"
	.ident	"clang version 3.5.0 (tags/RELEASE_350/final)"
	.ident	"clang version 3.5.0 (tags/RELEASE_350/final)"
	.ident	"clang version 3.5.0 (tags/RELEASE_350/final)"
	.ident	"clang version 3.5.0 (tags/RELEASE_350/final)"
	.ident	"clang version 3.5.0 (tags/RELEASE_350/final)"
	.ident	"clang version 3.5.0 (tags/RELEASE_350/final)"
	.ident	"clang version 3.5.0 (tags/RELEASE_350/final)"
	.ident	"clang version 3.5.0 (tags/RELEASE_350/final)"
	.ident	"clang version 3.5.0 (tags/RELEASE_350/final)"
	.ident	"clang version 3.5.0 (tags/RELEASE_350/final)"
	.ident	"clang version 3.5.0 (tags/RELEASE_350/final)"
	.ident	"clang version 3.5.0 (tags/RELEASE_350/final)"
	.ident	"clang version 3.5.0 (tags/RELEASE_350/final)"
	.ident	"clang version 3.5.0 (tags/RELEASE_350/final)"
	.ident	"clang version 3.5.0 (tags/RELEASE_350/final)"
	.ident	"clang version 3.5.0 (tags/RELEASE_350/final)"
