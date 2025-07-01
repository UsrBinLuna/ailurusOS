#ifndef GDT_H
#define GDT_H

#include <stdint.h>

#define GDT_ENTRIES 6

struct GDT {
    uint16_t limit;
    uint32_t base;
    uint8_t access_byte;
    uint8_t flags;
};

struct __attribute__((packed)) GDTR {
    uint16_t limit;
    uint64_t base;
};

void encodeGdtEntry(uint8_t *target, struct GDT source);
void fillGdt(void);
void loadGdt(void);
void reload_segments(void);

extern uint8_t gdt[GDT_ENTRIES][8];

#endif // GDT_H
