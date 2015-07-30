#include "fb_out_drv.h"
#include "utils.h"
#include "memory.h"
#include "serial.h"
#include "gdt.h"
#include "idt.h"

// main function loaded through loader.asm
int kmain() {
    gdt_init();
    idt_init();

    char* buf = "aaaa";
    memset(buf+2, 'b', 2);
    printk(PRINTK_FB, buf);
    printk(PRINTK_FB, "Hello!");

    asm volatile("int $0x3");
    asm volatile("int $0x4");

    return 0;
} 
