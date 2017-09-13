###############################################################################
# Makefile for the project ELE542_Proto1
###############################################################################

## General Flags
PROJECT = ELE542_Proto1
MCU = atmega32
TARGET = ELE542_Proto1.elf
CC = avr-gcc

CPP = avr-g++

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2 -std=gnu99   -DF_CPU=16000000UL -O0 -funsigned-char
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS +=  -Wl,-Map=ELE542_Proto1.map


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Include Directories
INCLUDES = -I"C:\Users\aj52040\Downloads\ELE542__LABP28559101_GROA03019209\." 

## Objects that must be built in order to link
OBJECTS = ADC.o calibration.o i2c_caneva.o main.o moteur.o PWM.o sonar.o UART.o utils.o watchdog.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) ELE542_Proto1.hex ELE542_Proto1.eep ELE542_Proto1.lss## Compile
ADC.o: ../ADC.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

calibration.o: ../calibration.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

i2c_caneva.o: ../i2c_caneva.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

main.o: ../main.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

moteur.o: ../moteur.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

PWM.o: ../PWM.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

sonar.o: ../sonar.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

UART.o: ../UART.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

utils.o: ../utils.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

watchdog.o: ../watchdog.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

##Link
$(TARGET): $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET)

%.hex: $(TARGET)
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.eep: $(TARGET)
	-avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@ || exit 0

%.lss: $(TARGET)
	avr-objdump -h -S $< > $@

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) ELE542_Proto1.elf dep/* ELE542_Proto1.hex ELE542_Proto1.eep ELE542_Proto1.lss ELE542_Proto1.map


## Other dependencies
-include $(shell mkdir dep 2>NUL) $(wildcard dep/*)

