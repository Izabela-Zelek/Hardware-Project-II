###############################################################################
# Makefile for StarterKit
###############################################################################

## General Flags
PROJECT = StarterKit
GAME= StarterKit
MCU = atmega644
TARGET = $(GAME).elf
CC = avr-gcc
INFO=../gameinfo.properties

## Print Rule
print-%  : ; @echo $* = $($*)

## Uzebin Directory (bin directory of tools)
## Edit this line to point to location of uzebox
TOOLS_DIR = ../../../uzebox

## Kernel settings
KERNEL_DIR = $(TOOLS_DIR)/kernel
KERNEL_OPTIONS  = -DVIDEO_MODE=1 -DINTRO_LOGO=0 -DTILE_HEIGHT=12

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2 -std=gnu99 -DF_CPU=28636360UL -Os -fsigned-char -ffunction-sections -fno-toplevel-reorder
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 
CFLAGS += $(KERNEL_OPTIONS)

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS += -Wl,-Map=$(GAME).map 
LDFLAGS += -Wl,-gc-sections 


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Objects that must be built in order to link
OBJECTS = uzeboxVideoEngineCore.o uzeboxCore.o uzeboxSoundEngine.o uzeboxSoundEngineCore.o uzeboxVideoEngine.o $(GAME)Engine.o $(GAME).o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Include Directories
INCLUDES = -I"$(KERNEL_DIR)" 

## Compile Kernel files
$(info VAR="KERNEL_DIR")
$(info VAR="$(KERNEL_DIR)")
$(info VAR="CC")
$(info VAR="$(CC)")
$(info VAR="INCLUDES")
$(info VAR="$(INCLUDES)")
$(info VAR="ASMFLAGS")
$(info VAR="$(ASMFLAGS)")


uzeboxVideoEngineCore.o: $(KERNEL_DIR)/uzeboxVideoEngineCore.s
	$(CC) $(INCLUDES) $(ASMFLAGS) -c  $<

uzeboxSoundEngineCore.o: $(KERNEL_DIR)/uzeboxSoundEngineCore.s
	$(CC) $(INCLUDES) $(ASMFLAGS) -c  $<

uzeboxCore.o: $(KERNEL_DIR)/uzeboxCore.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

uzeboxSoundEngine.o: $(KERNEL_DIR)/uzeboxSoundEngine.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

uzeboxVideoEngine.o: $(KERNEL_DIR)/uzeboxVideoEngine.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

## Compile game ASM sources
$(GAME)Engine.o: ../$(GAME)Engine.asm
	$(CC) $(INCLUDES) $(ASMFLAGS) -c  $<

## Compile game sources
$(GAME).o: ../$(GAME).c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

$(info VAR="LINKING....")

$(info VAR="$(TARGET)")
$(info VAR="$(OBJECTS)")
$(info VAR="$(CC)")
$(info VAR="$(LDFLAGS)")
$(info VAR="$(LINKONLYOBJECTS)")
$(info VAR="$(LIBDIRS)")
$(info VAR="$(LIBS)")


##Link
$(TARGET): $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET)

%.hex: $(TARGET)
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.eep: $(TARGET)
	-avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@ || exit 0

%.lss: $(TARGET)
	avr-objdump -h -S $< > $@

## Edit directory to point to location of packrom
%.uze: $(TARGET)
	-$(TOOLS_DIR)/tools/packrom/packrom $(GAME).hex $@ $(INFO)

UNAME := $(shell sh -c 'uname -s 2>/dev/null || echo not')
AVRSIZEFLAGS := -A ${TARGET}
ifneq (,$(findstring MINGW,$(UNAME)))
AVRSIZEFLAGS := -C --mcu=${MCU} ${TARGET}
endif

size: ${TARGET}
	@echo
	@avr-size ${AVRSIZEFLAGS}


## Clean directory, build and run emulator
.PHONY: run-test

run-test: clean all run

## Build
all: $(TARGET) $(GAME).hex $(GAME).eep $(GAME).lss $(GAME).uze size

clean:
	-rm -rf $(OBJECTS) $(GAME).* dep/*

run:
	$(TOOLS_DIR)/tools/uzem/uzem $(GAME).hex

## Other dependencies
-include $(shell mkdir dep 2>/dev/null) $(wildcard dep/*)


