
    .syntax unified
    .cpu    cortex-m4
    .thumb
	.section .thread, "ax"
	.align 4
	.text

	.thumb_func
	.globl  __ctxt_switch
__ctxt_switch:
     push    {r4, r5, r6, r7, r8, r9, r10, r11, lr}

     str     sp, [r1, #36]
     ldr     sp, [r0, #36]

	 cpsie   i
     pop     {r4, r5, r6, r7, r8, r9, r10, r11, pc}
