#include "fb_cursor_drv.h"
#include "framebuffer.h"

void fb_set_cursor(unsigned short row, unsigned short col) {
    unsigned short pos = row*FB_WIDTH;
    pos += col;
    fb_move_cursor(pos);
}

void fb_set_cursor_pos(unsigned short pos) {
    /* TODO: add bounds checking */
    fb_move_cursor(pos);
}
