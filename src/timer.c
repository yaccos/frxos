#include "timer.h"

#include <stddef.h>
#include <stdint.h>

#include "debug.h"

#include "idt.h"
#include "irq.h"
#include "io.h"

#define TIMER_CH0  0x40
#define TIMER_CH1  0x41
#define TIMER_CH2  0x42
#define TIMER_DATA 0x43

#define TIMER_DEFAULT_DIVIDER 0xFFFF // default ticks per IRQ

static uint16_t current_divider = 0;
static uint64_t clock_ticks = 0;

static void tick_handler(struct full_interrupt_frame *frame) {
  clock_ticks += current_divider;
}

void install_timer() {
  set_irq_handler(0, &tick_handler);
  set_timer_divider(TIMER_DEFAULT_DIVIDER);
}

void set_timer_divider(uint16_t divider) {
  current_divider = divider;

  outb(TIMER_DATA, 0x36);
  outb(TIMER_CH0, divider & 0xFF);
  outb(TIMER_CH0, (divider >> 8) & 0xFF);
}

uint64_t clock() {
  return clock_ticks;
}

void sleep(uint64_t sec) {
  const uint64_t start_time = clock_ticks;
  const uint64_t end_time = TICKS_PER_SEC * sec;
  wait_for(clock_ticks >= end_time);
}

void usleep(uint64_t usec) {
  const uint64_t start_time = clock_ticks;
  const uint64_t end_time = (TICKS_PER_SEC / 1000) * usec / 1000;
  wait_for(clock_ticks >= end_time);
}
