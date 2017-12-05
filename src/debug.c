#include "debug.h"

#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "mini-printf.h"
#include "serial.h"

#define DEBUG_PORT COM1

#define DEBUG_BUFFER_SIZE 4096
static char debug_buffer[DEBUG_BUFFER_SIZE] = { 0 };

void dprintf(const char *format, ...) {
  va_list args;
  va_start(args, format);
  int len = mini_vsnprintf(debug_buffer, DEBUG_BUFFER_SIZE, format, args);
  if(len > 0)
    serial_write(DEBUG_PORT, debug_buffer, len);
  va_end(args);
}

void dump_fault_state(struct fault_frame *frame) {
  // print current registers
  dprintf("Registers:\n");
  dprintf("              EAX = 0x%08x,   ECX = 0x%08x\n", frame->regs.eax, frame->regs.ecx);
  dprintf("              EDX = 0x%08x,   ECX = 0x%08x\n", frame->regs.edx, frame->regs.ebx);
  dprintf("              ESP = 0x%08x,   EBP = 0x%08x\n", frame->regs.esp, frame->regs.ebp);
  dprintf("              ESI = 0x%08x,   EDI = 0x%08x\n", frame->regs.esi, frame->regs.edi);
  dprintf("           EFLAGS = 0x%08x,    CS =     0x%04x\n", frame->inf.eflags, frame->inf.cs);

  // dump stack
  extern const void _stack_top, _stack_bottom;
  dprintf("Stack:");
  {
    const void *ebp = (const void*)frame->regs.ebp;
    const void *esp = (const void*)frame->regs.esp;
    const void *ptr = esp - (uint32_t)esp % 8;
    while(ptr < &_stack_top) {
      if((uint32_t)ptr % 8 == 0) {
        dprintf("\n  0x%08x:      ", (uint32_t)ptr);
      } else if((uint32_t)ptr % 4 == 0) {
        dprintf(" ");
      }

      if(ptr == ebp) {
        esp = ebp;
        ebp = ((void**)ebp)[0];
      }
      
      dprintf("%c%02x", ptr == esp ? '<' : ' ', *(uint8_t*)ptr);

      ptr++;
    }

    dprintf("\n                       {  end of stack  }\n");
  }

  // dump stack trace
  dprintf("Stack trace:\n");
  {
    const void *eip = (const void*)frame->inf.eip;
    const void *esp = (const void*)frame->regs.esp;
    const void *ebp = (const void*)frame->regs.ebp;

    do {
      dprintf("  function at <0x%08x>,  stack [ 0x%08x - 0x%08x ]\n", (uint32_t)eip, (uint32_t)esp, (uint32_t)ebp);

      esp = ebp;
      ebp = ((void**)esp)[0];
      eip = ((void**)esp)[1];
    } while(ebp > &_stack_bottom && ebp <= &_stack_top);

    dprintf("                    {  end of stack trace  }\n");
  }

  dprintf("\n");
}

void foo() { debug(); }
