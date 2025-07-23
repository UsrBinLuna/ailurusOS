#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "boot/limine.h"
#include "memory.h"
#include "draw/framebuffer.h"
#include "draw/font/draw_text.h"
#include "interrupts/ps2.h"
#include "interrupts.h"
#include "gdt.h"
#include "idt.h"
#include "pic.h"
#include "io.h"
#include "../lib/syscalls.h"

// limine boot stuff
__attribute__((used, section(".limine_requests")))
static volatile LIMINE_BASE_REVISION(3);

__attribute__((used, section(".limine_requests_start")))
static volatile LIMINE_REQUESTS_START_MARKER;

__attribute__((used, section(".limine_requests_end")))
static volatile LIMINE_REQUESTS_END_MARKER;

// kernel entry point //
void kernel_entry(void) {
    if (LIMINE_BASE_REVISION_SUPPORTED == false) {
        hcf();
    }

    if (framebuffer_request.response == NULL
        || framebuffer_request.response->framebuffer_count < 1) {
            hcf();
    }

    struct limine_framebuffer *framebuffer = framebuffer_request.response->framebuffers[0];

    bool interrupts = are_interrupts_enabled();
    if (interrupts) {
        kprint("[ GDT ] Interrupts enabled: TRUE\n");
    } else {
        kprint("[ GDT ] Interrupts enabled: FALSE\n");
    }

    unsigned long f;
    
    if (interrupts) {
        kprint("[ GDT ] Disabling interrupts\n");
        f = save_irqdisable();
    }

    fillGdt();
    kprint("[ GDT ] Populating GDT\n");
    loadGdt();
    kprint("[ GDT ] Loading GDT\n");
    reload_segments();
    kprint("[ GDT ] Reloaded Segments\n");

    PIC_remap(0x20, 0x28);

    ps2_init();
    idt_init();

    irq_install();

    __asm__ volatile ("sti");
    kprint("[ GDT ] Interrupts Enabled\n");
    IRQ_clear_mask(0); // timer input
    kprint("[ IRQ ] Unmasked Line 1 (TIMER)\n");
    IRQ_clear_mask(1); // keyboard input
    kprint("[ IRQ ] Unmasked Line 1 (KEYBOARD)\n");

    // done, hang
    hcf();
}
