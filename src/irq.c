#include "irq.h"

#include <stddef.h>
#include <stdint.h>

#include "types.h"
#include "debug.h"
#include "io.h"
#include "interrupt.h"

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
 
void install_irq() {
  irq_remap(0x20, 0x28);

  // install default IRQ handler
  extern void _irq0();
  extern void _irq1();
  extern void _irq2();
  extern void _irq3();
  extern void _irq4();
  extern void _irq5();
  extern void _irq6();
  extern void _irq7();
  extern void _irq8();
  extern void _irq9();
  extern void _irq10();
  extern void _irq11();
  extern void _irq12();
  extern void _irq13();
  extern void _irq14();
  extern void _irq15();

  load_idt_entry(32, (uint32_t)&_irq0, 0x08, 0x8E);
  load_idt_entry(33, (uint32_t)&_irq1, 0x08, 0x8E);
  load_idt_entry(34, (uint32_t)&_irq2, 0x08, 0x8E);
  load_idt_entry(35, (uint32_t)&_irq3, 0x08, 0x8E);
  load_idt_entry(36, (uint32_t)&_irq4, 0x08, 0x8E);
  load_idt_entry(37, (uint32_t)&_irq5, 0x08, 0x8E);
  load_idt_entry(38, (uint32_t)&_irq6, 0x08, 0x8E);
  load_idt_entry(39, (uint32_t)&_irq7, 0x08, 0x8E);
  load_idt_entry(40, (uint32_t)&_irq8, 0x08, 0x8E);
  load_idt_entry(41, (uint32_t)&_irq9, 0x08, 0x8E);
  load_idt_entry(42, (uint32_t)&_irq10, 0x08, 0x8E);
  load_idt_entry(43, (uint32_t)&_irq11, 0x08, 0x8E);
  load_idt_entry(44, (uint32_t)&_irq12, 0x08, 0x8E);
  load_idt_entry(45, (uint32_t)&_irq13, 0x08, 0x8E);
  load_idt_entry(46, (uint32_t)&_irq14, 0x08, 0x8E);
  load_idt_entry(47, (uint32_t)&_irq15, 0x08, 0x8E);
}

/*
   arguments:
     offset1 - vector offset for master PIC
       vectors on the master become offset1..offset1+7
     offset2 - same for slave PIC: offset2..offset2+7
   */
void irq_remap(uint8_t offset1, uint8_t offset2) {
  uint8_t a1 = inb(PIC1_DATA);                        // save masks
  uint8_t a2 = inb(PIC2_DATA);

  outb(PIC1_COMMAND, ICW1_INIT+ICW1_ICW4);  // starts the initialization sequence (in cascade mode)
  io_wait();
  outb(PIC2_COMMAND, ICW1_INIT+ICW1_ICW4);
  io_wait();
  outb(PIC1_DATA, offset1);                 // ICW2: Master PIC vector offset
  io_wait();
  outb(PIC2_DATA, offset2);                 // ICW2: Slave PIC vector offset
  io_wait();
  outb(PIC1_DATA, 4);                       // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
  io_wait();
  outb(PIC2_DATA, 2);                       // ICW3: tell Slave PIC its cascade identity (0000 0010)
  io_wait();

  outb(PIC1_DATA, ICW4_8086);
  io_wait();
  outb(PIC2_DATA, ICW4_8086);
  io_wait();

  outb(PIC1_DATA, a1);   // restore saved masks.
  outb(PIC2_DATA, a2);
}
 
/* Helper func */
static inline uint16_t __pic_get_irq_reg(int ocw3) {
    /* OCW3 to PIC CMD to get the register values.  PIC2 is chained, and
     * represents IRQs 8-15.  PIC1 is IRQs 0-7, with 2 being the chain */
    outb(PIC1_COMMAND, ocw3);
    outb(PIC2_COMMAND, ocw3);
    return (inb(PIC2_COMMAND) << 8) | inb(PIC1_COMMAND);
}
 
/* Returns the combined value of the cascaded PICs irq request register */
uint16_t pic_get_irr(void) {
    return __pic_get_irq_reg(PIC_READ_IRR);
}
 
/* Returns the combined value of the cascaded PICs in-service register */
uint16_t pic_get_isr(void) {
    return __pic_get_irq_reg(PIC_READ_ISR);
}


void irq_handler(struct full_interrupt_frame *frame) {
  dprintf(":: IRQ%u\n", frame->num);

  if(frame->num >= 0x08) {
    outb(PIC2, 0x20);
  }

  outb(PIC1, 0x20);
}
