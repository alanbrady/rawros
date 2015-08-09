#include "framebuffer.h"
#include "io.h"

char* fb = (char*)0x000b8000; // frame buffer/address

/**
 * fb_write_cell
 *  Write the given data to a given cell with the given
 *  foreground and background colors
 *
 *  @param cell Cell to write to
 *  @param c Character to write
 *  @param fg Foreground color
 *  @param bg Background color
 *  **/
void fb_write_cell(const unsigned int cell, char c, 
        unsigned char fg, unsigned char bg) {
    fb[cell] = c;
    fb[cell+1] = ((bg & 0x0F) << 4) | (fg & 0x0F);
}

/**
 * fb_write_cell_string
 *  Write the given string to a given cell with the given
 *  foreground and background colors
 *
 *  @param cell Cell to write to
 *  @param str String to write, must be null terminated
 *  @param fg Foreground color
 *  @param bg Background color
 *  **/
void fb_write_cell_string(const unsigned int cell, const char* str, 
        unsigned char fg, unsigned char bg) {
    unsigned int i = cell;
    while (*str != '\0') {
        fb_write_cell(i, *str, fg, bg);
        i += 2;
        ++str;
    }
}

/**
 * fb_write_cell_data
 *  Write the given data array to a given cell with the given
 *  foreground and background colors with the given length
 *
 *  @param cell Cell to write to
 *  @param data Data to write to frame buffer
 *  @param len Length of data to write from data array
 *  @param fg Foreground color
 *  @param bg Background color
 *  **/
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
    outb(FB_DATA_PORT, (unsigned char)((pos >> 8) & 0xFF));
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMM);
    outb(FB_DATA_PORT, (unsigned char)(pos & 0xFF));
}

