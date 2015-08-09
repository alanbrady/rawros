; vim: ft=nasm

section .multiboot
align 4
mboot:
    MBALIGN             equ 1<<0
    MEMINFO             equ 1<<1
    FLAGS               equ (MBALIGN | MEMINFO)
    MAGIC_NUMBER        equ 0x1BADB002
    CHECKSUM            equ -(MAGIC_NUMBER+FLAGS)

    dd MAGIC_NUMBER
    dd FLAGS
    dd CHECKSUM

section .bss,nobits
align 4
stack_bottom:
times 16384 db 0
stack_top:

section .text
global loader
loader:
    mov esp, stack_top

    extern kmain
    call kmain
    cli
.loop:
    hlt
    jmp .loop
