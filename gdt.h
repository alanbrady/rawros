#ifndef GDT_H
#define GDT_H

#define NUM_GDT_ENTRIES 3

struct _gdt_ptr_t {
    unsigned short size;
    unsigned int address;
} __attribute__((packed));
typedef struct _gdt_ptr_t gdt_ptr_t;

typedef struct {
    unsigned short limit_low;
    unsigned short base_low;
    unsigned char base_middle;
    unsigned char access;
    unsigned char granularity;
    unsigned char base_high;
} __attribute__((packed)) gdt_entry_t;

gdt_entry_t gdt_entries[NUM_GDT_ENTRIES];

gdt_ptr_t gdt_ptr;

extern void gdt_flush(unsigned long g);

void gdt_set_entry(unsigned int i, unsigned long base, unsigned long limit,
        unsigned char access, unsigned char granularity);

void gdt_init();

#endif
