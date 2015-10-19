#include "isr.h"

#include "utils.h"
#include "pic.h"
#include "keyboard.h"

void isr_handler(registers_t regs) {
    if (regs.err_code == 0x21) {
        printk(PRINTK_FB, "keyboard interrupt: %h\n", read_keyboard());
    } else {
        printk(PRINTK_FB, "interrupt:%h %h\n", regs.int_no, regs.err_code);
    }

    pic_ack(regs.err_code);
}
