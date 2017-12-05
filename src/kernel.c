#include <stddef.h>
#include <stdint.h>

#include "types.h"
#include "debug.h"
#include "interrupt.h"
#include "kb.h"

// register const void *const esp asm("esp");
// register const void *const ebp asm("ebp");

void foo();

void kernel_main() {  
  // initialize interrupt table
  idt_init();
  
  // initialize keyboard
  kb_init();

  debug();
  foo();
  debug();
}

static const char *const error_messages[32];

int kernel_fault_handler(struct fault_frame *info) {
  if(info->int_no < 0 || info->int_no >= 32) {
    return 0;
  }

  if(info->int_no == 1) {
    // debug...
    dump_fault_state(info);
    return 0;
  } else if(info->int_no == 3) {
    // breakpoint
    return 0;
  }
   
  dprintf("== EXCEPTION OCCURRED ==\n");
  dprintf("Exception %d: %s (%d)\n", info->int_no, error_messages[info->int_no], info->err_code);
  dump_fault_state(info);
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
