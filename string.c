#include "string.h"

unsigned int strlen(const char* str) {
    const char* strStart = str;
    while (*(str) != '\0') {++str;}
    return str-strStart;
}

void strcpy(const char* from, char* to) {
    while (*from != '\0') {
        *to++ = *from++;
    }
}
