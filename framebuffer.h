#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

// Frame buffer defines
#define FB_BLACK            0
#define FB_BLUE             1
#define FB_GREEN            2
#define FB_CYAN             3
#define FB_RED              4
#define FB_MAGENTA          5
#define FB_BROWN            6
#define FB_LIGHTGREY        7
#define FB_DARKGREY         8
#define FB_LIGHTBLUE        9
#define FB_LIGHTGREEN       10
#define FB_LIGHTCYAN        11
#define FB_LIGHTRED         12
#define FB_LIGHTMAGENTA     13
#define FB_LIGHTBROWN       14
#define FB_WHTIE            15

// Frame buffer port defines
#define FB_COMMAND_PORT     0x3D4
#define FB_DATA_PORT        0x3D5

// Frame buffer port commands
#define FB_HIGH_BYTE_COMM   14
#define FB_LOW_BYTE_COMM    15

void fb_write_cell(const unsigned int cell, char c, 
        unsigned char fg, unsigned char bg);

void fb_write_cell_string(const unsigned int cell, const char* str, 
        unsigned char fg, unsigned char bg);

void fb_write_cell_data(const unsigned int cell, const char* data, 
        const unsigned int len, unsigned char fg, unsigned char bg); 

void fb_move_cursor(const unsigned short pos);

#endif
