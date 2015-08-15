#ifndef PIC_H
#define PIC_H

#include "io.h"
#include "types.h"

#define PIC1_PORTA          0x20
#define PIC1_PORTB          0x21
#define PIC2_PORTA          0xA0
#define PIC2_PORTB          0xA1

#define ICW1_INIT           0x10
#define ICW1_ICW4           0x01  /* 0:disabled 1: enable */
#define ICW1_MS             0x02  /* 0:m/s  1: master only */
#define ICW1_TRIGGER        0x04  /* 0:edge 1:level */
/* sane master: 0x11 */
/* sane slave:  0x11 */

#define ICW4_NESTED         0x01
#define ICW4_BUFFERED       0x02
#define ICW4_MASTER         0x04
#define ICW4_AUTO_EOI       0x08
#define ICW4_8086_MODE      0x10
/* sane master: 0x05 */
/* sane slave:  0x01 */

#define PIC1_OFFSET         0x20
#define PIC2_OFFSET         0x28

#define PIC_EOI             0x20

/* pic mask flags */
#define PIC1_TIMER_IRQ      0x01
#define PIC1_KBD_IRQ        0x02
#define PIC1_COM2_IRQ       0x08
#define PIC1_COM1_IRQ       0x10
#define PIC1_LPT2_IRQ       0x20
#define PIC2_FLOPPY_IRQ     0x40
#define PIC2_CMOSCLK_IRQ    0x01
#define PIC2_PS2MOUSE_IRQ   0x10
#define PIC2_PATA_IRQ       0x40
#define PIC2_SATA_IRQ       0x80
#define PIC_ALL_IRQ         0xFF
#define PIC_NO_IRQ          0x00

void pic_init(void);

void pic_ack(uint32_t interrupt);

void pic_set_mask(uint8_t pic1_mask, uint8_t pic2_mask);

#endif
