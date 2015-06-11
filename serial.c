#include "serial.h"
#include "io.h"

void serial_write(char a) {
    while(serial_is_transmit_empty(SERIAL_COM_BASE) == 0);

    outb(SERIAL_COM_BASE, a);
}

void serial_write_data(const char* str, const unsigned int len) {
    unsigned int i = 0;
    for(; i < len; ++i, ++str) {
        serial_write(*str);
    }
}

void serial_init(unsigned short com) {
    serial_configure_baud_rate(com, 2);
    serial_configure_buffers(com);
    serial_configure_line(com);
    serial_configure_modem(com);
}

void serial_configure_baud_rate(unsigned short com, unsigned short divisor) {
    outb(SERIAL_LINE_COMMAND_PORT(com), SERIAL_LINE_ENABLE_DLAB);
    outb(SERIAL_DATA_PORT(com), divisor & 0x00FF);
    outb(SERIAL_DATA_PORT(com), (divisor >> 8) & 0x00FF);
}

void serial_configure_line(unsigned short com) {
    outb(SERIAL_LINE_COMMAND_PORT(com), 0x03);
}

void serial_configure_modem(unsigned short com) {
    outb(SERIAL_MODEM_COMMAND_PORT(com), 0x03);
}

void serial_configure_buffers(unsigned short com) {
    outb(SERIAL_FIFO_COMMAND_PORT(com), 0xC7);
}

int serial_is_transmit_empty(unsigned short com) {
    return (inb(SERIAL_STATUS_PORT(com)) & 0x20);
}
