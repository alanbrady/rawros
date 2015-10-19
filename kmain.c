#include "utils.h"
#include "memory.h"
#include "gdt.h"
#include "idt.h"
#include "string.h"
#include "paging.h"
#include "pic.h"
#include "framebuffer.h"

static void print_memory_info(multiboot_info_t* mbi);

// main function loaded through loader.asm
int kmain(multiboot_info_t* mbi, uint32_t magic) {
    (void)magic; /* TODO: check if multiboot loader magic number is correct */


    gdt_init();
    idt_init();

    pic_init();
    pic_set_mask(PIC1_KBD_IRQ, PIC_NO_IRQ);

    asm volatile("sti");

    fb_enable_cursor();
    clrscr();

    printk(PRINTK_FB, "Cursor position: %u\n", fb_get_cursor());

    printk(PRINTK_FB, "Cursor start: %h\n",
            (unsigned int)(fb_get_cursor_start()));

    printk(PRINTK_FB, "Cursor end:   %h\n",
            (unsigned int)(fb_get_cursor_end()));

    printk(PRINTK_FB, "Frame buffer address: %h\n", fb_get_start_address());

    print_memory_info(mbi);

    printk(PRINTK_FB, "bitsize - char:  %u\n", sizeof(char)*8);
    printk(PRINTK_FB, "bitsize - short: %u\n", sizeof(short)*8);
    printk(PRINTK_FB, "bitsize - int:   %u\n", sizeof(int)*8);
    printk(PRINTK_FB, "bitsize - long:  %u\n", sizeof(long)*8);
    printk(PRINTK_FB, "sizeof page_entry_t: %u\n", sizeof(page_entry_t));

    for (;;) {
        asm volatile("hlt");
    }

    return 0;
}

static void print_memory_info(multiboot_info_t* mbi) {
    multiboot_memory_map_t* mmap = (multiboot_memory_map_t*)mbi->mmap_addr;
    unsigned int mem_index = 0;
    const char* headerStr = "| ID | Type | base               | \
length             |\n";
    const unsigned int headerLen = strlen(headerStr);
    unsigned int i;

    printk(PRINTK_FB, "Memory:\n");
    printk(PRINTK_FB, headerStr);
    for (i = 0; i < headerLen; ++i) {
        printk(PRINTK_FB, "-");
    }
    printk(PRINTK_FB, "\n");
    while ((uint32_t)mmap < (mbi->mmap_addr + mbi->mmap_length)) {
        printk(PRINTK_FB, "| %u  | %u    | %H | %H |\n",
                mem_index++, mmap->type, mmap->base_addr, mmap->length);

        mmap = (multiboot_memory_map_t*) ((uint32_t)mmap + mmap->size +
                sizeof(uint32_t));
    }
}
