#ifndef SYSTEM_H
#define SYSTEM_H

#include "types.h"

/* flag register flags */
#define CARRY_FLAG      0x00000001  /* bit 0  */
#define PARITY_FLAG     0x00000004  /* bit 2  */
#define ADJUST_FLAG     0x00000010  /* bit 4  */
#define ZERO_FLAG       0x00000040  /* bit 6  */
#define SIGN_FLAG       0x00000080  /* bit 7  */
#define TRAP_FLAG       0x00000100  /* bit 8  */
#define INTERRUPT_FLAG  0x00000200  /* bit 9  */
#define DIRECTION_FLAG  0X00000400  /* bit 10 */
#define OVERFLOW_FLAG   0x00000800  /* bit 11 */

extern void gdt_flush(intptr_t p);

extern void idt_flush(intptr_t p);

#endif 
