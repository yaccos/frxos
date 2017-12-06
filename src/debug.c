#include "debug.h"

#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "mini-printf.h"
#include "serial.h"
#include "irq.h"

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

void debug_dump_state(struct full_interrupt_frame *frame) {
  // print current registers
  dprintf("Registers:\n");
  dprintf("             EAX = 0x%08x      ECX = 0x%08x\n", frame->eax, frame->ecx);
  dprintf("             EDX = 0x%08x      ECX = 0x%08x\n", frame->edx, frame->ebx);
  dprintf("             ESP = 0x%08x      EBP = 0x%08x\n", frame->esp, frame->ebp);
  dprintf("             ESI = 0x%08x      EDI = 0x%08x\n", frame->esi, frame->edi);
  dprintf("              SS =     0x%04x       CS =     0x%04x\n", frame->ss, frame->cs);
  dprintf("              DS =     0x%04x       ES =     0x%04x\n", frame->ds, frame->es);
  dprintf("              FS =     0x%04x       GS =     0x%04x\n", frame->fs, frame->gs);
  dprintf("             EIP = 0x%08x   EFLAGS = 0x%08x\n", frame->eflags, frame->eip);

  // print EFLAGS flags
  dprintf("Flags:\n");
  dprintf("         ");
  dprintf("   CF=%u", ((frame->eflags >> 0) & 1));
  dprintf("   PF=%u", ((frame->eflags >> 2) & 1));
  dprintf("   AF=%u", ((frame->eflags >> 4) & 1));
  dprintf("   ZF=%u", ((frame->eflags >> 6) & 1));
  dprintf("   SF=%u", ((frame->eflags >> 7) & 1));
  dprintf("   TF=%u", ((frame->eflags >> 8) & 1));
  dprintf("\n         ");
  dprintf("   IF=%u", ((frame->eflags >> 9) & 1));
  dprintf("   DF=%u", ((frame->eflags >> 10) & 1));
  dprintf("   OF=%u", ((frame->eflags >> 11) & 1));
  dprintf(" IOPL=%u", ((frame->eflags >> 12) & 3));
  dprintf("   NT=%u", ((frame->eflags >> 14) & 1));
  dprintf("   RF=%u", ((frame->eflags >> 16) & 1));
  dprintf("\n         ");
  dprintf("   VM=%u", ((frame->eflags >> 17) & 1));
  dprintf("   AC=%u", ((frame->eflags >> 18) & 1));
  dprintf("  VIF=%u", ((frame->eflags >> 19) & 1));
  dprintf("  VIP=%u", ((frame->eflags >> 20) & 1));
  dprintf("   ID=%u", ((frame->eflags >> 21) & 1));
  dprintf("\n");

  // print PIC ISR and IRR
  dprintf("PIC info:\n");
  {
    uint16_t isr = pic_get_isr();
    uint16_t irr = pic_get_irr();
    dprintf("  ISR=%u, IRR=%u\n", isr, irr);
  }

  // dump stack
  extern const void _stack_top, _stack_bottom;
  dprintf("Stack:");
  {
    const void *ebp = (const void*)frame->ebp;
    const void *esp = (const void*)frame->esp;
    const void *ptr = esp - (uint32_t)esp % 16;
    while(ptr < &_stack_top) {
      if((uint32_t)ptr % 16 == 0) {
        dprintf("\n  0x%08x:  ", (uint32_t)ptr);
      } else if((uint32_t)ptr % 4 == 0) {
        dprintf(" ");
      }

      if(ptr == ebp) {
        esp = ebp;
        ebp = ((void**)ebp)[0];
      }
      
      dprintf("%c%02x", ptr == esp ? '{' : ' ', *(uint8_t*)ptr);

      ptr++;
    }

    dprintf("\n                         <  end of stack  >\n");
  }

  // dump stack trace
  dprintf("Stack trace:\n");
  {
    const void *eip = (const void*)frame->eip;
    const void *esp = (const void*)frame->esp;
    const void *ebp = (const void*)frame->ebp;

    do {
      dprintf("  function at <0x%08x>,    stack [ 0x%08x - 0x%08x ]\n", (uint32_t)eip, (uint32_t)esp, (uint32_t)ebp);

      esp = ebp;
      ebp = ((void**)esp)[0];
      eip = ((void**)esp)[1];
    } while(ebp > &_stack_bottom && ebp <= &_stack_top);

    dprintf("                      <  end of stack trace  >\n");
  }

  dprintf("\n");
}
