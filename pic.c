#include "pic.h" 
void pic_init(void) {
    /* ICW1 */
    outb(PIC1_PORTA, ICW1_INIT | ICW1_ICW4);
    outb(PIC2_PORTA, ICW1_INIT | ICW1_ICW4);
    io_wait();

    /* ICW2 */
    outb(PIC1_PORTB, PIC1_OFFSET);
    outb(PIC2_PORTB, PIC2_OFFSET);
    io_wait();

    /* ICW3 */
    outb(PIC1_PORTB, 0x04); /* Map IRQ2 to PIC2 */ 
    outb(PIC2_PORTB, 0x02); /* Slave is mapped to IRQ2 */
    io_wait();

    /* ICW4 */
    outb(PIC1_PORTB, ICW4_NESTED | ICW4_MASTER);
    outb(PIC2_PORTB, ICW4_NESTED);
    io_wait();
}

void pic_ack(uint32_t interrupt) {
    if (interrupt < PIC1_OFFSET || interrupt > PIC2_OFFSET+7) 
        return;

    outb(PIC1_PORTA, PIC_EOI);
    outb(PIC2_PORTA, PIC_EOI);
}

void pic_set_mask(uint8_t pic1_mask, uint8_t pic2_mask) {
    /* since IRQs with zeroes are the ones enabled, if we pass into the
     * function the IRQs we want to enable then xor with 0xFF we get the
     * inverted selection */
    uint8_t xpic1_mask = 0xFF ^ pic1_mask;
    uint8_t xpic2_mask = 0xFF ^ pic2_mask;
    outb(PIC1_PORTB, xpic1_mask);
    outb(PIC2_PORTB, xpic2_mask);
}
    
