; vim: set ft=nasm:
global memset
memset:
    push ebp
    mov ebp, esp
    ;mov eax, [ebp+8]
    mov bl, [ebp+11]
    cmp bl, 0x1
    je atoOne
    xor eax, eax
    leave
    ret
atoOne:
    mov eax, 0x0001
    leave
    ret
    ;mov bl,  [ebp+9]
    ;and ebx, 0x000F
    ;mov ecx, [ebp+13]
    ;xor edx, edx
;loop:
    ;test ecx, ecx
    ;je done
    ;mov [eax], ebx
    ;add eax, 4
    ;dec ecx
    ;jmp loop
;done:
    leave
    ret

global memread
memread:
    push ebp
    mov ebp, esp
    mov eax, [ebp+8]
    leave
    ret
    
