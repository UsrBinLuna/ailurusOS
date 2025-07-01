#include <stdint.h>
#include "gdt.h"
#include "../lib/error.h"

uint8_t gdt[GDT_ENTRIES][16];

void encodeGdtEntry(uint8_t *target, struct GDT source) {
    if (source.limit > 0xFFFFF) {kerror("GDT cannot encode limits larger than 0xFFFFF");}
    
    // encode limit
    target[0] = source.limit & 0xFF;
    target[1] = (source.limit >> 8) & 0xFF;
    target[6] = (source.limit >> 16) & 0x0F;
    
    // encode base
    target[2] = source.base & 0xFF;
    target[3] = (source.base >> 8) & 0xFF;
    target[4] = (source.base >> 16) & 0xFF;
    target[7] = (source.base >> 24) & 0xFF;
    
    // encode access byte
    target[5] = source.access_byte;
    
    // encode flags
    target[6] |= (source.flags << 4);
}

void fillGdt() {

    // static structs
    struct GDT null_descriptor = {
        .limit = 0x0,
        .base = 0x0,
        .access_byte = 0x0,
        .flags = 0x0
    };

    struct GDT kernel_code_seg = {
        .limit = 0xFFFFF,
        .base = 0x0,
        .access_byte = 0x9A,
        .flags = 0xA
    };

    struct GDT kernel_data_seg = {
        .limit = 0xFFFFF,
        .base = 0x0,
        .access_byte = 0x92,
        .flags = 0xC
    };

    struct GDT user_code_seg = {
        .limit = 0xFFFFF,
        .base = 0x0,
        .access_byte = 0xFA,
        .flags = 0xA
    };

    struct GDT user_data_seg = {
        .limit = 0xFFFFF,
        .base = 0x0,
        .access_byte = 0xF2,
        .flags = 0xC
    };

    encodeGdtEntry(gdt[0], null_descriptor);
    encodeGdtEntry(gdt[1], kernel_code_seg);
    encodeGdtEntry(gdt[2], kernel_data_seg);
    encodeGdtEntry(gdt[3], user_code_seg);
    encodeGdtEntry(gdt[4], user_data_seg);
}

void loadGdt() {
    struct GDTR gdtr = {
        .limit = sizeof(gdt) - 1,
        .base = (uint64_t)&gdt
    };

    asm volatile ("lgdt %0" : : "m"(gdtr));
}

extern void reload_cs_label(void);

void reload_segments(void) {
    asm volatile (
        "pushq $0x08\n\t"
        "pushq %0\n\t"
        "lretq\n\t"
        :
        : "r"(reload_cs_label)
        : "memory"
    );
}

void reload_cs_label(void) {
    asm volatile (
        "mov $0x10, %%ax\n\t"
        "mov %%ax, %%ds\n\t"
        "mov %%ax, %%es\n\t"
        "mov %%ax, %%fs\n\t"
        "mov %%ax, %%gs\n\t"
        "mov %%ax, %%ss\n\t"
        :
        :
        : "ax"
    );
}
