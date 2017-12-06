#include "kernel.h"

#include <stddef.h>
#include <stdint.h>

#include "debug.h"

#include "gdt.h"
#include "idt.h"
#include "irq.h"
#include "serial.h"
#include "display.h"
#include "timer.h"
#include "keyboard.h"

/**
 * Call kernel initialization code
**/
void kernel_init() {
  install_gdt();
  install_idt();
  install_irq();

  install_serial(COM1);
  install_display();
  install_timer();
  install_keyboard();
}

/**
 * Main code for kernel
**/
void kernel_main() {
  vga_printf(0, 0, 0xF000, "Hello, %s!\nHello, %s!", "World", "Diamond");
  for(;;) {
    vga_printf(4, 0, 0x0900, "  %u           ", (uint32_t)(clock() / TICKS_PER_SEC));
  }
}

/**
 * Call kernel finalization code (after clean exit from kernel_main())
**/
void kernel_fini() {
  dprintf("==== DONE ====\n");
}
