#include "isr.h"

#include "utils.h"

void isr_handler(registers_t regs) {
    printk(PRINTK_FB, "received interrupt");
    (void)regs;
}
