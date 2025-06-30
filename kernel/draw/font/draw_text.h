#ifndef DRAW_TEXT_H
#define DRAW_TEXT_H

#include <stdint.h>

void print_char(int ascii_code, uint8_t text_col, uint8_t text_row);
void kprint(char *str, uint8_t row);

#endif // DRAW_TEXT_H