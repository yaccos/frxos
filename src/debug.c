#include "debug.h"

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>

#include "mini-printf.h"
#include "serial.h"
#include "idt.h"

#define DEBUG_PORT COM1

void dprintf(const char *format, ...) {
  #define DEBUG_BUFFER_SIZE 4096
  static char debug_buffer[DEBUG_BUFFER_SIZE] = { 0 };
  
  va_list args;
  va_start(args, format);
  
  int len = mini_vsnprintf(debug_buffer, DEBUG_BUFFER_SIZE, format, args);
  
  if(len > 0) {
    serial_write(DEBUG_PORT, debug_buffer, len);
  }
  
  va_end(args);
  #undef DEBUG_BUFFER_SIZE
}

void __debug_mode(struct full_interrupt_frame *frame) {
}
