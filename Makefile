SOURCES = $(wildcard *.c)
SOURCES += $(wildcard *.s)
OBJECTS = $(SOURCES:.s=.o)
OBJECTS := $(OBJECTS:.c=.o)
CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
		 -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c
LDFLAGS = -T link.ld -melf_i386
AS = nasm
ASFLAGS = -f elf32

all: kernel.elf
	cp kernel.elf ./coreboot/payload.elf & \
	cp kernel.elf ./iso/boot/ & \
	make -C ./coreboot/
	genisoimage -R -b boot/grub/stage2_eltorito -boot-load-size 4 -no-emul-boot -A os -input-charset utf8 -quiet -boot-info-table -o os.iso iso

kernel.elf: $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) -o kernel.elf

run:
	#/usr/bin/qemu-system-i386 -L ./coreboot -bios ./coreboot/build/coreboot.rom -s -enable-kvm -vga std -serial file:kout.txt 
	bochs -f bochs_config -q

gdb:
	/usr/bin/qemu-system-i386 -L ./coreboot -bios ./coreboot/build/coreboot.rom -s -S


%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -f *.o
