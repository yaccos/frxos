#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include <stddef.h>
#include <stdint.h>

#define IDT_SIZE 256

struct idt_entry {
  uint16_t offset_lo;
  uint16_t selector;
  uint8_t  zero;
  uint8_t  flags;
  uint16_t offset_hi;
} __attribute__((packed));

struct idt_pointer {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed));

extern struct idt_entry idt[IDT_SIZE];
extern struct idt_pointer idt_ptr;

void load_idt_entry(uint8_t num, uint32_t offset, uint16_t selector, uint8_t flags);
void idt_init();

#endif // INTERRUPT_H_
