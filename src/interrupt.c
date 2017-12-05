#include "interrupt.h"

#include <stddef.h>
#include <stdint.h>

#include "debug.h"
#include "io.h"

struct idt_entry idt[IDT_SIZE] = { 0 };
struct idt_pointer idt_ptr;

void load_idt_entry(uint8_t num, uint32_t offset, uint16_t selector, uint8_t flags) {
  idt[num].offset_lo = offset & 0xFFFF;
  idt[num].offset_hi = (offset >> 16) & 0xFFFF;
  idt[num].selector = selector;
  idt[num].flags = flags;
  idt[num].zero = 0;
}

void idt_init() {
  idt_ptr.limit = (sizeof(struct idt_entry) * IDT_SIZE) - 1;
  idt_ptr.base  = (uint32_t)&idt;
  asm("lidt %0" :: "m"(idt_ptr));

  // install default exception handlers
  extern void _isr0();
  extern void _isr1();
  extern void _isr2();
  extern void _isr3();
  extern void _isr4();
  extern void _isr5();
  extern void _isr6();
  extern void _isr7();
  extern void _isr8();
  extern void _isr9();
  extern void _isr10();
  extern void _isr11();
  extern void _isr12();
  extern void _isr13();
  extern void _isr14();
  extern void _isr15();
  extern void _isr16();
  extern void _isr17();
  extern void _isr18();
  extern void _isr19();
  extern void _isr20();
  extern void _isr21();
  extern void _isr22();
  extern void _isr23();
  extern void _isr24();
  extern void _isr25();
  extern void _isr26();
  extern void _isr27();
  extern void _isr28();
  extern void _isr29();
  extern void _isr30();
  extern void _isr31();

  load_idt_entry(0, (uint32_t)&_isr0, 0x08, 0x8E);
  load_idt_entry(1, (uint32_t)&_isr1, 0x08, 0x8E);
  load_idt_entry(2, (uint32_t)&_isr2, 0x08, 0x8E);
  load_idt_entry(3, (uint32_t)&_isr3, 0x08, 0x8E);
  load_idt_entry(4, (uint32_t)&_isr4, 0x08, 0x8E);
  load_idt_entry(5, (uint32_t)&_isr5, 0x08, 0x8E);
  load_idt_entry(6, (uint32_t)&_isr6, 0x08, 0x8E);
  load_idt_entry(7, (uint32_t)&_isr7, 0x08, 0x8E);
  load_idt_entry(8, (uint32_t)&_isr8, 0x08, 0x8E);
  load_idt_entry(9, (uint32_t)&_isr9, 0x08, 0x8E);
  load_idt_entry(10, (uint32_t)&_isr10, 0x08, 0x8E);
  load_idt_entry(11, (uint32_t)&_isr11, 0x08, 0x8E);
  load_idt_entry(12, (uint32_t)&_isr12, 0x08, 0x8E);
  load_idt_entry(13, (uint32_t)&_isr13, 0x08, 0x8E);
  load_idt_entry(14, (uint32_t)&_isr14, 0x08, 0x8E);
  load_idt_entry(15, (uint32_t)&_isr15, 0x08, 0x8E);
  load_idt_entry(16, (uint32_t)&_isr16, 0x08, 0x8E);
  load_idt_entry(17, (uint32_t)&_isr17, 0x08, 0x8E);
  load_idt_entry(18, (uint32_t)&_isr18, 0x08, 0x8E);
  load_idt_entry(19, (uint32_t)&_isr19, 0x08, 0x8E);
  load_idt_entry(20, (uint32_t)&_isr20, 0x08, 0x8E);
  load_idt_entry(21, (uint32_t)&_isr21, 0x08, 0x8E);
  load_idt_entry(22, (uint32_t)&_isr22, 0x08, 0x8E);
  load_idt_entry(23, (uint32_t)&_isr23, 0x08, 0x8E);
  load_idt_entry(24, (uint32_t)&_isr24, 0x08, 0x8E);
  load_idt_entry(25, (uint32_t)&_isr25, 0x08, 0x8E);
  load_idt_entry(26, (uint32_t)&_isr26, 0x08, 0x8E);
  load_idt_entry(27, (uint32_t)&_isr27, 0x08, 0x8E);
  load_idt_entry(28, (uint32_t)&_isr28, 0x08, 0x8E);
  load_idt_entry(29, (uint32_t)&_isr29, 0x08, 0x8E);
  load_idt_entry(30, (uint32_t)&_isr30, 0x08, 0x8E);
  load_idt_entry(31, (uint32_t)&_isr31, 0x08, 0x8E);
}
