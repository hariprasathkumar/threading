Simple multi threading (Not a conventional one .. but a fundamental one)

This project applies theoretical understanding of scheduling into practice.

You would need:
	a. A TM4C123x Launch pad (Mine's an old one, there are some new ones too; 
							  Checkout ti.com)
	b. Eclipse - Make file project
	c. Open OCD package 
	d. GNU ARM embedded toolchain ("none")
	e. GDB cross compiled for ARM 


Files:
	|
	|_ _ ASM
	|	|
	|	|_ _ startup.s (vector table stuff)
	|	|
	|	|_ _ thread.s  (context switch routine - no FPU used mind you!)
	|
	|_ _HAL
	|	|
	|	|_ _ inc
	|	|	|
	|	|	|_ _ gpio.h (for fun - using the three LEDs on board)
	|	|	|
	|	|	|_ _ nvic.h (Let the man know to open the flood gates :-) )
	|	|	|
	|	|	|_ _ sysctrl.h (Clk and reset stuff)
	|	|	|
	|	|	|_ _ timer.h (To simulate Periodic mesage posting) 
	|	|	
	|	|_ _src
	|		|
	|		|_ _ gpio.c 
	|		|
	|		|_ _ nvic.c
	|		|
	|		|_ _ sysctrl.c
	|		|
	|		|_ _ timer.c
	|		
	|_ _THREAD
	|	|
	|	|_ _ inc
	|	|	|
	|	|	|_ _ msg.h (Get the message from timer in the buffer)
	|	|	|
	|	|	|_ _ thread.h (Schedule - just invoke stuff)
	|	|
	|	|_ _ src
	|		|
	|		|_ _ msg.c
	|		|
	|		|_ _ thread.c
	|
	|
	|_ _ entry.c (the so-called main)
	|
	|_ _ types.h (some basic type system when needed to be added for the entire project) 
	|
	|_ _ Makefile (make)
	|
	|_ _ scat.ld (Link for TM4C123x)

The goal is to see (I mean literally see) the threading in action.

For eclipse:
	Just google eclipse installer

For Open OCD: 
	get the package
	NOTE: You would need the udev rules.d setup properly for this (I am using debian)
	Use option - -f board/ti_ek-tm4c123gxl.cfg

For GNU ARM toolchain:
	Just google it. Get the one ARM "none" eabi

For GDB:
	This you would have to compile the source on your machine, at least that what didnt get me into trouble
 
Then import project; Build; 
You can download code with openocd / "bug" option in eclipse as this already has the flash driver

Open On-Chip Debugger 0.11.0+dev-00715-g480d4e177 (2022-06-11-14:41)
Licensed under GNU GPL v2
For bug reports, read
	http://openocd.org/doc/doxygen/bugs.html
Info : The selected transport took over low-level target control. The results might differ compared to plain JTAG/SWD
Started by GNU MCU Eclipse
Info : Listening on port 6666 for tcl connections
Info : Listening on port 4444 for telnet connections
Info : clock speed 22053 kHz
Info : ICDI Firmware version: 9270
Error: SRST error
Info : [tm4c123gh6pm.cpu] Cortex-M4 r0p1 processor detected
Info : [tm4c123gh6pm.cpu] target has 6 breakpoints, 4 watchpoints
Info : starting gdb server for tm4c123gh6pm.cpu on 3333
Info : Listening on port 3333 for gdb connections
Info : accepting 'gdb' connection on tcp/3333
target halted due to debug-request, current mode: Thread 
xPSR: 0x61000000 pc: 0x000009e6 psp: 0x200004b4
Warn : Prefer GDB command "target extended-remote :3333" instead of "target remote :3333"
Error: SRST error
target halted due to debug-request, current mode: Thread 
xPSR: 0x01000000 pc: 0x00000270 msp: 0x20007ffc
Error: SRST error
target halted due to debug-request, current mode: Thread 
xPSR: 0x01000000 pc: 0x00000270 msp: 0x20007ffc, semihosting
Info : Padding image section 0 at 0x00000c22 with 2 bytes
Error: SRST error
target halted due to debug-request, current mode: Thread 
xPSR: 0x01000000 pc: 0x00000270 msp: 0x20007ffc, semihosting
Error: SRST error
target halted due to debug-request, current mode: Thread 
xPSR: 0x01000000 pc: 0x00000270 msp: 0x20007ffc, semihosting

(reset doesnt seem to work for me - if same for you dont rely on the reset option in eclipse)

ON running you would see the Stuff in action:
	Red ON -> Red OFF -> Blue ON -> Blue OFF -> Green ON -> Green OFF - repeat


<<If you had reached here, its a good bet that you are trying a version of 
	the same; It may not be much, I do hope it helps; Happy coding!! >>


 
