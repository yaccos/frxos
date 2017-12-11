#include "debug.h"

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>

#include "printf.h"
#include "serial.h"
#include "timer.h"
#include "idt.h"
#include "display.h"

#define DEBUG_PORT COM1

void dprintf(const char *format, ...) {
  #define DEBUG_BUFFER_SIZE 4096
  static char debug_buffer[DEBUG_BUFFER_SIZE] = { 0 };
  
  va_list args;
  va_start(args, format);
  
  int len = vsnprintf(debug_buffer, DEBUG_BUFFER_SIZE, format, args);
  
  if(len > 0) {
    serial_write(DEBUG_PORT, debug_buffer, len);
  }
  
  va_end(args);
  #undef DEBUG_BUFFER_SIZE
}

extern uint32_t in_debug_mode;    // current in debug mode?
extern uint32_t leave_debug_mode; // should leave debug mode?

void __debug_mode(struct full_interrupt_frame *frame) {
  in_debug_mode = 1;
  leave_debug_mode = 0;

  static uint16_t vga_tmp_buffer[VGA_SIZE];

  vga_readb(0, 0, vga_tmp_buffer, VGA_SIZE);

  const uint16_t COLOR     = 0x1F00;
  const uint16_t WEAK_COLOR= 0x1900;
  const uint16_t ON_COLOR  = 0xF100;
  const uint16_t OFF_COLOR = 0x1F00;

  vga_fill(COLOR);

  // draw debug info on screen
  {
    extern const char __stack_top, __stack_bottom;

    vga_printf(0,  0,   COLOR, "Debug Mode");

    // registers
    vga_printf(2,  0,   COLOR, "Registers");
    vga_printf(3,  2,   COLOR, "EAX=%08X", frame->eax);
    vga_printf(3,  16,  COLOR, "ECX=%08X", frame->ecx);
    vga_printf(3,  30,  COLOR, "EDX=%08X", frame->edx);
    vga_printf(4,  2,   COLOR, "EBX=%08X", frame->ebx);
    vga_printf(4,  16,  COLOR, "ESP=%08X", frame->esp);
    vga_printf(4,  30,  COLOR, "EBP=%08X", frame->ebp);
    vga_printf(5,  2,   COLOR, "ESI=%08X", frame->esi);
    vga_printf(5,  16,  COLOR, "EDI=%08X", frame->edi);
    vga_printf(5,  30,  COLOR, "EIP=%08X", frame->eip);
    vga_printf(6,  2,   COLOR, "SS=%04X",  frame->ss);
    vga_printf(6,  11,  COLOR, "CS=%04X",  frame->cs);
    vga_printf(7,  2,   COLOR, "DS=%04X",  frame->ds);
    vga_printf(7,  11,  COLOR, "ES=%04X",  frame->es);
    vga_printf(7,  20,  COLOR, "FS=%04X",  frame->fs);
    vga_printf(7,  29,  COLOR, "GS=%04X",  frame->gs);
    vga_printf(6,  27,  COLOR, "EFLAGS=%08X", frame->eflags);

    // flags
    vga_printf(9,  0,   COLOR, "Flags:");
    vga_printf(10, 2,   (frame->eflags >> 0) & 1 ? ON_COLOR : OFF_COLOR,  "CF=%u", (frame->eflags >> 0) & 1);
    vga_printf(10, 8,   (frame->eflags >> 2) & 1 ? ON_COLOR : OFF_COLOR,  "PF=%u", (frame->eflags >> 2) & 1);
    vga_printf(10, 14,  (frame->eflags >> 4) & 1 ? ON_COLOR : OFF_COLOR,  "AF=%u", (frame->eflags >> 4) & 1);
    vga_printf(10, 20,  (frame->eflags >> 6) & 1 ? ON_COLOR : OFF_COLOR,  "ZF=%u", (frame->eflags >> 6) & 1);
    vga_printf(10, 26,  (frame->eflags >> 7) & 1 ? ON_COLOR : OFF_COLOR,  "SF=%u", (frame->eflags >> 7) & 1);
    vga_printf(10, 32,  (frame->eflags >> 8) & 1 ? ON_COLOR : OFF_COLOR,  "TF=%u", (frame->eflags >> 8) & 1);
    vga_printf(10, 38,  (frame->eflags >> 9) & 1 ? ON_COLOR : OFF_COLOR,  "IF=%u", (frame->eflags >> 9) & 1);
    vga_printf(11, 2,   (frame->eflags >> 10) & 1 ? ON_COLOR : OFF_COLOR, "DF=%u", (frame->eflags >> 10) & 1);
    vga_printf(11, 8,   (frame->eflags >> 11) & 1 ? ON_COLOR : OFF_COLOR, "OF=%u", (frame->eflags >> 11) & 1);
    vga_printf(11, 18,  (frame->eflags >> 12) & 3 ? ON_COLOR : OFF_COLOR, "IOPL=%u", (frame->eflags >> 12) & 3);
    vga_printf(11, 26,  (frame->eflags >> 14) & 1 ? ON_COLOR : OFF_COLOR, "NT=%u", (frame->eflags >> 14) & 1);
    vga_printf(11, 32,  (frame->eflags >> 16) & 1 ? ON_COLOR : OFF_COLOR, "RF=%u", (frame->eflags >> 16) & 1);
    vga_printf(11, 38,  (frame->eflags >> 17) & 1 ? ON_COLOR : OFF_COLOR, "VM=%u", (frame->eflags >> 17) & 1);
    vga_printf(12, 2,   (frame->eflags >> 18) & 1 ? ON_COLOR : OFF_COLOR, "AC=%u", (frame->eflags >> 18) & 1);
    vga_printf(12, 8,   (frame->eflags >> 19) & 1 ? ON_COLOR : OFF_COLOR, "VIF=%u", (frame->eflags >> 19) & 1);
    vga_printf(12, 14,  (frame->eflags >> 20) & 1 ? ON_COLOR : OFF_COLOR, "VIP=%u", (frame->eflags >> 20) & 1);
    vga_printf(12, 20,  (frame->eflags >> 21) & 1 ? ON_COLOR : OFF_COLOR, "ID=%u", (frame->eflags >> 21) & 1);

    // stack
    vga_printf(0, 44, COLOR, "Stack:");
    {

      const char *ebp = (const char*)frame->ebp;
      const char *esp = (const char*)frame->esp;
      const char *ptr = esp - (uint32_t)esp % 16;

      uint32_t max_stack_lines = VGA_ROWS - 2;
      int i;
      for(i = 0; i < max_stack_lines && ptr < &__stack_top; i++) {
        vga_printf(1 + i, 46, COLOR, "%08X:", ptr);
        
        for(int j = 0; j < 8; j++) {
          if(ptr == ebp) {
            esp = ebp;
            ebp = ((const char**)ebp)[0];
          }    

          if(esp == ptr + j)
            vga_printf(1 + i, 56 + 3 * j - 1, WEAK_COLOR, "(");
          vga_printf(1 + i, 56 + 3 * j, COLOR, "%02X", ((uint8_t*)ptr)[j]);
        }
        ptr += 8;
      }
      if(i < max_stack_lines) {
        vga_printf(1 + i, 46, WEAK_COLOR, "%08X:         < top >        ", ptr);
      }
    }

    // stack trace
    vga_printf(14, 0, COLOR, "Stack trace:");
    {
      const char *eip = (const char*)frame->eip;
      const char *esp = (const char*)frame->esp;
      const char *ebp = (const char*)frame->ebp;
  
      uint32_t max_stack_lines = (VGA_ROWS - 16);
      int i;
      for(i = 0; i + 2 <= max_stack_lines && ebp > &__stack_bottom && ebp <= &__stack_top; i += 2) {
        vga_printf(15 + i, 2, COLOR, "function at <%08X>", eip);
        vga_printf(16 + i, 4, COLOR, "stack frame: %08X - %08X", esp, ebp);

        esp = ebp;
        ebp = ((const char**)esp)[0];
        eip = ((const char**)esp)[1];
      }
      if(i < max_stack_lines) {
        vga_printf(15 + i, 15, WEAK_COLOR, "< end >");
      }
      // do {
      //   vga_printf("  function at <0x%08x>,    stack [ 0x%08x - 0x%08x ]\n", (uint32_t)eip, (uint32_t)esp, (uint32_t)ebp);
  
      //   esp = ebp;
      //   ebp = ((void**)esp)[0];
      //   eip = ((void**)esp)[1];
      // } while(ebp > &_stack_bottom && ebp <= &_stack_top);
  
      // dprintf("                      <  end of stack trace  >\n");
    }
  
  }
  
  wait_for(leave_debug_mode);

  vga_writeb(0, 0, vga_tmp_buffer, VGA_SIZE);

  leave_debug_mode = 0;
  in_debug_mode = 0;
}

void __f() {
  dprintf(":: %u %u\n", in_debug_mode, leave_debug_mode);
}
