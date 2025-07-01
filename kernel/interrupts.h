#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include <stdbool.h>

static inline unsigned long save_irqdisable(void);
static inline void irqrestore(unsigned long flags);
static inline bool are_interrupts_enabled();

#endif // INTERRUPTS_H