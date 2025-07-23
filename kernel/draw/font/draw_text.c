#include <stdio.h>
#include <string.h>
#include "../../../lib/string.h"
#include "font_data.h"
#include "../framebuffer.h"

#define MAX_COLS 80
#define MAX_ROWS 30

void print_char(int ascii_code, uint8_t text_col, uint8_t text_row) {
    const uint8_t* glyph = font[ascii_code];


    for (int row = 0; row < 16; row++) {
        uint8_t row_bits = glyph[row];

        int col = 0;
        for (int bit = 7; bit >= 0; bit--) {
            unsigned char bit_value = (row_bits >> bit) & 1;
            if (bit_value == 0b1) pixel((text_col * 8) + col, (text_row * 16) + row, 0xffffff);
            col++;
        }
    }
}

void clear_screen() {
    for (int y = 0; y < MAX_ROWS * 16; y++) {
        for (int x = 0; x < MAX_COLS * 8; x++) {
            pixel(x, y, 0x000000); // Black background
        }
    }
}

void scroll() {
    struct limine_framebuffer *fb = get_framebuffer();

    uint32_t *fb_ptr = (uint32_t *)fb->address;
    uint64_t pitch = fb->pitch / 4;
    uint64_t fb_width = fb->width;
    uint64_t fb_height = fb->height;

    uint64_t bytes_per_row = fb_width * sizeof(uint32_t);
    uint64_t src_offset = 16 * pitch * sizeof(uint32_t); // Start from row 16
    uint64_t dest_offset = 0;
    uint64_t bytes_to_move = (fb_height - 16) * pitch * sizeof(uint32_t);

    memmove(
        fb_ptr,
        fb_ptr + (16 * pitch),
        bytes_to_move
    );
}

void kprint(const char *str) {
    static uint8_t col = 0;
    static uint8_t row = 0;

    for (size_t i = 0; str[i] != '\0'; i++) {
        char c = str[i];

        if (c == '\n') {
            col = 0;       // Reset to start of line
            row++;         // Move to next row
            continue;      // Skip printing for newline
        }

        print_char((unsigned char)c, col, row);
        col++;

        // Handle text wrapping
        if (col >= MAX_COLS) {
            col = 0;
            row++;
        }

        // Handle screen overflow (basic clear)
        if (row >= MAX_ROWS) {
            scroll();
            row -= 1;
        }
    }
}