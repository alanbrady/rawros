SOURCES = $(wildcard *.c)
SOURCES += $(wildcard *.s)
OBJECTS = $(SOURCES:.s=.o)
OBJECTS := $(OBJECTS:.c=.o)
CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
	-nostartfiles -nodefaultlibs -Wall -Wextra -Werror -Og -g
LDFLAGS = -T link.ld -melf_i386
AS = nasm
ASFLAGS = -f elf32
TARGET=kernel.elf
ISO_NAME=os.iso
BOCHS=./bochs
BOCHS_FLAGS= -f ./bochs_config -q
QEMU=qemu-system-i386
QEMU_FLAGS= -cdrom $(ISO_NAME) -serial stdio
QEMU_DEBUG_FLAGS= -s -S

all: iso

$(TARGET): $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) -o $(TARGET)

run: iso
	$(QEMU) $(QEMU_FLAGS)

qemu: iso
	$(QEMU) $(QEMU_FLAGS) $(QEMU_DEBUG_FLAGS)

bochs: iso
	$(BOCHS) $(BOCHS_FLAGS)

iso: $(TARGET)
	cp $(TARGET) ./iso/boot/
	genisoimage -R -b boot/grub/stage2_eltorito -boot-load-size 4 -no-emul-boot \
		-A os -input-charset utf8 -quiet -boot-info-table -o $(ISO_NAME) iso

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

%.o: %.s
	$(AS) $< -o $@ $(ASFLAGS)

clean:
	rm -f *.o
