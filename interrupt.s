; vim: ft=nasm
%macro ISR_NOERRORCODE 1
    global isr%1
    isr%1:
        cli
        push byte 0
        push byte %1
        jmp isr_common_stub
%endmacro

%macro ISR_ERRORCODE 1
    global isr%1
    isr%1:
        cli
        push byte %1
        jmp isr_common_stub
%endmacro

extern isr_handler

isr_common_stub:
    ; save all the registers, eax, edi, esi ebp, etc.,
    ; by pushing them onto the stack
    pusha
    
    ; push ds onto stack
    mov ax, ds
    push eax

    ; load up kernel segment selector
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call isr_handler
    
    ; reset our registers so we can return control
    pop eax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    popa
    add esp, 8 ; clean up error code and isr on stack
    sti ; return interrupt functioning
    iret

;8, 10-14
ISR_NOERRORCODE 0
ISR_NOERRORCODE 1
ISR_NOERRORCODE 2
ISR_NOERRORCODE 3
ISR_NOERRORCODE 4
ISR_NOERRORCODE 5
ISR_NOERRORCODE 6
ISR_NOERRORCODE 7
ISR_ERRORCODE 8 ; *
ISR_NOERRORCODE 9
ISR_ERRORCODE 10  ;*
ISR_ERRORCODE 11  ;*
ISR_ERRORCODE 12  ;*
ISR_ERRORCODE 13  ;*
ISR_ERRORCODE 14  ;*
ISR_NOERRORCODE 15
ISR_NOERRORCODE 16
ISR_NOERRORCODE 17
ISR_NOERRORCODE 18
ISR_NOERRORCODE 19
ISR_NOERRORCODE 20
ISR_NOERRORCODE 21
ISR_NOERRORCODE 22
ISR_NOERRORCODE 23
ISR_NOERRORCODE 24
ISR_NOERRORCODE 25
ISR_NOERRORCODE 26
ISR_NOERRORCODE 27
ISR_NOERRORCODE 28
ISR_NOERRORCODE 29
ISR_NOERRORCODE 30
ISR_NOERRORCODE 31
ISR_NOERRORCODE 32
ISR_NOERRORCODE 33
ISR_NOERRORCODE 34
ISR_NOERRORCODE 35
ISR_NOERRORCODE 36
ISR_NOERRORCODE 37
ISR_NOERRORCODE 38
ISR_NOERRORCODE 39
ISR_NOERRORCODE 40
ISR_NOERRORCODE 41
ISR_NOERRORCODE 42
ISR_NOERRORCODE 43
ISR_NOERRORCODE 44
ISR_NOERRORCODE 45
