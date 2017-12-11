#include "kernel.h"

#include <stddef.h>
#include <stdint.h>

#include "attr.h"
#include "debug.h"

#include "multiboot.h"

#include "gdt.h"
#include "idt.h"
#include "irq.h"
#include "memory.h"
#include "serial.h"
#include "display.h"
#include "timer.h"
#include "keyboard.h"
#include "shell.h"

/**
 * Call kernel initialization code
**/
void kernel_init(uint32_t mbmagic, multiboot_info_t *mbinfo) {
  install_serial(COM1); // initialize serial first, for debugging
  
  if(mbmagic != 0x2BADB002)
    kernel_halt("Invalid Multiboot magic word");
  
  // required multiboot flags
  uint32_t mb_required_flags = (1 << 0) | (1 << 6) | (1 << 12);
  if(mbinfo->flags & mb_required_flags != mb_required_flags)
    kernel_halt("Missing required Multiboot flags");
  
  install_gdt();
  install_idt();
  install_irq();

  install_memmgr(mbinfo);
  install_display();
  install_timer();
  install_keyboard();
}

/**
 * Main code for kernel
**/
void kernel_main() {
  shell();
}

/**
 * Call kernel finalization code (after clean exit from kernel_main())
**/
__fastcall void kernel_fini(const char *message) {
  // clear screen with message
  uint16_t color = 0x1F00;
  vga_fill(color);
  vga_printf(0, 0, color, "Kernel halted.");

  if(message) {
    vga_printf(2, 0, color, "%s", message);
  }
}
