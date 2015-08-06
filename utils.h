#ifndef UTILS_H
#define UTILS_H

#include "types.h"

#define PRINTK_FB 1
#define PRINTK_COM1 2
#define PRINTK_COM2 3

void printk(const unsigned short out, const char* fmt, ...);

void clrscr();

void intToStr(int i, char* buf);

#endif
