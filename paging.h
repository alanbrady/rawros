#ifndef PAGING_H
#define PAGING_H

#include "types.h"

#define PDE_PRESENT         0x01;
#define PDE_RW              0x02;
#define PDE_USER            0x04;
#define PDE_WRITETHROUGH    0x08;
#define PDE_CACHE_DISABLED  0x10;
#define PDE_ACCESSED        0x20;
#define PDE_4MB             0x80;

#define PTE_PRESENT         0x01;
#define PTE_RW              0x02;
#define PTE_USER            0x04;
#define PTE_WRITETHROUGH    0x08;
#define PTE_CACHE_DISABLED  0x10;
#define PTE_ACCESSED        0x20;
#define PTE_DIRTY           0x40;
#define PTE_ATTR_INDEX      0x80;

struct _page_entry_t {
    uint16_t addr_high;
    uint8_t addr_low;
    uint8_t flags;
} __attribute__((packed));
typedef struct _page_entry_t page_entry_t;

void page_set_entry(page_entry_t* pe, uint32_t addr, uint8_t flags);

#endif
