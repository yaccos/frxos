#include "irq.h"

#include <stddef.h>
#include <stdint.h>

#include "debug.h"

#include "io.h"

#define PIC1          0x20    /* IO base address for master PIC */
#define PIC2          0xA0    /* IO base address for slave PIC */
#define PIC1_COMMAND  PIC1
#define PIC1_DATA     (PIC1+1)
#define PIC2_COMMAND  PIC2
#define PIC2_DATA     (PIC2+1)

#define PIC_READ_IRR                0x0A    /* OCW3 irq ready next CMD read */
#define PIC_READ_ISR                0x0B    /* OCW3 irq service next CMD read */

#define ICW1_ICW4       0x01    /* ICW4 (not) needed */
#define ICW1_SINGLE     0x02    /* Single (cascade) mode */
#define ICW1_INTERVAL4  0x04    /* Call address interval 4 (8) */
#define ICW1_LEVEL      0x08    /* Level triggered (edge) mode */
#define ICW1_INIT       0x10    /* Initialization - required! */

#define ICW4_8086       0x01    /* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO       0x02    /* Auto (normal) EOI */
#define ICW4_BUF_SLAVE  0x08    /* Buffered mode/slave */
#define ICW4_BUF_MASTER 0x0C    /* Buffered mode/master */
#define ICW4_SFNM       0x10    /* Special fully nested (not) */

static void irq_remap(uint8_t port_offset1, uint8_t port_offset2);

static void (*irq_handlers[16])(struct full_interrupt_frame*) = { 0 };

void irq_common_handler(struct full_interrupt_frame *frame) {
  if(frame->no >= 0x10)
    // not an IRQ
    return;
  
  if(irq_handlers[frame->no]) {
    irq_handlers[frame->no](frame);
  } else {
    dprintf("Unhandled IRQ %d\n", frame->no);
  }

  // ackknowlegde IRQ
  if(frame->no >= 8)
    outb(PIC2_PORT, 0x20);
  outb(PIC1_PORT, 0x20);
}

void set_irq_handler(uint8_t num, void (*func)(struct full_interrupt_frame*)) {
  if(num < 0x10)
    irq_handlers[num] = func;
}

void set_irq_return(void(*func)(struct full_interrupt_frame*)) {
  extern void (*__irq_return_ptr)(struct full_interrupt_frame*);
  __irq_return_ptr = func;
}

void install_irq() {
  irq_remap(PIC1_PORT, PIC2_PORT);

  load_idt_func(PIC1_PORT + 0, _irq0);
  load_idt_func(PIC1_PORT + 1, _irq1);
  load_idt_func(PIC1_PORT + 2, _irq2);
  load_idt_func(PIC1_PORT + 3, _irq3);
  load_idt_func(PIC1_PORT + 4, _irq4);
  load_idt_func(PIC1_PORT + 5, _irq5);
  load_idt_func(PIC1_PORT + 6, _irq6);
  load_idt_func(PIC1_PORT + 7, _irq7);
  load_idt_func(PIC2_PORT + 0, _irq8);
  load_idt_func(PIC2_PORT + 1, _irq9);
  load_idt_func(PIC2_PORT + 2, _irq10);
  load_idt_func(PIC2_PORT + 3, _irq11);
  load_idt_func(PIC2_PORT + 4, _irq12);
  load_idt_func(PIC2_PORT + 5, _irq13);
  load_idt_func(PIC2_PORT + 6, _irq14);
  load_idt_func(PIC2_PORT + 7, _irq15);
}

static void irq_remap(uint8_t port_offset1, uint8_t port_offset2) {
  uint8_t a1 = inb(PIC1_DATA);
  uint8_t a2 = inb(PIC2_DATA);

  outb(PIC1_COMMAND, ICW1_INIT+ICW1_ICW4);
  io_wait();
  outb(PIC2_COMMAND, ICW1_INIT+ICW1_ICW4);
  io_wait();
  outb(PIC1_DATA, port_offset1);
  io_wait();
  outb(PIC2_DATA, port_offset2);
  io_wait();
  outb(PIC1_DATA, 4);
  io_wait();
  outb(PIC2_DATA, 2);
  io_wait();

  outb(PIC1_DATA, ICW4_8086);
  io_wait();
  outb(PIC2_DATA, ICW4_8086);
  io_wait();

  outb(PIC1_DATA, a1);
  outb(PIC2_DATA, a2);
}

static inline uint16_t __pic_get_irq_reg(int ocw3) {
  outb(PIC1_COMMAND, ocw3);
  outb(PIC2_COMMAND, ocw3);
  return (inb(PIC2_COMMAND) << 8) | inb(PIC1_COMMAND);
}

uint16_t pic_get_irr(void) {
  return __pic_get_irq_reg(PIC_READ_IRR);
}

uint16_t pic_get_isr(void) {
  return __pic_get_irq_reg(PIC_READ_ISR);
}

__always_inline
inline void irq_disable(){
	asm volatile("cli");
}

__always_inline
inline void irq_enable(){
	asm volatile("sti");
}

