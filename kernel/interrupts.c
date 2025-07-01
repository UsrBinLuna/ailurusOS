#include <stdbool.h>

unsigned long save_irqdisable(void) {
    unsigned long flags;
    asm volatile ("pushf\n\tcli\n\tpop %0" : "=r"(flags) : : "memory");
    return flags;
}

void irqrestore(unsigned long flags) {
    asm ("push %0\n\tpopf" : : "rm"(flags) : "memory","cc");
}

bool are_interrupts_enabled() {
    unsigned long flags;
    asm volatile ( "pushf\n\t"
                    "pop %0"
                    : "=g"(flags) );

    return flags & (1 << 9);
}