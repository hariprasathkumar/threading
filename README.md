### Simple multi threading 
(Not a conventional one .. but a fundamental one)

This project applies theoretical understanding of scheduling into practice.

You would need:
	- A TM4C123x Launch pad (Mine's an old one, there are some new ones too; 
							  Checkout ti.com)
	- Eclipse - Make file project
	- Open OCD package 
	- GNU ARM embedded toolchain ("none")
	- GDB cross compiled for ARM 


Files:
startup.s (vector table stuff)
thread.s  (context switch routine - no FPU used mind you!)
gpio.c (for fun - using the three LEDs on board)
nvic.c (Let the man know to open the flood gates :-) )
sysctrl.c (Clk and reset stuff)
timer.c (To simulate Periodic mesage posting) 
msg.c (Get the message from timer in the buffer)
thread.c (Schedule - just invoke stuff)
entry.c (the so-called main)
types.h (some basic type system when needed to be added for the entire project) 
Makefile (make)
scat.ld (Link for TM4C123x)

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

ON running you would see the Stuff in action:
	Red ON -> Red OFF -> Blue ON -> Blue OFF -> Green ON -> Green OFF - repeat


<<If you had reached here, its a good bet that you are trying a version of 
	the same; It may not be much, I do hope it helps; Happy coding!! >>


 
