#include "utils.h"
#include "fb_out_drv.h"
#include "serial.h"

unsigned char isCom1Init = 0;
unsigned char isCom2Init = 0;

unsigned int _strlen(const char* str) {
    unsigned int len = 0;
    while (len < MAX_STR_LEN && *str != '\0') {
        ++str;
        ++len;
    } 
    return len;
}

void printk(const unsigned short out, const char* str,
        const unsigned int len) {
    switch(out) {
        case RPRINT_FB:
            fb_write(str, len);
            break;
        case RPRINT_COM1:
            if (!isCom1Init) {
                serial_init(SERIAL_COM1);
                isCom1Init = 1;
            }
            serial_write_data(str, len, SERIAL_COM1);
            break;
        case RPRINT_COM2:
           if (!isCom2Init) {
               serial_init(SERIAL_COM2);
               isCom2Init = 1;
           } 
           serial_write_data(str, len, SERIAL_COM2);
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
