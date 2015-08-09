#ifndef SYSTEM_H
#define SYSTEM_H

#include "types.h"


extern void gdt_flush(intptr_t p);

extern void idt_flush(intptr_t p);

#endif 
