; vim: set ft=nasm
global memset
memset:
    push ebp
    mov ebp, esp
    mov edi, [ebp+8]
    mov al, [ebp+12]
    mov ecx, [ebp+16]
    rep stosb
    leave
    ret

global memread
memread:
    push ebp
    mov ebp, esp
    mov eax, [ebp+8]
    leave
    ret

