#ifndef ISR_H
#define ISR_H

typedef struct {
    unsigned long ds;
    unsigned long edi, ebp, esp, ebx, edx, ecx, eax;
    unsigned long int_no, err_code;
    unsigned long eip, cs, eflags, useresp, ss;
} registers_t;

void isr_handler(registers_t regs);

#endif
