#include "framebuffer.h"

__attribute__((used, section(".limine_requests")))
volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};

struct limine_framebuffer *get_framebuffer(void) {
    if (framebuffer_request.response == NULL ||
        framebuffer_request.response->framebuffer_count < 1) {
        return NULL;
    }
    return framebuffer_request.response->framebuffers[0];
}

void pixel(uint32_t x, uint32_t y, uint32_t color) {
    struct limine_framebuffer *fb = get_framebuffer();
    if (fb == NULL) return;

    if (x >= fb->width || y >= fb->height) return;

    uint32_t *fb_ptr = (uint32_t *)fb->address;
    uint64_t pitch = fb->pitch / 4;
    fb_ptr[y * pitch + x] = color;
}
