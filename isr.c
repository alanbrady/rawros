#include "isr.h"

#include "utils.h"
#include "pic.h"

void isr_handler(registers_t regs) {
    printk(PRINTK_FB, "interrupt:%h %h\n", regs.int_no, regs.err_code);

    pic_ack(regs.err_code);
}
