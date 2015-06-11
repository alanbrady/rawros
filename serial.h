#ifndef SERIAL_H
#define SERIAL_H

#define SERIAL_COM_BASE                     0x3F8

#define SERIAL_DATA_PORT(base)              (base)
#define SERIAL_FIFO_COMMAND_PORT(base)      (base+2)
#define SERIAL_LINE_COMMAND_PORT(base)      (base+3)
#define SERIAL_MODEM_COMMAND_PORT(base)     (base+4) 
#define SERIAL_STATUS_PORT(base)            (base+5) 

#define SERIAL_LINE_ENABLE_DLAB             0x80

void serial_write(char a);

void serial_write_data(const char* str, const unsigned int len);

void serial_init(unsigned short com);

void serial_configure_baud_rate(unsigned short com, unsigned short divisor);

void serial_configure_line(unsigned short com);

void serial_configure_modem(unsigned short com);

void serial_configure_buffers(unsigned short com);

int serial_is_transmit_empty(unsigned short com);

#endif
