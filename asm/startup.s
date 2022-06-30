
    	.syntax unified
	    .cpu    cortex-m4
		.thumb
		.section .start, "ax"
		.align 4
		.global __stack
		.global reset

		.dc.l __stack
		.dc.l reset // 0
		.dc.l nmi_h // 1
		.dc.l hardflt_h // 2
		.dc.l memflt_h // 3
		.dc.l busflt_h // 4
		.dc.l usgflt_h // 5
		.dc.l deflt // 6
		.dc.l deflt // 7
		.dc.l deflt // 8
		.dc.l deflt // 9
		.dc.l svccall_h // 10
		.dc.l deflt // 11
		.dc.l deflt // 12
		.dc.l pendsv_h // 13
		.rept 20
			.dc.l deflt
		.endr
		.dc.l systk_h // 34
		.rept 120
			.dc.l deflt
		.endr

.thumb_func
.type reset, %function
reset:
		cpsid i
		ldr r0, =__main_stack_area_start__
		msr MSP, r0
		ldr r0, =___process_stack_area_start__
		msr PSP, r0
		movs r0, #2
		msr CONTROL, r0
		isb
		BL entry
		B .

.thumb_func
.type deflt, %function
deflt:
	B .

.thumb_func
.type nmi_h, %function
nmi_h:
	B .

.thumb_func
.type hardflt_h, %function
hardflt_h:
	B .

.thumb_func
.type memflt_h, %function
memflt_h:
	B .

.thumb_func
.type busflt_h, %function
busflt_h:
	B .

.thumb_func
.type usgflt_h, %function
usgflt_h:
	B .

.thumb_func
.type svccall_h, %function
svccall_h:
	B .

.thumb_func
.type pendsv_h, %function
pendsv_h:
	B .

.thumb_func
.type systk_h, %function
systk_h:
	B systimer_handler

