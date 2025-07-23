#define PIC1		    0x20		
#define PIC2		    0xA0		
#define PIC1_COMMAND	PIC1
#define PIC1_DATA	    (PIC1+1)
#define PIC2_COMMAND	PIC2
#define PIC2_DATA	    (PIC2+1)

// command codes
#define PIC_EOI		    0x20 // end of interrupt

#include <stdint.h>
#include "draw/font/draw_text.h"
#include "io.h"

void PIC_sendEOI(uint8_t irq) {
	if(irq >= 8)
		outb(PIC2_COMMAND,PIC_EOI);
	
	outb(PIC1_COMMAND,PIC_EOI);
}

#define ICW1_ICW4	        0x01
#define ICW1_SINGLE	        0x02
#define ICW1_INTERVAL4  	0x04
#define ICW1_LEVEL	        0x08
#define ICW1_INIT	        0x10

#define ICW4_8086	        0x01
#define ICW4_AUTO	        0x02
#define ICW4_BUF_SLAVE	    0x08
#define ICW4_BUF_MASTER	    0x0C
#define ICW4_SFNM	        0x10

void PIC_remap(int offset1, int offset2) {
    kprint("[ PIC ] Offsets set\n");
	outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
	io_wait();
	outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
	io_wait();
	outb(PIC1_DATA, offset1);
	io_wait();
	outb(PIC2_DATA, offset2);
	io_wait();
	outb(PIC1_DATA, 4);
	io_wait();
	outb(PIC2_DATA, 2);
	io_wait();
	
	outb(PIC1_DATA, ICW4_8086);
	io_wait();
	outb(PIC2_DATA, ICW4_8086);
	io_wait();

	// Unmask both PICs.
	outb(PIC1_DATA, 0);
	outb(PIC2_DATA, 0);
    kprint("[ PIC ] Unmasked PIC\n");
}

void PIC_disable(void) {
    outb(PIC1_DATA, 0xff);
    outb(PIC2_DATA, 0xff);
}

void IRQ_set_mask(uint8_t IRQline) {
    uint16_t port;
    uint8_t value;

    if(IRQline < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        IRQline -= 8;
    }
    value = inb(port) | (1 << IRQline);
    outb(port, value);        
}

void IRQ_clear_mask(uint8_t IRQline) {
    uint16_t port;
    uint8_t value;

    if(IRQline < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        IRQline -= 8;
    }
    value = inb(port) & ~(1 << IRQline);
    outb(port, value);        
}

#define PIC_READ_IRR                0x0a
#define PIC_READ_ISR                0x0b

/* helper */
static uint16_t __PIC_get_irq_reg(int ocw3) {
    outb(PIC1_COMMAND, ocw3);
    outb(PIC2_COMMAND, ocw3);
    return (inb(PIC2_COMMAND) << 8) | inb(PIC1_COMMAND);
}

uint16_t PIC_get_irr(void) {
    return __PIC_get_irq_reg(PIC_READ_IRR);
}

uint16_t PIC_get_isr(void) {
    return __PIC_get_irq_reg(PIC_READ_ISR);
}