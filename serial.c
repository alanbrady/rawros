#include "serial.h"
#include "io.h"

void serial_write(char a, const unsigned short com) {
    while(serial_is_transmit_empty(com) == 0);
    outb(com, a);
}

void serial_write_data(const char* str, const unsigned int len, const unsigned short com) {
    unsigned int i = 0;
    for(; i < len; ++i, ++str) {
        serial_write(*str, com);
    }
}

void serial_init(unsigned short com) {
    serial_set_baud_rate(com, 115200);
    serial_configure_buffers(com);
    serial_configure_line(com, SERIAL_LCR_WORDLEN_8, SERIAL_LCR_NO_PARITY,
            SERIAL_LCR_ONE_STOPBIT);
    serial_configure_modem(com);
}

void serial_set_baud_rate(unsigned short com, unsigned int frequency) {
    // old, probably garbage, left for reference until tested
    /*outb(SERIAL_LINE_CONTROL_REG(com), SERIAL_LINE_ENABLE_DLAB);*/
    /*outb(SERIAL_DATA_PORT(com), divisor & 0x00FF);*/
    /*outb(SERIAL_DATA_PORT(com), (divisor >> 8) & 0x00FF);*/

    // dlab changes the way base and base+1 behave
    // with it enabled +0 and +1 are the divisor registers
    serial_enable_dlab(com);

    // calculate divisor based on the requested frequency
    // frequency must be 0 > f >= 115200
    // greater than 115200 caps the frequency and 0 makes default to
    // 115200
    if (frequency == 0 || frequency > 115200) frequency = 115200;
    unsigned int divisor = 115200/frequency;

    outb(SERIAL_DIV_LATCH_LOW(com), divisor & 0x00FF);
    outb(SERIAL_DIV_LATCH_HIGH(com), (divisor >> 8) & 0x00FF);

    // go ahead and disable dlab since it's only used when setting the
    // divisor, this way dlab is isolated to this function
    serial_disable_dlab(com);
}

int serial_configure_line(unsigned short com, unsigned short wordLength,
        unsigned short parity, unsigned short stopBits) {
    // check for invalid wordLength
    if (wordLength != SERIAL_LCR_WORDLEN_5 &&
            wordLength != SERIAL_LCR_WORDLEN_6 &&
            wordLength != SERIAL_LCR_WORDLEN_7 &&
            wordLength != SERIAL_LCR_WORDLEN_8) {
        return 0;
    }

    // check for ivnalid parity
    if (parity != SERIAL_LCR_NO_PARITY &&
            parity != SERIAL_LCR_ODD_PARITY &&
            parity != SERIAL_LCR_EVEN_PARITY &&
            parity != SERIAL_LCR_MARK &&
            parity != SERIAL_LCR_SPACE) {
        return 0;
    }

    // check for invalid stop bit
    if (stopBits != SERIAL_LCR_ONE_STOPBIT &&
            stopBits != SERIAL_LCR_TWO_STOPBIT) {
        return 0;
    }

    // good to go, setup our LCR with the given options
    outb(SERIAL_LINE_CONTROL_REG(com),
            wordLength | parity | stopBits);
    return -1;
}

void serial_configure_modem(unsigned short com) {
    outb(SERIAL_MODEM_CONTROL_REG(com), 0x0B);
}

void serial_configure_buffers(unsigned short com) {
    outb(SERIAL_FIFO_CONTROL_REG(com), 0xC7);
}

int serial_is_transmit_empty(unsigned short com) {
    return (inb(SERIAL_LINE_STATUS_REG(com)) &
            SERIAL_LSR_EMPTY_TX_HOLDING_REG);
}

void serial_enable_dlab(unsigned short com) {
    short currLineReg = inb(SERIAL_LINE_CONTROL_REG(com));
    outb(SERIAL_LINE_CONTROL_REG(com), currLineReg | 0x80);
}

void serial_disable_dlab(unsigned short com) {
    short currLineReg = inb(SERIAL_LINE_CONTROL_REG(com));
    outb(SERIAL_LINE_CONTROL_REG(com), currLineReg & 0x3F);
}

void serial_enable_rda_interrupt(unsigned short com) {
    outb(SERIAL_INTERRUPT_ENABLE_REG(com), 0x01);
}

void serial_disable_rda_interrupt(unsigned short com) {
    outb(SERIAL_INTERRUPT_ENABLE_REG(com), 0x00);
}

int serial_is_interrupt_pending(unsigned short com) {
    return (inb(SERIAL_INTERRUPT_ID_REG(com)) & 0x01) == 0x01;
}

int serial_identify_interrupt(unsigned short com) {
    return inb(SERIAL_INTERRUPT_ID_REG(com)) & 0x0E;
}
