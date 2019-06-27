#ifndef IRQ_H_
#define IRQ_H_

#include <stddef.h>
#include <stdint.h>

#include "idt.h"

#ifdef __cplusplus
extern "C" {
#endif

#define PIC1_PORT 0x20
#define PIC2_PORT 0x28

void install_irq();
void irq_disable();
void irq_enable();
void set_irq_handler(uint8_t num, void (*func)(struct full_interrupt_frame*));
void set_irq_return(void(*func)(struct full_interrupt_frame*));

uint16_t pic_get_irr();
uint16_t pic_get_isr();

#ifdef __cplusplus
}
#endif

#endif // IRQ_H_
