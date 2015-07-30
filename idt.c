#include "idt.h"

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

void idt_init() {
    idt_ptr.size = sizeof(idt_entry_t)*NUM_IDT_ENTRIES - 1;
    idt_ptr.address = (unsigned long)&idt;

    idt_set_entry( 0,   (unsigned long)&isr0,   0x08, 0x8E);
    idt_set_entry( 1,   (unsigned long)&isr1,   0x08, 0x8E);
    idt_set_entry( 2,   (unsigned long)&isr2,   0x08, 0x8E);
    idt_set_entry( 3,   (unsigned long)&isr3,   0x08, 0x8E);
    idt_set_entry( 4,   (unsigned long)&isr4,   0x08, 0x8E);
    idt_set_entry( 5,   (unsigned long)&isr5,   0x08, 0x8E);
    idt_set_entry( 6,   (unsigned long)&isr6,   0x08, 0x8E);
    idt_set_entry( 7,   (unsigned long)&isr7,   0x08, 0x8E);
    idt_set_entry( 8,   (unsigned long)&isr8,   0x08, 0x8E);
    idt_set_entry( 9,   (unsigned long)&isr9,   0x08, 0x8E);
    idt_set_entry( 10,  (unsigned long)&isr10,  0x08, 0x8E);
    idt_set_entry( 11,  (unsigned long)&isr11,  0x08, 0x8E);
    idt_set_entry( 12,  (unsigned long)&isr12,  0x08, 0x8E);
    idt_set_entry( 13,  (unsigned long)&isr13,  0x08, 0x8E);
    idt_set_entry( 14,  (unsigned long)&isr14,  0x08, 0x8E);
    idt_set_entry( 15,  (unsigned long)&isr15,  0x08, 0x8E);
    idt_set_entry( 16,  (unsigned long)&isr16,  0x08, 0x8E);
    idt_set_entry( 17,  (unsigned long)&isr17,  0x08, 0x8E);
    idt_set_entry( 18,  (unsigned long)&isr18,  0x08, 0x8E);
    idt_set_entry( 19,  (unsigned long)&isr19,  0x08, 0x8E);
    idt_set_entry( 20,  (unsigned long)&isr20,  0x08, 0x8E);
    idt_set_entry( 21,  (unsigned long)&isr21,  0x08, 0x8E);
    idt_set_entry( 22,  (unsigned long)&isr22,  0x08, 0x8E);
    idt_set_entry( 23,  (unsigned long)&isr23,  0x08, 0x8E);
    idt_set_entry( 24,  (unsigned long)&isr24,  0x08, 0x8E);
    idt_set_entry( 25,  (unsigned long)&isr25,  0x08, 0x8E);
    idt_set_entry( 26,  (unsigned long)&isr26,  0x08, 0x8E);
    idt_set_entry( 27,  (unsigned long)&isr27,  0x08, 0x8E);
    idt_set_entry( 28,  (unsigned long)&isr28,  0x08, 0x8E);
    idt_set_entry( 29,  (unsigned long)&isr29,  0x08, 0x8E);
    idt_set_entry( 30,  (unsigned long)&isr30,  0x08, 0x8E);
    idt_set_entry( 31,  (unsigned long)&isr31,  0x08, 0x8E);

    idt_flush((unsigned long)&idt_ptr);
}

void idt_set_entry(unsigned int i, unsigned int address, unsigned int sel,
        unsigned short flags) {
    idt[i].base_low = address & 0xFFFF;
    idt[i].base_high = (address >> 16) & 0xFFFF;
    idt[i].sel = sel;
    idt[i].flags = flags; /* need to OR 0x60 in user mode */
    idt[i].always0 = 0;
}
