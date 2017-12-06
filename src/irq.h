#ifndef IRQ_H_
#define IRQ_H_

#include <stddef.h>
#include <stdint.h>

void install_irq();

void irq_remap(uint8_t offset1, uint8_t offset2);
uint16_t pic_get_irr(void);
uint16_t pic_get_isr(void);

#endif // IRQ_H_
