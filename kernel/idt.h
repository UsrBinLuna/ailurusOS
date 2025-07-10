#ifndef IDT_H
#define IDT_H

#include <stdint.h>
#include <stdbool.h>

#define IDT_MAX_DESCRIPTORS 256

typedef struct {
	uint16_t    isr_low;
	uint16_t    kernel_cs;    // The GDT segment selector that the CPU will load into CS before calling the ISR
	uint8_t	    ist;          // The IST in the TSS that the CPU will load into RSP; set to zero for now
	uint8_t     attributes;
	uint16_t    isr_mid;
	uint32_t    isr_high;
	uint32_t    reserved;     // zero
} __attribute__((packed)) idt_entry_t;

typedef struct {
	uint16_t	limit;
	uint64_t	base;
} __attribute__((packed)) idtr_t;

__attribute__((aligned(0x10))) static idt_entry_t idt[256];
static bool vectors[IDT_MAX_DESCRIPTORS];
extern void* isr_stub_table[];

void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags);
void idt_init(void);
void irq_install(void);

#endif // IDT_H
