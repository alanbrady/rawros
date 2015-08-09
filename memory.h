#ifndef MEMORY_H
#define MEMORY_H

#include "types.h"
struct multiboot_info
{
    uint32_t flags;
    uint32_t mem_lower;
    uint32_t mem_upper;
    uint32_t boot_device;
    uint32_t cmdline;
    uint32_t mods_count;
    uint32_t mods_addr;
    uint32_t num;
    uint32_t size;
    uint32_t addr;
    uint32_t shndx;
    uint32_t mmap_length;
    uint32_t mmap_addr;
} __attribute__((packed));
typedef struct multiboot_info multiboot_info_t;

struct _multiboot_memory_map {
    uint32_t size;
    uint64_t base_addr;
    uint64_t length;
    uint32_t type;
} __attribute__((packed));
typedef struct _multiboot_memory_map multiboot_memory_map_t;

extern int memset(const void* dest, unsigned char c,
       const unsigned long int len);

extern int memread(int a);

#endif
