################################################################################
# Options
################################################################################

TOOLCHAIN ?= arm-none-eabi

AOPS = --warn --fatal-warnings
COPS = -Wall -Werror -O2 -nostdlib -nostartfiles -ffreestanding -I.

################################################################################
# Source files
################################################################################

C_SRCS = $(wildcard *.c) $(wildcard lib/*.c)
C_OBJS = $(C_SRCS:%.c=%.o)
C_HDRS = $(wildcard *.h) $(wildcard lib/*.h)

################################################################################
# Rules
################################################################################

all : kernel.img

clean :
	rm -f *.o
	rm -f *.bin
	rm -f *.hex
	rm -f *.srec
	rm -f *.elf
	rm -f *.list
	rm -f *.img

vectors.o : vectors.s
	$(TOOLCHAIN)-as $(AOPS) vectors.s -o vectors.o

%.o: %.c $(C_HDRS)
	$(TOOLCHAIN)-gcc $(COPS) -c $< -o $@

notmain.elf : memmap vectors.o $(C_OBJS)
	$(TOOLCHAIN)-ld vectors.o $(C_OBJS) -T memmap -o notmain.elf
	$(TOOLCHAIN)-objdump -D notmain.elf > notmain.list

kernel.img : notmain.elf
	$(TOOLCHAIN)-objcopy --srec-forceS3 notmain.elf -O srec notmain.srec
	$(TOOLCHAIN)-objcopy notmain.elf -O binary kernel.img

################################################################################
# Utility rules
################################################################################

copy : kernel.img
	pbcopy < notmain.srec
