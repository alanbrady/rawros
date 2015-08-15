#include "paging.h"

void page_set_entry(page_entry_t* pe, uint32_t addr, uint8_t flags) {
    pe->addr_low = (uint8_t)((addr << 4) & 0xF0);
    pe->addr_high = (uint16_t)(addr >> 4);
    pe->flags = flags;
}

