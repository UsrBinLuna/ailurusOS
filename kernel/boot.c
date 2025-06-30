#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "boot/limine.h"
#include "memory.h"
#include "draw/framebuffer.h"
#include "draw/font/draw_text.h"

// limine boot stuff
__attribute__((used, section(".limine_requests")))
static volatile LIMINE_BASE_REVISION(3);

__attribute__((used, section(".limine_requests_start")))
static volatile LIMINE_REQUESTS_START_MARKER;

__attribute__((used, section(".limine_requests_end")))
static volatile LIMINE_REQUESTS_END_MARKER;

// halt and implode
static void hcf(void) {
    for (;;) {
        asm ("hlt");
    }
}

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

    kprint("Hello World!", 1);
    kprint("i hate c", 5);

    kprint("i fucked your mom last night", 7);


    // done, hang
    hcf();
}
