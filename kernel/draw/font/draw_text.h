#ifndef DRAW_TEXT_H
#define DRAW_TEXT_H

#include <stdint.h>

void print_char(int ascii_code, uint8_t text_col, uint8_t text_row);
void kprint(const char *str);

#endif // DRAW_TEXT_H