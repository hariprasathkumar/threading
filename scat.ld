ENTRY(reset);

MEMORY { FLASH : ORIGIN = 0x00000000, LENGTH = 0x40000 
		 SRAM  : ORIGIN = 0x20000000, LENGTH = 0x08000 }

__stack_size = 0x100;
__thd_stack_size = 0x400;

SECTIONS
{
	.start : { *(.start) *(.thread) } > FLASH	
	.text  : { *(.text) } > FLASH
	
	.rodata : { *(.rodata) } > FLASH
	.data : { *(.data) } > FLASH
	
	.debug : { *(.debug) } > FLASH
	.debug_info : { *(.debug_info) } > FLASH
	
	. = 0x20000000;
	.bss : { *(.bss) } > SRAM

	. = ALIGN(0x40);
	__thd1_wrk_area_start__ = .;
	.thd1 : {
		. = . + __thd_stack_size;
		*(.thd1)
	} > SRAM
	__thd1_wrk_area_end__ = .;
	
	. = ALIGN(0x40);
	__thd2_wrk_area_start__ = .;
	.thd2 : {
		. = . + __thd_stack_size;
		*(.thd2)
	} > SRAM
	__thd2_wrk_area_end__ = .;

	. = ALIGN(8);
	___process_stack_area_start__ = .;
	.pstack : {
		. = . + __thd_stack_size;
		*(.pstack)
	} > SRAM
	___process_stack_area_end__ = .;	

	. = ALIGN(8);
	__main_stack_area_start__ = .;
	.mstack : {
		__stack = ORIGIN(SRAM) + LENGTH(SRAM) - 4;
		_ssize = __stack_size;
		. = (__stack - _ssize);
		*(.mstack)
	} > SRAM
	__main_stack_area_end__ = .;	
}