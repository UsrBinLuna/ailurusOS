#include "idt.h"
#include "draw/font/draw_text.h"

__attribute__((aligned(0x10))) static idt_entry_t idt[256];
static idtr_t idtr;

extern void irq1_stub(void);

void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags) {
    idt_entry_t* descriptor = &idt[vector];

    descriptor->isr_low        = (uint64_t)isr & 0xFFFF;
    descriptor->kernel_cs      = 0x08;
    descriptor->ist            = 0;
    descriptor->attributes     = flags;
    descriptor->isr_mid        = ((uint64_t)isr >> 16) & 0xFFFF;
    descriptor->isr_high       = ((uint64_t)isr >> 32) & 0xFFFFFFFF;
    descriptor->reserved       = 0;
}

void idt_init() {
    kprint("[ IDT ] Initializing IDT");
    idtr.base = (uintptr_t)&idt[0];
    idtr.limit = (uint16_t)sizeof(idt_entry_t) * IDT_MAX_DESCRIPTORS - 1;

    for (uint8_t vector = 0; vector < 32; vector++) {
        idt_set_descriptor(vector, isr_stub_table[vector], 0x8E);
        vectors[vector] = true;
    }

    __asm__ volatile ("lidt %0" : : "m"(idtr));
    kprint("[ IDT ] Loaded IDT");
    __asm__ volatile ("sti");
}

void irq_install() {
    idt_set_descriptor(0x21, irq1_stub, 0x8E); // 0x8E = interrupt gate
}