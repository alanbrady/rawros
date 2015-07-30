#ifndef IDT_H
#define IDT_H

#include "system.h"

#define NUM_IDT_ENTRIES 256

typedef struct { 
    unsigned short base_low;
    unsigned short sel;
    unsigned char always0;
    unsigned char flags;
    unsigned short base_high;
} __attribute__((packed)) idt_entry_t;

typedef struct {
    unsigned short size;
    unsigned long address;
} __attribute__((packed)) idt_ptr_t;

idt_entry_t idt[256];
idt_ptr_t idt_ptr;

void idt_init();

void idt_set_entry(unsigned int i, unsigned int address, unsigned int sel,
        unsigned short flags);

#endif
