#include <stdint.h>
#include "../io.h"
#include "../pic.h"

void interrupt_handler(void) {
    PIC_sendEOI(0x20);
}