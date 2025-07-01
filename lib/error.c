#include "syscalls.h"
#include "../kernel/draw/font/draw_text.h"

void kerror(const char *str) {
    kprint(str);
    hcf();
}