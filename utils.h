#ifndef UTILS_H
#define UTILS_H

#define MAX_STR_LEN 1000

#define RPRINT_FB 1
#define RPRINT_COM1 2

unsigned int _strlen(const char* str);

void rprintf(const unsigned short out, const char* str, const unsigned int len);

void clrscr();

void intToStr(int i, char* buf);

#endif
