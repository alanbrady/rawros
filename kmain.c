/*#include "framebuffer.h"*/
/*#include "serial.h"*/
#include "utils.h"
/*#include "fb_out_drv.h"*/

// main function loaded through loader.asm
int kmain() {
    const char* out = "hello serial!\n";
    /*rprintf(RPRINT_COM1, out, _strlen(out));*/
    clrscr();
    out = "hello frame buffer!\n";
    printk(RPRINT_FB, out, _strlen(out)); 
    printk(RPRINT_FB, "test2\n", _strlen("test2\n"));
    printk(RPRINT_FB, "test3", _strlen("test3"));
    printk(RPRINT_FB, " test4\n", _strlen(" test4\n"));

    // TODO - implement memory allocs needed (?) 
    /*char* buf;*/
    /*intToStr(3, buf);*/
    /*rprintf(RPRINT_FB, buf, _strlen(buf));*/

    return 0;
} 
