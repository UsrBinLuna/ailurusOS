#include <stdio.h>
#include "../../../lib/string.h"
#include "font_data.h"
#include "../framebuffer.h"

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

void kprint(char *str, uint8_t row) {
    size_t length = strlen(str);

    for (size_t i = 0; i < length; i++) {
        int ascii_code = (unsigned char)str[i];
        print_char(ascii_code, i, row);
    }
}