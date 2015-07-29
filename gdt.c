#include "gdt.h"

void gdt_set_entry(unsigned int i, unsigned long base, unsigned long limit,
        unsigned char access, unsigned char granularity) {
    gdt_entries[i].base_low = (base & 0xFFFF);
    gdt_entries[i].base_middle = ((base >> 16) & 0xFF);
    gdt_entries[i].base_high = ((base >> 24) & 0xFF);

    gdt_entries[i].limit_low = (limit & 0xFFFF);
    gdt_entries[i].granularity = ((limit >> 16) & 0x0F);

    gdt_entries[i].granularity |= (granularity & 0xF0);
    gdt_entries[i].access = access;
}

void gdt_init() {
    gdt_ptr.size = (sizeof(gdt_entry_t)*NUM_GDT_ENTRIES)-1;
    gdt_ptr.address = (unsigned long)&gdt_entries;

    gdt_set_entry(0, 0, 0, 0, 0);
    gdt_set_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    gdt_set_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    gdt_flush((unsigned long)&gdt_ptr);
}
