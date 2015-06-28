#ifndef OUTB
#define OUTB

/**
 * outb:
 * Sends the given data to the given I/O port
 *
 * @param port The port to send the data
 * @param data The data to be sent
 */
extern void outb(const unsigned short port, const unsigned char data);

/**
 * inb:
 * Recieves a byte of data from the given port
 *
 * @param port The port to receive data from
 */
extern unsigned char inb(const unsigned short port);

#endif

