; vim: ft=nasm
global outb
outb:
    push eax
    push edx
    mov al, [esp + 8]
    mov dx, [esp + 4]
    out dx, al
    pop edx
    pop eax
    ret

global inb
inb:
    push edx
    mov dx, [esp + 4]
    in al, dx
    pop edx
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
