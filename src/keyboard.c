#include "keyboard.h"

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "debug.h"

#include "irq.h"
#include "io.h"

#define PS2_PORT 0x60

static void key_handler(struct full_interrupt_frame *frame) {
  uint8_t scancode = inb(PS2_PORT);
  bool pressed = (scancode & 0x80) == 0;

  // resolve extended scancodes (beginning with 0xE0 or 0xE1)
  static int scancode_more = 0;
  static uint16_t scancode_saved = 0;
  if(scancode_more <= 0) {
    if(scancode == 0xE0) {
      scancode_more = 1;
      scancode_saved = 0x0100;
      return;
    } else if(scancode == 0xE1) {
      scancode_more = 2;
      scancode_saved = 0x0000;
      return;
    } else {
      scancode = scancode & 0x7F;
    }
  } else if(scancode_more == 1) {
    scancode_more = 0;
    scancode = scancode & 0x7F | scancode_saved;
  } else {
    scancode_more--;
    scancode_saved |= (scancode & 0x7F) << 8;
    return;
  }

  if(scancode == 0x1D45) {
    // if Pause/Brk is pressed, then enter debug mode
    if(pressed) {
      set_irq_return(&enter_debug_mode);
    }
    return;
  }

  // dprintf("Unhandled key: %04X %s\n", scancode, (pressed ? "DOWN" : "UP"));
}

void install_keyboard() {
  set_irq_handler(1, &key_handler);
}
