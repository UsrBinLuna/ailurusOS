#include "pic.h"

void timer_handler() {
    PIC_sendEOI(0);
}