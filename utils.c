#include "utils.h"
#include "string.h"
#include "fb_out_drv.h"
#include "serial.h"

#define MAX_PRINTK_LEN 300

char printk_buf[MAX_PRINTK_LEN];

unsigned char isCom1Init = 0;
unsigned char isCom2Init = 0;

void printk(const unsigned short out, const char* fmt, ...) {
    va_list vl;
    va_start(vl, fmt);
    /*int val = va_arg(vl, int);*/
    int val = (*(int*)vl);
    int i = 0;
    for (; i < 8; ++i) {
        switch ((val >> (7-i)) & 0x000F) {
            case 0x0:
                fb_write("0", 1);
                break;
            case 0x1:
                fb_write("1", 1);
                break;
            case 0x2:
                fb_write("2", 1);
                break;
            case 0x3:
                fb_write("3", 1);
                break;
            case 0x4:
                fb_write("4", 1);
                break;
            case 0x5:
                fb_write("5", 1);
                break;
            case 0x6:
                fb_write("6", 1);
                break;
            case 0x7:
                fb_write("7", 1);
                break;
            case 0x8:
                fb_write("8", 1);
                break;
            case 0x9:
                fb_write("9", 1);
                break;
            case 0xa:
                fb_write("a", 1);
                break;
            case 0xb:
                fb_write("b", 1);
                break;
            case 0xc:
                fb_write("c", 1);
                break;
            case 0xd:
                fb_write("d", 1);
                break;
            case 0xe:
                fb_write("e", 1);
                break;
            case 0xf:
                fb_write("f", 1);
                break;
        }
        /*val = val >> 1;*/
    }
    /*va_end;*/

    unsigned int len = strlen(fmt);
    switch(out) {
        case PRINTK_FB:
            fb_write(fmt, len);
            break;
        case PRINTK_COM1:
            if (!isCom1Init) {
                serial_init(SERIAL_COM1);
                isCom1Init = 1;
            }
            serial_write_data(fmt, len, SERIAL_COM1);
            break;
        case PRINTK_COM2:
           if (!isCom2Init) {
               serial_init(SERIAL_COM2);
               isCom2Init = 1;
           } 
           serial_write_data(fmt, len, SERIAL_COM2);
           break;
    }
}

void clrscr() {
    fb_clear();
}


void intToStr(int i, char* buf) {
    do {
        int mod = i%10;
        switch(mod) {
            case 0:
                buf = "0";
                break;
            case 1:
                buf = "1";
                break;
            case 2:
                buf = "2";
                break;
            case 3:
                buf = "3";
                break;
            case 4:
                buf = "4";
                break;
            case 5:
                buf = "5";
                break;
            case 6:
                buf = "6";
                break;
            case 7:
                buf = "7";
                break;
            case 8:
                buf = "8";
                break;
            case 9:
                buf = "9";
                break;
        }
        buf++;
        i = i/10;
    } while (i != 0);
    buf = '\0';
}
