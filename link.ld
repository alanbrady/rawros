OUTPUT_FORMAT("elf32-i386")
ENTRY(loader)

SECTIONS {
    . = 0x00100000;

    .multiboot : AT(ADDR(.multiboot))
    {
        *(.multiboot)
    }

    .text ALIGN(0x1000) : AT(ADDR(.text))
    {
        *(.text)
        *(.rodata*)
    }

    .data ALIGN (0x1000) : AT(ADDR(.data))
    {
        *(.data)
    }

    .bss ALIGN (0x1000) : AT(ADDR(.bss))
    {
        *(COMMON)
        *(.bss)
    }
}
