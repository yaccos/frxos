#include "keyboard.h"

#include <stddef.h>
#include <stdint.h>

#include "irq.h"

static void key_handler(struct full_interrupt_frame *frame) { }

void install_keyboard() {
  set_irq_handler(1, &key_handler);
}
