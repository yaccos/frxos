#include "keyboard.h"

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "debug.h"

#include "irq.h"
#include "io.h"

#define PS2_PORT 0x60
#define MAX_PRESSED_KEYSTROKES 256

uint8_t reading_key = 0;
static size_t n_keystrokes_stored = 0;
static uint8_t pressed_keystrokes[MAX_PRESSED_KEYSTROKES] = {0};
static void key_handler(struct full_interrupt_frame *frame) {
  uint8_t scancode = inb(PS2_PORT);
  dprintf("Scancode: 0x%2X \n",scancode);
  bool pressed = (scancode & 0x80) == 0;

  // If a key is pressed and we are reading keystrokes, put it to the buffer
  if(pressed && reading_key){
	dprintf("Processing scancode ...\n");
  	pressed_keystrokes[n_keystrokes_stored++] = scancode;
  }

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

  if(scancode == 0x1D45 || scancode == 0x39) {
    // if Pause/Brk or spacebar is pressed, then enter debug mode
    if(pressed) {
      set_irq_return(&enter_debug_mode);
    }
    return;
  }

  // dprintf("Unhandled key: %04X %s\n", scancode, (pressed ? "DOWN" : "UP"));
}

// Utility for kernel components to get the recent keystrokes, but only
// one at a time as this is a stack
uint8_t keystroke_pop(){
	// Disables interrupts in order to prevent new keyboard events
	// to interfere and cause trouble
	irq_disable();
	uint8_t res;
	if (n_keystrokes_stored == 0){
		res = 0x00;
	}
	else{
		res = pressed_keystrokes[--n_keystrokes_stored];
	}
	irq_enable();
       return res;       
}
void install_keyboard() {
  set_irq_handler(1, &key_handler);
}
