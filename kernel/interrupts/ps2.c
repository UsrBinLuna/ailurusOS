#define PS2_COMMAND 0x64
#define PS2_DATA    0x60

#include <stdint.h>
#include "../io.h"
#include "../draw/font/draw_text.h"

void ps2_init() {
    // Disable both ports
    outb(PS2_COMMAND, 0xAD);
    outb(PS2_COMMAND, 0xA7);
    io_wait();
    
    // Clear output buffer
    while (inb(0x64) & 1) 
        inb(0x60);
    
    // Set configuration byte
    outb(PS2_COMMAND, 0x20);
    uint8_t config = inb(PS2_DATA);
    config |= 0x01;  // Enable keyboard interrupt
    config &= ~0x30; // Disable mouse and translation
    outb(PS2_COMMAND, 0x60);
    outb(PS2_DATA, config);
    
    // Test controller
    outb(PS2_COMMAND, 0xAA);
    if(inb(PS2_DATA) != 0x55) {
        kprint("[ PS2 ] Controller test failed!");
        return;
    }
    
    // Enable keyboard port
    outb(PS2_COMMAND, 0xAE);
    kprint("[ PS2 ] Keyboard enabled");
}