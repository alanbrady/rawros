#include "keyboard.h"
#include "io.h"

unsigned short read_keyboard() {
    unsigned short scancode = inb(0x60);
    return scancode;
}
