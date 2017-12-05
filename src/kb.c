#include "kb.h"

#include <stddef.h>
#include <stdint.h>

#include "debug.h"
#include "io.h"
#include "interrupt.h"

void kb_init() {
  // enable IRQ1 for keyboard
  outb(0x21, 0xFD);
}
