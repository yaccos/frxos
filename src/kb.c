#include "kb.h"

#include <stddef.h>
#include <stdint.h>

#include "debug.h"
#include "io.h"
#include "interrupt.h"

void install_keyboard() {
}

void kb_int_handler() {
  dprintf("key!\n");
}
