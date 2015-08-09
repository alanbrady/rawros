#include "utils.h"
#include "memory.h"
#include "gdt.h"
#include "idt.h"

// main function loaded through loader.asm
int kmain(multiboot_info_t* mbi, uint32_t magic) {
    (void)magic; /* TODO: check if multiboot loader magic number is correct */

    gdt_init();
    idt_init();
    clrscr();

    multiboot_memory_map_t* mmap = (multiboot_memory_map_t*)mbi->mmap_addr;
    unsigned int mem_index = 0;
    while ((uint32_t)mmap < (mbi->mmap_addr + mbi->mmap_length)) {
        printk(PRINTK_FB, "memory %u: type:%u base: %H length: %H\n",
                mem_index++, mmap->type, mmap->base_addr, mmap->length);

        mmap = (multiboot_memory_map_t*) ((uint32_t)mmap + mmap->size +
                sizeof(uint32_t));
    }


    asm volatile("int $0x3");
    asm volatile("int $0x4");

    return 0;
}
