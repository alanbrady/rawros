/*#include "framebuffer.h"*/
/*#include "serial.h"*/
/*#include "utils.h"*/
/*#include "memory.h"*/
#include "fb_out_drv.h"
#include "utils.h"
#include "memory.h"
#include "serial.h"

// main function loaded through loader.asm
int kmain() {
    /*const char* out = "hello serial!\n";*/
    /*rprintf(RPRINT_COM1, out, _strlen(out));*/
    /*clrscr();*/
    /*out = "hello frame buffer!\n";*/
    /*printk(RPRINT_FB, out, _strlen(out)); */
    /*printk(RPRINT_FB, "test2\n", _strlen("test2\n"));*/
    /*printk(RPRINT_FB, "test3", _strlen("test3"));*/
    /*printk(RPRINT_FB, " test4\n", _strlen(" test4\n"));*/

    /*printk(RPRINT_COM2, "test", _strlen("test"));*/

    // TODO - implement memory allocs needed (?) 
    /*char* buf;*/
    /*intToStr(3, buf);*/
    /*rprintf(RPRINT_FB, buf, _strlen(buf));*/

    /*const char* buf = "aaaa";*/
    /*int ret = memset(buf, '\0', 1);*/
    int ret = memread(0xFFFFFFFF);
    serial_write_int(ret, SERIAL_COM1);

    /*ret = memread(buf+4);*/
    /*serial_write(ret, SERIAL_COM1);*/
    /*ret = memread(buf+5);*/
    /*serial_write(ret, SERIAL_COM1);*/
    /*ret = memread(buf+6);*/
    /*serial_write(ret, SERIAL_COM1);*/
    /*printk(PRINTK_FB, "test", ret);*/
    /*if (ret == 0) {*/
        /*printk(PRINTK_FB, "is zero ");*/
    /*} else {*/
        /*printk(PRINTK_FB, "is not zero ");*/
    /*}*/
    /*fb_write(i, 4);*/
    /*fb_write(buf, 4);*/
    printk(PRINTK_FB, "-", ret);


    return 0;
} 
