#ifndef SYSTEM_H
#define SYSTEM_H

#include "types.h"

struct _raminfo_t {
    uint64_t base;
    uint64_t size;
    uint32_t type;
    uint32_t acpi3ext;
} __attribute((packed));
typedef struct _raminfo_t raminfo_t;

extern void gdt_flush(intptr_t p);

extern void idt_flush(intptr_t p);

extern unsigned int get_raminfo(intptr_t p);

#endif 
