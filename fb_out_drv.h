#ifndef FB_OUT_DRV_H
#define FB_OUT_DRV_H

#define ROW_WIDTH 160 
#define ROW_HEIGHT 30

void fb_write_string(const char* str, unsigned int len);

void fb_write_char(const char c);

void fb_clear();

#endif
