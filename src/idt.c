#include "idt.h"

#include <stddef.h>
#include <stdint.h>

#include "attr.h"
#include "debug.h"

struct idt_entry {
  uint16_t offset_lo;
  uint16_t selector;
  uint8_t  zero;
  uint8_t  flags;
  uint16_t offset_hi;
} __packed;

struct idt_pointer {
  uint16_t limit;
  struct idt_entry *base;
} __packed;

static struct idt_entry idt[IDT_SIZE] = { 0 };
static struct idt_pointer idt_ptr;

extern const char *const exception_messages[32];

void install_idt() {
  idt_ptr.limit = (sizeof(struct idt_entry) * IDT_SIZE) - 1;
  idt_ptr.base = idt;
  asm volatile("lidt %0" :: "m"(idt_ptr));

  load_idt_func(0, _isr0);
  load_idt_func(1, _isr1);
  load_idt_func(2, _isr2);
  load_idt_func(3, _isr3);
  load_idt_func(4, _isr4);
  load_idt_func(5, _isr5);
  load_idt_func(6, _isr6);
  load_idt_func(7, _isr7);
  load_idt_func(8, _isr8);
  load_idt_func(9, _isr9);
  load_idt_func(10, _isr10);
  load_idt_func(11, _isr11);
  load_idt_func(12, _isr12);
  load_idt_func(13, _isr13);
  load_idt_func(14, _isr14);
  load_idt_func(15, _isr15);
  load_idt_func(16, _isr16);
  load_idt_func(17, _isr17);
  load_idt_func(18, _isr18);
  load_idt_func(19, _isr19);
  load_idt_func(20, _isr20);
  load_idt_func(21, _isr21);
  load_idt_func(22, _isr22);
  load_idt_func(23, _isr23);
  load_idt_func(24, _isr24);
  load_idt_func(25, _isr25);
  load_idt_func(26, _isr26);
  load_idt_func(27, _isr27);
  load_idt_func(28, _isr28);
  load_idt_func(29, _isr29);
  load_idt_func(30, _isr30);
  load_idt_func(31, _isr31);

  // toggle debug screen
  load_idt_func(126, _isr126);
}

void load_idt_entry(uint8_t num, void(*func)(), uint16_t selector, uint8_t flags) {
  uint32_t offset = (uint32_t)func;

  idt[num].offset_lo = offset & 0xFFFF;
  idt[num].offset_hi = (offset >> 16) & 0xFFFF;
  idt[num].selector = selector;
  idt[num].flags = flags;
  idt[num].zero = 0;
}

__cold
int fault_handler(struct full_interrupt_frame *frame) {
  if(frame->no < 32 && exception_messages[frame->no]) {
    dprintf("Exception %d: %s (%d)\n", frame->no, exception_messages[frame->no], frame->err_code);
  } else {
    dprintf("Exception %d (%d)\n", frame->no, frame->err_code);
  }

  return 0;
}

const char *const exception_messages[32] = {
  0,
};
