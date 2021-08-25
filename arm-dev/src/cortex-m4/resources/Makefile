# Project dependencies
PROJECT := final

# Build tools
CC=arm-none-eabi-gcc
CP=arm-none-eabi-objcopy

# Compiler options
CFLAGS  = -ggdb -O0 -Wall -Wextra -Warray-bounds -mlittle-endian -Wno-unused-parameter -Wno-misleading-indentation
CFLAGS  += -mthumb -mcpu=cortex-m4 -mthumb-interwork

# Linker file / options
LD := ../../lkr_scripts
LFLAGS  = -T $(wildcard $(LD)/*.ld)
LFLAGS += --specs=nano.specs --specs=nosys.specs 
LFLAGS += -Wl,-Map -Wl,$(BUILDDIR)/$(PROJECT).map

# Directories to be searched for header files
INCLUDE = -I..\..\..\..\STM32F4xx_DSP_StdPeriph_Lib_V1.8.0\Libraries\CMSIS\include 
INCLUDE += -I..\..\..\..\STM32F4xx_DSP_StdPeriph_Lib_V1.8.0\Libraries\STM32F4xx_StdPeriph_Driver\inc
INCLUDE += -I..\..\core\sys_lib
INCLUDE += -Iinclude
INCLUDE += -I.\

# Add Standard Peripheral Library to the build configuration
DEFS = -DUSE_STDPERIPH_DRIVER

#source and build directories
DRIVERS := drivers
SOURCEDIR := src
SYSTEM := ../../core/sys_lib
STARTUP := ../../core/startup
BUILDDIR := build

OBJECTS = $(patsubst $(SOURCEDIR)/%.c, $(BUILDDIR)/%.o, $(wildcard $(SOURCEDIR)/*.c)) \
		  $(patsubst $(DRIVERS)/%.c, $(BUILDDIR)/%.o, $(wildcard $(DRIVERS)/*.c)) \
		  $(patsubst $(SYSTEM)/%.c, $(BUILDDIR)/%.o, $(wildcard $(SYSTEM)/*.c)) \
		  $(patsubst $(STARTUP)/%.s, $(BUILDDIR)/%.o, $(wildcard $(STARTUP)/*.s))

# Build targets
.PHONY: all
all: $(BUILDDIR)/$(PROJECT).elf 

$(BUILDDIR)/%.o: $(SOURCEDIR)/%.c 
	$(CC) $(INCLUDE) $(DEFS) $(CFLAGS) -c $< -o $@
	
$(BUILDDIR)/%.o: $(DRIVERS)/%.c 
	$(CC) $(INCLUDE) $(DEFS) $(CFLAGS) -c $< -o $@	

$(BUILDDIR)/%.o: $(SYSTEM)/%.c 
	$(CC) $(INCLUDE) $(DEFS) $(CFLAGS) -c $< -o $@

$(BUILDDIR)/%.o: $(STARTUP)/%.s
	$(CC) $(INCLUDE) $(DEFS) $(CFLAGS) -c $< -o $@

$(BUILDDIR)/$(PROJECT).elf: $(OBJECTS)
	$(CC) $(INCLUDE) $(DEFS) $(CFLAGS) $(LFLAGS) -o $@ $(OBJECTS)
	$(CP) -O binary $(BUILDDIR)/$(PROJECT).elf $(BUILDDIR)/$(PROJECT).bin

.PHONY: clean
clean:
	del $(BUILDDIR)\*.o $(BUILDDIR)\*.bin $(BUILDDIR)\*.elf $(BUILDDIR)\*.map
	
load:
	openocd -f ..\..\..\..\boards\blackpill.cfg

flash:
	openocd -f interface\stlink.cfg -f target\stm32f4x.cfg -c "program $(BUILDDIR)/final.elf verify reset exit"