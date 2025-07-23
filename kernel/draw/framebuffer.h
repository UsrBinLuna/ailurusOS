#pragma once
#include "../boot/limine.h"
#include <stdint.h>
#include <stddef.h>

extern volatile struct limine_framebuffer_request framebuffer_request;
extern uint32_t *fb_ptr;

struct limine_framebuffer *get_framebuffer(void);
void pixel(uint32_t x, uint32_t y, uint32_t color);
uint32_t get_pixel(uint32_t x, uint32_t y);