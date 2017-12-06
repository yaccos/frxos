#include "debug.h"

#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "mini-printf.h"
#include "serial.h"

#define DEBUG_PORT COM1

#define DEBUG_BUFFER_SIZE 4096
static char debug_buffer[DEBUG_BUFFER_SIZE] = { 0 };

void dprintf(const char *format, ...) {
  va_list args;
  va_start(args, format);

  int len = mini_vsnprintf(debug_buffer, DEBUG_BUFFER_SIZE, format, args);
  
  if(len > 0) {
    serial_write(DEBUG_PORT, debug_buffer, len);
  }

  va_end(args);
}
