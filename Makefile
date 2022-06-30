PROJECT_ROOT=/home/focal/eclipse-workspace
FILES=$(PROJECT_ROOT)/build/asm/startup.o  \
	  $(PROJECT_ROOT)/build/entry.o \
      $(PROJECT_ROOT)/build/hal/sysctrl.o \
      $(PROJECT_ROOT)/build/hal/gpio.o \
      $(PROJECT_ROOT)/build/hal/timer.o \
      $(PROJECT_ROOT)/build/thread/thread.o \
      $(PROJECT_ROOT)/build/thread/msg.o \
      $(PROJECT_ROOT)/build/hal/nvic.o \
      $(PROJECT_ROOT)/build/asm/thread.o
INCLUDE=-I$(PROJECT_ROOT) \
		-I$(PROJECT_ROOT)/asm \
		-I$(PROJECT_ROOT)/hal/inc \
		-I$(PROJECT_ROOT)/thread/inc 
TOOLS_PATH=/home/focal/src/gcc-arm-11.2-2022.02-x86_64-arm-none-eabi/bin
CC=arm-none-eabi-gcc
ASM=arm-none-eabi-as
LD=arm-none-eabi-ld
DISASM=arm-none-eabi-objdump
ASMFLAGS=--gen-debug -mcpu=cortex-m4
CFLAGS=-g -mcpu=cortex-m4 -mthumb
LINKERFLAGS=-A armv7e-m --default-script $(PROJECT_ROOT)/scat.ld --print-memory-usage

export PATH:=$(PATH):$(TOOLS_PATH)


all: $(FILES)
	@echo "Linking modules.."
	@$(LD) $(LINKERFLAGS) $(FILES) -o $(PROJECT_ROOT)/project.axf
	@$(DISASM) --disassemble --source $(PROJECT_ROOT)/project.axf \
		> $(PROJECT_ROOT)/project-disassembly.txt 

clean:
	@echo "Cleaning files.."
	@rm -rf $(PROJECT_ROOT)/build/*.*
	@rm -rf $(PROJECT_ROOT)/build/asm/*.*
	@rm -rf $(PROJECT_ROOT)/build/rt/*.*
	@rm -rf $(PROJECT_ROOT)/build/hal/*.*
	@rm -rf $(PROJECT_ROOT)/build/thread/*.*
	@rm -rf $(PROJECT_ROOT)/project.axf $(PROJECT_ROOT)/project-disassembly.txt
	@echo "Cleaning complete.."

$(PROJECT_ROOT)/build/asm/startup.o: $(PROJECT_ROOT)/asm/startup.s
	@echo "Assembling startup.s.."
	@$(ASM) $(ASMFLAGS) $(PROJECT_ROOT)/asm/startup.s \
		-o $(PROJECT_ROOT)/build/asm/startup.o
$(PROJECT_ROOT)/build/hal/sysctrl.o : $(PROJECT_ROOT)/hal/src/sysctrl.c
	@echo "Compiling sysctrl.c.."
	@$(CC) $(CFLAGS) $(INCLUDE) -c $(PROJECT_ROOT)/hal/src/sysctrl.c \
		-o $(PROJECT_ROOT)/build/hal/sysctrl.o
$(PROJECT_ROOT)/build/hal/gpio.o : $(PROJECT_ROOT)/hal/src/gpio.c
	@echo "Compiling gpio.c.."
	@$(CC) $(CFLAGS) $(INCLUDE) -c $(PROJECT_ROOT)/hal/src/gpio.c \
		-o $(PROJECT_ROOT)/build/hal/gpio.o
$(PROJECT_ROOT)/build/thread/msg.o : $(PROJECT_ROOT)/thread/src/msg.c
	@echo "Compiling msg.c.."
	@$(CC) $(CFLAGS) $(INCLUDE) -c $(PROJECT_ROOT)/thread/src/msg.c \
		-o $(PROJECT_ROOT)/build/thread/msg.o
$(PROJECT_ROOT)/build/thread/thread.o : $(PROJECT_ROOT)/thread/src/thread.c
	@echo "Compiling thread.c.."
	@$(CC) $(CFLAGS) $(INCLUDE) -c $(PROJECT_ROOT)/thread/src/thread.c \
		-o $(PROJECT_ROOT)/build/thread/thread.o
$(PROJECT_ROOT)/build/hal/nvic.o : $(PROJECT_ROOT)/hal/src/nvic.c
	@echo "Compiling nvic.c.."
	@$(CC) $(CFLAGS) $(INCLUDE) -c $(PROJECT_ROOT)/hal/src/nvic.c \
		-o $(PROJECT_ROOT)/build/hal/nvic.o
$(PROJECT_ROOT)/build/asm/thread.o : $(PROJECT_ROOT)/asm/thread.s
	@echo "Assembling thread.s.."
	@$(ASM) $(ASMFLAGS) $(PROJECT_ROOT)/asm/thread.s \
		-o $(PROJECT_ROOT)/build/asm/thread.o
$(PROJECT_ROOT)/build/hal/timer.o : $(PROJECT_ROOT)/hal/src/timer.c
	@echo "Compiling timer.c.."
	@$(CC) $(CFLAGS) $(INCLUDE) -c $(PROJECT_ROOT)/hal/src/timer.c \
		-o $(PROJECT_ROOT)/build/hal/timer.o
$(PROJECT_ROOT)/build/entry.o: $(PROJECT_ROOT)/entry.c
	@echo "Compiling entry.c.."
	@$(CC) $(CFLAGS) $(INCLUDE) -c $(PROJECT_ROOT)/entry.c -o $(PROJECT_ROOT)/build/entry.o

