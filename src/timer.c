#include "timer.h"

#include <stddef.h>
#include <stdint.h>

#include "io.h"

void timer_phase(uint16_t rate) {
  outb(0x43, 0x36);
  outb(0x40, rate & 0xFF);
  outb(0x40, (rate >> 8) & 0xFF);
}

void install_timer() {
  timer_phase(0xFFFF);
}

