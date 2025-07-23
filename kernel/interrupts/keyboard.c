#include <stdint.h>
#include "../io.h"
#include "../pic.h"
#include "../draw/font/draw_text.h"
#include "../../lib/convert.h"
#include "../draw/framebuffer.h"

void keyboard_handler() {
    uint8_t scancode = inb(0x60);

    // ignore break codes
    if (scancode & 0x80) {
        PIC_sendEOI(1);
    } else {
        char buf[4];
        u8_to_str(scancode, buf);
        kprint(buf);
        kprint("\n");
        
        PIC_sendEOI(1);
    }
}
