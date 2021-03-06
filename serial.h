#ifndef SERIAL_H
#define SERIAL_H

// Com port address, BIOS may have different addresses for COM2+
#define SERIAL_COM1                     0x3F8
#define SERIAL_COM2                     0x2F8
#define SERIAL_COM3                     0x3E8
#define SERIAL_COM4                     0x2E8

#define SERIAL_DATA_TXRX(base)              (base)      // with DLAB off
#define SERIAL_INTERRUPT_ENABLE_REG(base)   (base+1)

#define SERIAL_DIV_LATCH_LOW(base)          (base)      // with DLAB on
#define SERIAL_DIV_LATCH_HIGH(base)         (base+1)

#define SERIAL_FIFO_CONTROL_REG(base)       (base+2)    // base+2 is different 
#define SERIAL_INTERRUPT_ID_REG(base)       (base+2)    // depending on if r/w

#define SERIAL_LINE_CONTROL_REG(base)       (base+3)
#define SERIAL_MODEM_CONTROL_REG(base)      (base+4)
#define SERIAL_LINE_STATUS_REG(base)        (base+5)

// Line Control Register Options
#define SERIAL_LCR_WORDLEN_5                0x00
#define SERIAL_LCR_WORDLEN_6                0x01
#define SERIAL_LCR_WORDLEN_7                0x02
#define SERIAL_LCR_WORDLEN_8                0x03

#define SERIAL_LCR_ONE_STOPBIT              0X00
#define SERIAL_LCR_TWO_STOPBIT              0X04

#define SERIAL_LCR_NO_PARITY                0x00
#define SERIAL_LCR_ODD_PARITY               0x08
#define SERIAL_LCR_EVEN_PARITY              0x18
#define SERIAL_LCR_MARK                     0x28
#define SERIAL_LCR_SPACE                    0x38

#define SERIAL_IIR_MODEM_STATUS             0x00
#define SERIAL_IIR_TX_HOLDING_REG_EMPTY     0x02
#define SERIAL_IIR_RX_DATA_AVAILABLE        0x04
#define SERIAL_IIR_RX_LINE_STATUS           0x06
#define SERIAL_IIR TIMEOUT_PENDING          0x0C

#define SERIAL_LSR_DATA_RDY                 0x01
#define SERIAL_LSR_OVERRUN_ERR              0x02
#define SERIAL_LSR_PARITY_ERR               0x04
#define SERIAL_LSR_FRAMING_ERR              0x08
#define SERIAL_LSR_BREAK_INT                0x10
#define SERIAL_LSR_EMPTY_TX_HOLDING_REG     0x20
#define SERIAL_LSR_EMPTY_RX_HOLDING_REG     0x40
#define SERIAL_LSR_ERR_RX_FIFO              0x80

//#define SERIAL_LINE_ENABLE_DLAB             0x80

void serial_write_char(unsigned char a, const unsigned short com);
void serial_write_int(unsigned int i, const unsigned short com);
void serial_write_data(const char* str, const unsigned int len, 
        const unsigned short com);
void serial_init(unsigned short com);

/**
  * serial_set_baud_rate
  * com - com port to use
  * frequency - serial connection frequency, 0 > f >= 115200
  **/
void serial_set_baud_rate(unsigned short com, unsigned int frequency);
int serial_configure_line(unsigned short com, unsigned short wordLength,
        unsigned short parity, unsigned short stopBits);
void serial_configure_modem(unsigned short com);
void serial_configure_buffers(unsigned short com);

void serial_enable_dlab(unsigned short com);
void serial_disable_dlab(unsigned short com);

void serial_enable_rda_interrupt(unsigned short com);
void serial_disable_rda_interrupt(unsigned short com);

int serial_is_interrupt_pending(unsigned short com);
int serial_identify_interrupt(unsigned short com);

int serial_is_transmit_empty(unsigned short com);

#endif
