#ifndef UTILS_H
#define UTILS_H

#define PRINTK_FB 1
#define PRINTK_COM1 2
#define PRINTK_COM2 3

typedef unsigned char *va_list;
#define va_start(list, param) (list = (((va_list)&param) + sizeof(param)))
#define va_arg(list, type) (*(type *)((list += sizeof(type)) - sizeof(type)))

void printk(const unsigned short out, const char* fmt, ...);

void clrscr();

void intToStr(int i, char* buf);

#endif
