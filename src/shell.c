#include <stddef.h>
#include <stdint.h>

#include "attr.h"
#include "debug.h"

#include "display.h"
#include "timer.h"

#define SHELL_BUFFER_LENGTH 256

static const char *readline(char *buffer, size_t length);

void shell() {
  // char buffer[SHELL_BUFFER_LENGTH];
  // const char *line = readline(buffer, SHELL_BUFFER_LENGTH);

  // dprintf("line: %s\n", line);
}

static const char *readline(char *buffer, size_t length) {
  buffer[0] = 0;

  return buffer;
}
