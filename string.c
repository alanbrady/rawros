#include "string.h"

unsigned int strlen(const char* str) {
    unsigned int len = 0;
    while (len < MAX_STR_LEN && *str != '\0') {
        ++str;
        ++len;
    } 
    return len;
}

void strcpy(const char* from, char* to) {
    while (*from != '\0') {
        *to++ = *from++;
    }
}
