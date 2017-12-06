#include <stddef.h>
#include <stdint.h>

#include "types.h"
#include "debug.h"
#include "io.h"
#include "interrupt.h"
#include "irq.h"
#include "timer.h"
#include "kb.h"

__attribute__((noreturn)) extern void kernel_halt();
__attribute__((noreturn)) extern void kernel_reboot();

static inline void install_gdt() { /* TODO: implement in gdt.c */ }

void kernel_main() {
  install_gdt();
  install_idt();
  install_irq();
  install_timer();
  install_keyboard();

  // enable interrupts
  asm volatile("sti");

  debug();

  // event loop (wait for interrupts)
  for(;;)
    asm("hlt");
}

static const char *const error_messages[32];

int kernel_fault_handler(struct full_interrupt_frame *info) {
  if(info->num < 0 || info->num >= 32) {
    return 0;
  }
  
  dprintf("== EXCEPTION OCCURRED ==\n");
  dprintf("Exception %d: %s (%d)\n", info->num, error_messages[info->num], info->err_code);
  debug_dump_state(info);
  return 1;
}

static const char *const error_messages[32] = {
  "Division By Zero",
  "Debug",
  "Non Maskable Interrupt",
  "Breakpoint",
  "Into Detected Overflow",
  "Out of Bounds",
  "Invalid Opcode",
  "No Coprocessor",
  "Double Fault",
  "Coprocessor Segment Overrun",
  "Bad TSS",
  "Segment Not Present",
  "Stack Fault",
  "General Protection Fault",
  "Page Fault",
  "Unknown Interrupt",
  "Coprocessor Fault",
  "Alignment Check",
  "Machine Check",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
};
