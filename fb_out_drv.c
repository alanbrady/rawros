#include "fb_out_drv.h"
#include "framebuffer.h"
#include "fb_cursor_drv.h"

unsigned short fb_curr_pos = 0;

void fb_write(const char* str, unsigned int len) {
    unsigned int i = 0;
    for (; i < len; ++i) {
        if (*str == '\n') {
            fb_curr_pos += (ROW_WIDTH-(fb_curr_pos%ROW_WIDTH));
        } else {
            fb_write_cell(fb_curr_pos, *str, FB_LIGHTGREY, FB_BLACK);
            fb_curr_pos+=2;
        }
        ++str;
    }
    fb_set_cursor_pos(fb_curr_pos/2);
}

void fb_clear() {
    unsigned int i, k;
    for (i = 0; i < ROW_HEIGHT; ++i) {
        for (k = 0; k < ROW_WIDTH; k+=2) {
            fb_write_cell((i*ROW_HEIGHT)+k, '\0', FB_LIGHTGREY, FB_BLACK);
        }
    }
}
