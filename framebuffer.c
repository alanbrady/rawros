#include "framebuffer.h"
#include "io.h"

char* fb = (char*)0x000b8000; // frame buffer/address

void fb_write_cell(const unsigned int cell, char c, 
        unsigned char fg, unsigned char bg) {
    fb[cell] = c;
    fb[cell+1] = ((bg & 0x0F) << 4) | (fg & 0x0F);
}

void fb_write_cell_string(const unsigned int cell, const char* str, 
        unsigned char fg, unsigned char bg) {
    unsigned int i = cell;
    while (*str != '\0') {
        fb_write_cell(i, *str, fg, bg);
        i += 2;
        ++str;
    }
}

void fb_write_cell_data(const unsigned int cell, 
        const char* data, const unsigned int len, 
        unsigned char fg, unsigned char bg) {
    unsigned int i = cell;
    const char* dataEnd = data+len;
    while (data < dataEnd) {
        fb_write_cell(i, *data, fg, bg);
        i+=2;
        ++data;
    }
}

void fb_move_cursor(const unsigned short pos) {
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMM);
    outb(FB_DATA_PORT, (unsigned char)((pos >> 8) & 0x00FF));
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMM);
    outb(FB_DATA_PORT, (unsigned char)(pos & 0x00FF));
}

unsigned short fb_get_cursor() {
    unsigned short pos = 0;
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMM);
    pos = inb(FB_DATA_PORT);
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMM);
    pos = (inb(FB_DATA_PORT) << 8) | pos;
    return pos;
}

unsigned char fb_get_cursor_start() {
    outb(FB_COMMAND_PORT, FB_CURSOR_START);
    return inb(FB_DATA_PORT);
}

unsigned char fb_get_cursor_end() {
    outb(FB_COMMAND_PORT, FB_CURSOR_END);
    return inb(FB_DATA_PORT);
}

unsigned int fb_get_start_address() {
    unsigned int addr = 0;
    outb(FB_COMMAND_PORT, FB_START_ADDR_LOW);
    addr = inb(FB_DATA_PORT);
    outb(FB_COMMAND_PORT, FB_START_ADDR_HI);
    addr = (inb(FB_DATA_PORT)<<8) | addr;
    return addr;
}

void fb_enable_cursor() {
    outb(FB_COMMAND_PORT, FB_CURSOR_START);
    unsigned char curstart = inb(FB_DATA_PORT) & 0x1F;

    outb(FB_COMMAND_PORT, FB_CURSOR_START);
    outb(FB_DATA_PORT, curstart & ~0x20);
}
