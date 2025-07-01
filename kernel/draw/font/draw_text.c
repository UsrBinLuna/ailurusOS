#include <stdio.h>
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

void kprint(const char *str) {
    uint8_t col = 0;
    static uint8_t current_row = 0;

    for (size_t i = 0; str[i] != '\0'; i++) {
        char c = str[i];

        if (c == '\n') {
            col = 0;
            current_row++;
        } else {
            print_char((unsigned char)c, col, current_row);
            col++;

            if (col >= MAX_COLS) {
                col = 0;
                current_row++;
            }
        }

        if (current_row >= MAX_ROWS) {
            // TODO: scrolling
            break;
        }
    }

    current_row++;
}
