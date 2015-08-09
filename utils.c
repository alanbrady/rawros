#include "utils.h"
#include "string.h"
#include "fb_out_drv.h"
#include "serial.h"
#include "types.h"
#include "memory.h"

#define MAX_PRINTK_LEN 300

static void printk_uint(const unsigned short out, unsigned int val);
static void printk_int(const unsigned short out, int val);
static void printk_hex8(const unsigned short out, uint8_t val);
static void printk_hex16(const unsigned short out, uint16_t val);
static void printk_hex32(const unsigned short out, uint32_t val);
static void printk_hex64(const unsigned short out, uint64_t val);

static void printk_hex_nibble(const unsigned short out, uint8_t val);

static void printk_char(const unsigned short out, char c);
static void printk_string(const unsigned short out, char* str);

static unsigned char isCom1Init = 0;
static unsigned char isCom2Init = 0;

typedef union {
    unsigned int u;
    int d;
    uint32_t h;
    char* s;
} printk_val_t;

void printk(const unsigned short out, const char* fmt, ...) {
    const char* fmtPtr;
    unsigned int fmtSize;
    unsigned int i;
    printk_val_t val;

    (void)printk_hex8;
    (void)printk_hex16;
    (void)printk_hex64;

    va_list vl;
    va_start(vl, fmt);

    fmtSize = strlen(fmt);
    fmtPtr = fmt;

    for (i = 0; i < fmtSize; ++i) {
        if (*fmtPtr == '\0') {
            /* null char, quit */
            break;
        } else if (*fmtPtr == '%') {
            /* format char escape */
            char type = *(++fmtPtr);
            switch (type) {
                case 'u': /* unsigned int */
                    val.u = va_arg(vl, unsigned int);
                    printk_uint(out, val.u);
                    break;
                case 'd': /* int */
                    val.d = va_arg(vl, int);
                    printk_int(out, val.d);
                    break;
                case 'h': /* 32 bit hex */
                    val.h = va_arg(vl, uint32_t);
                    printk_hex32(out, val.h);
                    break;
                case 's': /* string (char*) */
                    val.s = va_arg(vl, char*);
                    printk_string(out, val.s);
                    break;
            }
            /* since whatever was in the format specifier has taken it's place,
             * adjust the length to reflect the length of chars to actually
             * parse and print */
            fmtSize -= 2;
        } else {
            printk_char(out, *fmtPtr);
        }
        ++fmtPtr;
    }

    va_end(vl);
}

void clrscr() {
    fb_clear();
}


void int_to_str(char* buf, int i) {
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

static void printk_uint(const unsigned short out, unsigned int val) {
    /* largest unsigned number for 0xFFFFFFFF = 4294967295 */
    unsigned int numLen = 11;
    unsigned int div = 1000000000;
    char numBuf[11];
    memset(numBuf, '\0', 11);

    while ((val/div) == 0) {
        --numLen;
        div /= 10;
    }
    numLen -= 2;
    do {
        int mod = val%10;
        char c;
        switch(mod) {
            case 0:
                c = '0';
                break;
            case 1:
                c = '1';
                break;
            case 2:
                c = '2';
                break;
            case 3:
                c = '3';
                break;
            case 4:
                c = '4';
                break;
            case 5:
                c = '5';
                break;
            case 6:
                c = '6';
                break;
            case 7:
                c = '7';
                break;
            case 8:
                c = '8';
                break;
            case 9:
                c = '9';
                break;
            default:
                c = '?';
        }
        numBuf[numLen--] = c;
        val = val/10;
    } while (val != 0);
    printk_string(out, numBuf);
}

static void printk_int(const unsigned short out, int val) {
    if (val < 0) {
        printk_char(out, '-');
        val *= -1;
    }
    printk_uint(out, (unsigned int)val);
}

static void printk_hex8(const unsigned short out, uint8_t val) {
    int i = 0;
    for (; i < 2; ++i) {
        printk_hex_nibble(out, (uint8_t)val);
        val = val >> 4;
    }
}

static void printk_hex16(const unsigned short out, uint16_t val) {
    int i = 0;
    for (; i < 2; ++i) {
        printk_hex_nibble(out, (uint8_t)val);
        val = val >> 4;
    }
}

static void printk_hex32(const unsigned short out, uint32_t val) {
    int i = 0;
    for (; i < 8; ++i) {
        printk_hex_nibble(out, (uint8_t)val);
        val = val >> 4;
    }
}

static void printk_hex64(const unsigned short out, uint64_t val) {
    int i;
    for (i = 0; i < 16; ++i) {
        printk_hex_nibble(out, (uint8_t)val);
        val = val >> 4;
    }
}

static void printk_hex_nibble(const unsigned short out, uint8_t val) {
    switch (val & 0x0F) {
        case 0x0:
            printk_char(out, '0');
            break;
        case 0x1:
            printk_char(out, '1');
            break;
        case 0x2:
            printk_char(out, '2');
            break;
        case 0x3:
            printk_char(out, '3');
            break;
        case 0x4:
            printk_char(out, '4');
            break;
        case 0x5:
            printk_char(out, '5');
            break;
        case 0x6:
            printk_char(out, '6');
            break;
        case 0x7:
            printk_char(out, '7');
            break;
        case 0x8:
            printk_char(out, '8');
            break;
        case 0x9:
            printk_char(out, '9');
            break;
        case 0xa:
            printk_char(out, 'a');
            break;
        case 0xb:
            printk_char(out, 'b');
            break;
        case 0xc:
            printk_char(out, 'c');
            break;
        case 0xd:
            printk_char(out, 'd');
            break;
        case 0xe:
            printk_char(out, 'e');
            break;
        case 0xf:
            printk_char(out, 'f');
            break;
    }
}

static void printk_char(const unsigned short out, char c) {
    switch(out) {
        case PRINTK_FB:
            fb_write_char(c);
            break;
        case PRINTK_COM1:
            if (!isCom1Init) {
                serial_init(SERIAL_COM1);
                isCom1Init = 1;
            }
            serial_write_char(c, SERIAL_COM1);
            break;
        case PRINTK_COM2:
           if (!isCom2Init) {
               serial_init(SERIAL_COM2);
               isCom2Init = 1;
           }
            serial_write_char(c, SERIAL_COM2);
           break;
    }
}

static void printk_string(const unsigned short out, char* str) {
    unsigned int len;

    len = strlen(str);
    switch(out) {
        case PRINTK_FB:
            fb_write_string(str, 3);
            break;
        case PRINTK_COM1:
            if (!isCom1Init) {
                serial_init(SERIAL_COM1);
                isCom1Init = 1;
            }
            serial_write_data(str, len, SERIAL_COM1);
            break;
        case PRINTK_COM2:
           if (!isCom2Init) {
               serial_init(SERIAL_COM2);
               isCom2Init = 1;
           }
            serial_write_data(str, len, SERIAL_COM2);
           break;
    }
}
