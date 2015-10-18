; vim: ft=nasm
global outb
outb:
    mov al, [esp + 8]
    mov dx, [esp + 4]
    out dx, al
    ret

global inb
inb:
    mov dx, [esp + 4]
    in al, dx
    ret

global io_wait
io_wait:
    push eax ; prevent clobbering our regs
    push edx
    mov dx, 0x80
    mov al, 0x0
    out dx,  al
    pop edx  ; restore regs
    pop eax
    ret
