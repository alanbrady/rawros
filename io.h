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


/**
 * io_wait:
 * Perform an output to port 0x80 which is used for checkpoints in POST.  We
 * probably shouldn't be doing this in this way but Linux does it so oh well.
 *
 * The only purpose for the function is to wait for an I/O cycle to complete
 * and conducting an arbitrary out req. achieves such.
 */
extern void io_wait(void);

#endif

