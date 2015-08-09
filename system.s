; vim: ft=nasm
global gdt_flush
gdt_flush:
    mov eax, [esp+4]
    lgdt [eax]
    xor eax, eax
    mov ax, 0x10
    mov ss, ax
    mov es, ax
    mov ds, ax
    mov fs, ax
    mov gs, ax
    jmp 0x08:flush2
flush2:
    ret

global idt_flush
idt_flush:
    mov eax, [esp+4]
    lidt [eax]
    ret

